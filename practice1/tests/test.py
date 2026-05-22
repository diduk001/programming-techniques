#!/usr/bin/env python3

from pathlib import Path
import subprocess
import csv


def parse_stdout(stdout: str) -> tuple[float, float, float, float]:
    lines = stdout.splitlines()
    result = tuple(float(line.split()[-1]) for line in lines)
    assert len(result) == 4, "Expected 4 timing results"
    return result


# Insertion sort time, Heap sort time, Quick sort time, std::sort time
def test_with_file(
    executable: Path, test_file: Path
) -> tuple[float, float, float, float]:
    try:
        completed = subprocess.run(
            [str(executable), str(test_file.absolute()), "/dev/null"],
            check=True,
            capture_output=True,
        )
    except subprocess.CalledProcessError as e:
        print(f"Error running {executable} with {test_file}: {e}")
        print(f"Stdout: {e.stdout.decode()}")
        print(f"Stderr: {e.stderr.decode()}")
        raise
    output = completed.stdout.decode().strip()
    return parse_stdout(output)


def main():
    results = []
    for test_file in (Path(__file__).parent / "generated").glob("test_*.csv"):
        num_sportsmen = test_file.stem.split("_")[1]
        executable = Path(__file__).parent.parent / "bin" / "main"
        timings = test_with_file(executable, test_file)
        results.append((num_sportsmen, timings[0], timings[1], timings[2], timings[3]))

    writer = csv.writer(open(Path(__file__).parent / "results.csv", "w"))
    writer.writerow(
        [
            "num_sportsmen",
            "insertion_sort_time",
            "heap_sort_time",
            "quick_sort_time",
            "std_sort_time",
        ]
    )
    writer.writerows(results)


if __name__ == "__main__":
    main()
