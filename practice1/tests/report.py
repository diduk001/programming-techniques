#!/usr/bin/env python3
"""Generates report.pdf: cover page (plot + repo link) followed by docs.pdf."""

import pathlib
import sys

from reportlab.lib.pagesizes import A4
from reportlab.lib.styles import getSampleStyleSheet, ParagraphStyle
from reportlab.lib.units import cm
from reportlab.platypus import Image, Paragraph, SimpleDocTemplate, Spacer
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont
from pypdf import PdfWriter, PdfReader
import io

_FONT_PATH = "/Library/Fonts/Arial Unicode.ttf"
_FONT_NAME = "ArialUnicode"
pdfmetrics.registerFont(TTFont(_FONT_NAME, _FONT_PATH))

REPO_URL = "https://github.com/diduk001/programming-techniques/tree/main/practice1"
BASE = pathlib.Path(__file__).parent.parent
PLOT = BASE / "sorting_performance.png"
DOCS = BASE / "docs.pdf"
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
    img_h = img_w * 480 / 640  # preserve 640×480 aspect ratio

    story = [
        Paragraph("Лабораторная работа 1", title_style),
        Spacer(1, 0.5 * cm),
        Image(str(PLOT), width=img_w, height=img_h),
        Spacer(1, 0.5 * cm),
        Paragraph(f'Репозиторий: <a href="{REPO_URL}">{REPO_URL}</a>', body_style),
    ]
    doc.build(story)
    return buf.getvalue()


def main():
    if not PLOT.exists():
        sys.exit(f"Missing: {PLOT}")
    if not DOCS.exists():
        sys.exit(f"Missing: {DOCS}")

    writer = PdfWriter()

    cover_bytes = build_cover()
    cover_reader = PdfReader(io.BytesIO(cover_bytes))
    for page in cover_reader.pages:
        writer.add_page(page)

    docs_reader = PdfReader(str(DOCS))
    for page in docs_reader.pages:
        writer.add_page(page)

    with open(OUT, "wb") as f:
        writer.write(f)

    print(f"Written: {OUT}")


if __name__ == "__main__":
    main()
