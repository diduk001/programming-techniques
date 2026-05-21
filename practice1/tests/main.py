#!/usr/bin/env python3

from generate import generate_test_data
import pathlib

TEST_SIZES = (
    100,
    250,
    500,
    1000,
    2500,
    5000,
    10000,
    25000,
    50000,
    100000,
    250000,
    500000,
)


def generate():
    for size in TEST_SIZES:
        sportsmen = generate_test_data(size)
        path = (
            pathlib.Path(__file__).parent
            / pathlib.Path("generated")
            / f"test_{size}.csv"
        )
        path.parent.mkdir(parents=True, exist_ok=True)
        with path.open("w") as f:
            f.write("sport,last_name,first_name,middle_name,age,height,weight\n")
            for sportsman in sportsmen:
                f.write(f"{sportsman.to_csv()}\n")


if __name__ == "__main__":
    generate()
