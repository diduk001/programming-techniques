from random import choice, seed

from sportsman import Sportsman

RANDOM_SEED = 42
seed(RANDOM_SEED)

FIRST_NAMES = ("Alice", "Bob", "Charlie", "David", "Eve", "Frank", "Grace", "Heidi", "Ivan", "Judy", "Kevin", "Laura", "Mallory", "Nina", "Oscar", "Peggy", "Quentin", "Rupert", "Sybil", "Trent")
LAST_NAMES = ("Smith", "Johnson", "Williams", "Brown", "Jones", "Garcia", "Miller", "Davis", "Rodriguez", "Martinez", "Hernandez", "Lopez", "Gonzalez", "Wilson", "Anderson", "Thomas", "Taylor", "Moore", "Jackson", "Martin")
MIDDLE_NAMES = ("A.", "B.", "C.", "D.", "E.", "F.", "G.", "H.", "I.", "J.", "K.", "L.", "M.", "N.", "O.", "P.", "Q.", "R.", "S.", "T.", "U.", "V.", "W.", "X.", "Y.", "Z.")
SPORTS = ("Basketball", "Soccer", "Tennis", "Swimming", "Running", "Cycling", "Gymnastics", "Boxing", "Skiing", "Skateboarding", "Surfing", "Climbing", "Rowing", "Fencing", "Archery", "Golf", "Baseball", "Volleyball", "Rugby", "Cricket")
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
        weight=choice(range(MIN_WEIGHT, MAX_WEIGHT + 1))
    )

def generate_test_data(num_sportsmen: int):
    return [generate_sportsman() for _ in range(num_sportsmen)]
