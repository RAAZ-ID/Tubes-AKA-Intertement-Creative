import time

import matplotlib.pyplot as plt

from prettytable import PrettyTable

# Algoritma Rekursif
def count_capitals_recursive(s, n=0, index=0):
    if index == len(s):
        return n
    if 65 <= ord(s[index]) <= 90:  # ASCII cek huruf kapital
        n += 1
    return count_capitals_recursive(s, n, index + 1)

# Algoritma Iteratif
def count_capitals_iterative(s):
    count = 0
    for char in s:
        if 65 <= ord(char) <= 90:  # ASCII cek huruf kapital
            count += 1
    return count

# Grafik untuk menyimpan data
n_values = []
recursive_times = []
iterative_times = []
capital_counts = []

# Fungsi untuk memperbarui grafik
def update_graph():
    plt.figure(figsize=(8, 6))
    plt.plot(n_values, recursive_times, label='Recursive', marker='o', linestyle='-')
    plt.plot(n_values, iterative_times, label='Iterative', marker='o', linestyle='-')
    plt.title('Performance Comparison: Recursive vs Iterative')
    plt.xlabel('Input Size (n)')
    plt.ylabel('Execution Time (seconds)')
    plt.legend()
    plt.grid(True)
    plt.show()

# Fungsi untuk mencetak tabel waktu eksekusi dan jumlah kapital
def print_execution_table():
    table = PrettyTable()
    table.field_names = ["Input Size (n)", "Recursive Time (s)", "Iterative Time (s)", "Huruf Kapital"]

    min_len = min(len(n_values), len(recursive_times), len(iterative_times), len(capital_counts))
    for i in range(min_len):
        table.add_row([n_values[i], recursive_times[i], iterative_times[i], capital_counts[i]])
    print(table)

# Program utama
while True:
    try:
        s = input("Masukkan string (atau ketik 'exit' untuk keluar): ")
        if s.lower() == 'exit':
            print("Program selesai. Terima kasih!")
            break

        # Menyimpan ukuran input (n)
        n = len(s)
        n_values.append(n)

        # Eksekusi algoritma rekursif
        start_time = time.time()
        recursive_count = count_capitals_recursive(s)
        recursive_times.append(time.time() - start_time)

        # Eksekusi algoritma iteratif
        start_time = time.time()
        iterative_count = count_capitals_iterative(s)
        iterative_times.append(time.time() - start_time)

        # Menyimpan jumlah huruf kapital ke dalam list
        capital_counts.append(recursive_count)

        # Mencetak tabel waktu eksekusi dan jumlah kapital
        print_execution_table()

        # Memperbarui grafik
        update_graph()

    except ValueError:
        print("Masukkan string yang valid!")
