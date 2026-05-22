#!/usr/bin/env python3

from pathlib import Path
import subprocess
import csv
import tempfile


def run_executable(executable: Path, test_file: Path) -> tuple[float, float, float, float, float, int, int]:
    with tempfile.NamedTemporaryFile(suffix=".csv", delete=False) as tmp:
        tmp_path = Path(tmp.name)

    try:
        completed = subprocess.run(
            [str(executable), str(test_file.absolute()), str(tmp_path)],
            check=True,
            capture_output=True,
        )
    except subprocess.CalledProcessError as e:
        print(f"Error running {executable} with {test_file}: {e}")
        print(f"Stdout: {e.stdout.decode()}")
        print(f"Stderr: {e.stderr.decode()}")
        raise

    stdout = completed.stdout.decode().strip()
    collisions = 0
    total_insertions = 0
    for line in stdout.splitlines():
        if line.startswith("Hash collisions:"):
            collisions = int(line.split()[-1])
        elif line.startswith("Total insertions:"):
            total_insertions = int(line.split()[-1])

    with tmp_path.open() as f:
        reader = csv.DictReader(f)
        row = next(reader)

    tmp_path.unlink()

    return (
        float(row["LinearSearch"]),
        float(row["BinaryTreeSearch"]),
        float(row["RedBlackTreeSearch"]),
        float(row["HashTableSearch"]),
        float(row["MultimapSearch"]),
        collisions,
        total_insertions,
    )


def main():
    tests_dir = Path(__file__).parent
    executable = tests_dir.parent / "bin" / "main"
    results_dir = tests_dir / "results"
    results_dir.mkdir(exist_ok=True)

    results = []
    for test_file in sorted(
        (tests_dir / "generated").glob("test_*.csv"),
        key=lambda p: int(p.stem.split("_")[1]),
    ):
        size = int(test_file.stem.split("_")[1])
        print(f"Testing with {test_file.name} (size={size})...")
        linear, bst, rbt, hash_t, multimap, collisions, total_ins = run_executable(
            executable, test_file
        )
        results.append((size, linear, bst, rbt, hash_t, multimap, collisions, total_ins))

    print("Writing results...")
    with (results_dir / "results.csv").open("w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow([
            "size",
            "linear_search_time",
            "bst_time",
            "rbt_time",
            "hash_table_time",
            "multimap_time",
            "hash_collisions",
            "total_insertions",
        ])
        writer.writerows(results)
    print("Done.")


if __name__ == "__main__":
    main()
