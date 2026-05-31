#!/usr/bin/env python3
import pathlib
import re
import sys

from reportlab.lib.pagesizes import A4
from reportlab.lib.styles import getSampleStyleSheet, ParagraphStyle
from reportlab.lib.units import cm
from reportlab.platypus import Image, Paragraph, SimpleDocTemplate, Spacer, Preformatted
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont
from pypdf import PdfWriter, PdfReader
import io

_FONT_PATH = "/Library/Fonts/Arial Unicode.ttf"
_FONT_NAME = "ArialUnicode"
pdfmetrics.registerFont(TTFont(_FONT_NAME, _FONT_PATH))

REPO_URL = "https://github.com/diduk001/programming-techniques/tree/main/practice3"
BASE = pathlib.Path(__file__).parent.parent
RESULTS = pathlib.Path(__file__).parent / "results"
PLOT = RESULTS / "prng_performance.png"
DOCS = BASE / "docs.pdf"
README = BASE / "README.md"
OUT = BASE / "report.pdf"


def build_cover() -> bytes:
    buf = io.BytesIO()
    doc = SimpleDocTemplate(
        buf,
        pagesize=A4,
        topMargin=2 * cm,
        bottomMargin=2 * cm,
        leftMargin=2 * cm,
        rightMargin=2 * cm,
    )
    styles = getSampleStyleSheet()
    page_w = A4[0] - 4 * cm

    title_style = ParagraphStyle(
        "CyrTitle", parent=styles["Title"], fontName=_FONT_NAME, fontSize=18
    )
    body_style = ParagraphStyle(
        "CyrBody", parent=styles["Normal"], fontName=_FONT_NAME, fontSize=11
    )

    img_w = page_w
    img_h = img_w * 0.6  # preserve 10x6 aspect ratio

    story = [
        Paragraph("Лабораторная работа 3", title_style),
        Spacer(1, 0.5 * cm),
        Image(str(PLOT), width=img_w, height=img_h),
        Spacer(1, 0.5 * cm),
        Paragraph(f'Репозиторий: <a href="{REPO_URL}">{REPO_URL}</a>', body_style),
    ]
    doc.build(story)
    return buf.getvalue()


def build_readme() -> bytes:
    buf = io.BytesIO()
    doc = SimpleDocTemplate(
        buf,
        pagesize=A4,
        topMargin=2 * cm,
        bottomMargin=2 * cm,
        leftMargin=2 * cm,
        rightMargin=2 * cm,
    )
    styles = getSampleStyleSheet()

    h1_style = ParagraphStyle("MdH1", parent=styles["Heading1"], fontName=_FONT_NAME, fontSize=16, spaceAfter=6)
    h2_style = ParagraphStyle("MdH2", parent=styles["Heading2"], fontName=_FONT_NAME, fontSize=13, spaceAfter=4)
    body_style = ParagraphStyle("MdBody", parent=styles["Normal"], fontName=_FONT_NAME, fontSize=10, spaceAfter=4)
    code_style = ParagraphStyle(
        "MdCode", parent=styles["Code"], fontName="Courier", fontSize=9,
        backColor="#f0f0f0", leftIndent=12, spaceAfter=4,
    )
    bullet_style = ParagraphStyle(
        "MdBullet", parent=styles["Normal"], fontName=_FONT_NAME, fontSize=10,
        leftIndent=16, spaceAfter=2,
    )

    text = README.read_text(encoding="utf-8")
    story = []
    in_code = False
    code_lines = []

    for line in text.splitlines():
        if line.startswith("```"):
            if in_code:
                story.append(Preformatted("\n".join(code_lines), code_style))
                code_lines = []
                in_code = False
            else:
                in_code = True
            continue
        if in_code:
            code_lines.append(line)
            continue

        if line.startswith("# "):
            story.append(Paragraph(line[2:], h1_style))
        elif line.startswith("## "):
            story.append(Paragraph(line[3:], h2_style))
        elif line.startswith("- ") or line.startswith("* "):
            content = line[2:]
            content = re.sub(r"`([^`]+)`", r'<font name="Courier">\1</font>', content)
            story.append(Paragraph(f"• {content}", bullet_style))
        elif line.startswith("!["):
            pass
        elif line.strip() == "":
            story.append(Spacer(1, 0.3 * cm))
        else:
            content = line
            content = re.sub(r"`([^`]+)`", r'<font name="Courier">\1</font>', content)
            content = re.sub(r"\*\*([^*]+)\*\*", r"<b>\1</b>", content)
            story.append(Paragraph(content, body_style))

    doc.build(story)
    return buf.getvalue()


def main():
    for path in (PLOT, README, DOCS):
        if not path.exists():
            sys.exit(f"Missing: {path}")

    writer = PdfWriter()

    for pdf_bytes in (build_cover(), build_readme()):
        for page in PdfReader(io.BytesIO(pdf_bytes)).pages:
            writer.add_page(page)

    for page in PdfReader(str(DOCS)).pages:
        writer.add_page(page)

    with open(OUT, "wb") as f:
        writer.write(f)

    print(f"Written: {OUT}")


if __name__ == "__main__":
    main()
