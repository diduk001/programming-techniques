#!/usr/bin/env python3

import csv
import matplotlib.pyplot as plt
from pathlib import Path

results_file = Path(__file__).parent / "results" / "results.csv"

with results_file.open() as f:
    reader = csv.DictReader(f)
    rows = list(reader)

sizes = [int(r["size"]) for r in rows]
aes_times = [float(r["aes_time"]) for r in rows]
fib_times = [float(r["fib_time"]) for r in rows]
rolling_times = [float(r["rolling_time"]) for r in rows]
std_times = [float(r["std_time"]) for r in rows]

plt.figure(figsize=(10, 6))
plt.plot(sizes, aes_times, label="AES PRNG", marker="o")
plt.plot(sizes, fib_times, label="Фибоначчи PRNG", marker="o")
plt.plot(sizes, rolling_times, label="Полиномиальный PRNG", marker="o")
plt.plot(sizes, std_times, label="std::mt19937_64", marker="o")
plt.xlabel("Размер выборки")
plt.ylabel("Время (мс)")
plt.xscale("log")
plt.yscale("log")
plt.title("Лабораторная работа 3: Сравнение скоростей генерации ПСЧ")
plt.legend()
plt.tight_layout()
plt.savefig(Path(__file__).parent / "results" / "prng_performance.png")
plt.show()
