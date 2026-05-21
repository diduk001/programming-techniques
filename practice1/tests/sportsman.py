from dataclasses import dataclass


@dataclass(frozen=True)
class Sportsman:
    first_name: str
    last_name: str
    middle_name: str
    sport: str
    age: int
    height: int
    weight: int

    def to_csv(self) -> str:
        return f"{self.sport},{self.last_name},{self.first_name},{self.middle_name},{self.age},{self.height},{self.weight}"

    @classmethod
    def from_csv(cls, csv_str: str):
        sport, last_name, first_name, middle_name, age, height, weight = csv_str.split(
            ","
        )
        return cls(
            first_name=first_name,
            last_name=last_name,
            middle_name=middle_name,
            sport=sport,
            age=int(age),
            height=int(height),
            weight=int(weight),
        )
