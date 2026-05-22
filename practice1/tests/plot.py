#!/usr/bin/env python3

import csv
import matplotlib.pyplot as plt
from pathlib import Path

with (Path(__file__).parent / "results.csv").open() as f:
    f = csv.reader(f)
    next(f)
    (
        num_elements,
        insertion_sort_time,
        heap_sort_time,
        quick_sort_time,
        std_sort_time,
    ) = zip(*f)

num_elements = list(map(int, num_elements))
insertion_sort_time = list(map(float, insertion_sort_time))
heap_sort_time = list(map(float, heap_sort_time))
quick_sort_time = list(map(float, quick_sort_time))
std_sort_time = list(map(float, std_sort_time))

plt.plot(
    num_elements,
    insertion_sort_time,
    label="Сортировка простыми вставками",
    marker="o",
)
plt.plot(num_elements, heap_sort_time, label="Пирамидальная сортировка", marker="o")
plt.plot(num_elements, quick_sort_time, label="Быстрая сортировка", marker="o")
plt.plot(num_elements, std_sort_time, label="std::sort", marker="o")
plt.xlabel("Кол-во спортсменов")
plt.ylabel("Время (мс)")
plt.title("Лабораторная работа 1: Сравнение алгоритмов сортировки")
plt.grid(True, which="both", ls="--")
plt.legend()
plt.tight_layout()
plt.savefig("sorting_performance.png")
plt.show()
