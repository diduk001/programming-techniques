#!/usr/bin/env python3

import csv
import matplotlib.pyplot as plt
from pathlib import Path

results_file = Path(__file__).parent / "results" / "results.csv"

with results_file.open() as f:
    reader = csv.DictReader(f)
    rows = list(reader)

sizes = [int(r["size"]) for r in rows]
linear_times = [float(r["linear_search_time"]) for r in rows]
bst_times = [float(r["bst_time"]) for r in rows]
rbt_times = [float(r["rbt_time"]) for r in rows]
hash_times = [float(r["hash_table_time"]) for r in rows]
multimap_times = [float(r["multimap_time"]) for r in rows]
collisions = [int(r["hash_collisions"]) for r in rows]

# Search time comparison
plt.figure(figsize=(10, 6))
plt.plot(sizes, linear_times, label="Линейный поиск", marker="o")
plt.plot(sizes, bst_times, label="Бинарное дерево поиска", marker="o")
plt.plot(sizes, rbt_times, label="Красно-чёрное дерево", marker="o")
plt.plot(sizes, hash_times, label="Хэш таблица", marker="o")
plt.plot(sizes, multimap_times, label="std::multimap", marker="o")
plt.xlabel("Размер массива")
plt.ylabel("Время (мс)")
plt.xscale("log")
plt.yscale("log")
plt.title("Лабораторная работа 2: Сравнение алгоритмов поиска")
plt.legend()
plt.tight_layout()
plt.savefig(Path(__file__).parent / "results" / "search_performance.png")
plt.show()

# Hash collisions vs size
plt.figure(figsize=(10, 6))
plt.plot(sizes, collisions, label="Коллизии хэш-функции", marker="o", color="tab:red")
plt.xlabel("Размер массива")
plt.ylabel("Число коллизий")
plt.xscale("log")
plt.title("Лабораторная работа 2: Коллизии хэш-функции")
plt.legend()
plt.tight_layout()
plt.savefig(Path(__file__).parent / "results" / "hash_collisions.png")
plt.show()
