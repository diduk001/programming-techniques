#!/usr/bin/env python3

from sportsman import Sportsman

from random import choice, seed
from pathlib import Path

RANDOM_SEED = 42
seed(RANDOM_SEED)


TEST_SIZES = (
    100,
    250,
    500,
    750,
    1000,
    2500,
    5000,
    7500,
    10000,
    25000,
    50000,
    75000,
    100000,
)

FIRST_NAMES = (
    "Alice",
    "Bob",
    "Charlie",
    "David",
    "Eve",
    "Frank",
    "Grace",
    "Heidi",
    "Ivan",
    "Judy",
    "Kevin",
    "Laura",
    "Mallory",
    "Nina",
    "Oscar",
    "Peggy",
    "Quentin",
    "Rupert",
    "Sybil",
    "Trent",
)
LAST_NAMES = (
    "Smith",
    "Johnson",
    "Williams",
    "Brown",
    "Jones",
    "Garcia",
    "Miller",
    "Davis",
    "Rodriguez",
    "Martinez",
    "Hernandez",
    "Lopez",
    "Gonzalez",
    "Wilson",
    "Anderson",
    "Thomas",
    "Taylor",
    "Moore",
    "Jackson",
    "Martin",
)
MIDDLE_NAMES = (
    "A.",
    "B.",
    "C.",
    "D.",
    "E.",
    "F.",
    "G.",
    "H.",
    "I.",
    "J.",
    "K.",
    "L.",
    "M.",
    "N.",
    "O.",
    "P.",
    "Q.",
    "R.",
    "S.",
    "T.",
    "U.",
    "V.",
    "W.",
    "X.",
    "Y.",
    "Z.",
)
SPORTS = (
    "Basketball",
    "Soccer",
    "Tennis",
    "Swimming",
    "Running",
    "Cycling",
    "Gymnastics",
    "Boxing",
    "Skiing",
    "Skateboarding",
    "Surfing",
    "Climbing",
    "Rowing",
    "Fencing",
    "Archery",
    "Golf",
    "Baseball",
    "Volleyball",
    "Rugby",
    "Cricket",
)
MIN_AGE, MAX_AGE = 18, 65
MIN_HEIGHT, MAX_HEIGHT = 150, 230
MIN_WEIGHT, MAX_WEIGHT = 50, 150


def generate_sportsman():
    return Sportsman(
        first_name=choice(FIRST_NAMES),
        last_name=choice(LAST_NAMES),
        middle_name=choice(MIDDLE_NAMES),
        sport=choice(SPORTS),
        age=choice(range(MIN_AGE, MAX_AGE + 1)),
        height=choice(range(MIN_HEIGHT, MAX_HEIGHT + 1)),
        weight=choice(range(MIN_WEIGHT, MAX_WEIGHT + 1)),
    )


def generate_test_data(num_sportsmen: int):
    return [generate_sportsman() for _ in range(num_sportsmen)]


def main():
    print("Generating test data...")
    for size in TEST_SIZES:
        print("Generating data for size:", size)
        sportsmen = generate_test_data(size)
        path = Path(__file__).parent / Path("generated") / f"test_{size}.csv"
        path.parent.mkdir(parents=True, exist_ok=True)
        with path.open("w") as f:
            f.write("sport,last_name,first_name,middle_name,age,height,weight\n")
            for sportsman in sportsmen:
                f.write(f"{sportsman.to_csv()}\n")
    print(f"Done generating {len(TEST_SIZES)} test files.")


if __name__ == "__main__":
    main()
