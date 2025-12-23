import time

import sys

import matplotlib.pyplot as plt

from prettytable import PrettyTable

# Menambah batas rekursi supaya tidak error saat input angka besar
sys.setrecursionlimit(2000)

print("Library berhasil dimuat. Lanjut ke Cell berikutnya!")
# Iteratif
def hitung_kapital_iteratif(teks):
    
    jumlah = 0
    
    for huruf in teks:
        
        if 'A' <= huruf <= 'Z':
            
            jumlah = jumlah + 1
            
    return jumlah
# Rekursif
def hitung_kapital_rekursif(teks, n):

    if n == 0:
        
        return 0
    
    karakter = teks[n-1]
    
    if 'A' <= karakter <= 'Z':
        
        tambah = 1
        
    else:
        
        tambah = 0
        
    return tambah + hitung_kapital_rekursif(teks, n - 1)

print("Fungsi Algoritma siap digunakan.")
# Grafik untuk menyimpan data
n_values = []
recursive_times = []
iterative_times = []

# Fungsi memperbarui grafik
def update_graph():
    plt.figure(figsize=(8, 6))
    plt.plot(n_values, recursive_times, label='Recursive', marker='o', linestyle='-', color='red')
    plt.plot(n_values, iterative_times, label='Iterative', marker='o', linestyle='--', color='blue')
    plt.title('Performance Comparison: Recursive vs Iterative')
    plt.xlabel('Input Size (n)')
    plt.ylabel('Execution Time (seconds)')
    plt.legend()
    plt.grid(True)
    plt.show()

# Fungsi mencetak tabel waktu eksekusi
def print_execution_table():
    table = PrettyTable()
    table.field_names = ["n", "Recursive Time (s)", "Iterative Time (s)"]
    
    # Mengisi tabel sesuai jumlah data
    for i in range(len(n_values)):
        table.add_row([n_values[i], format(recursive_times[i], '.6f'), format(iterative_times[i], '.6f')])
        
    print(table)
# Program utama
while True:
    try:
        n = int(input("Masukkan nilai n (atau ketik -1 untuk keluar): "))
        
        if n == -1:
            print("Program selesai. Terima kasih!")
            break
            
        if n < 0:
            print("Masukkan nilai n yang positif!")
            continue

        # Generate Data Dummy
        pola = "AbCdEfGhIj" 
        teks = (pola * (n // 10 + 1))[:n]
        
        n_values.append(n)

        # Ukur waktu eksekusi algoritma rekursif
        start_time = time.time()
        
        # Panggil fungsi rekursif
        hitung_kapital_rekursif(teks, len(teks))
        recursive_times.append(time.time() - start_time)

        # Ukur waktu eksekusi algoritma iteratif
        start_time = time.time()
        
        # Panggil fungsi iteratif
        hitung_kapital_iteratif(teks)
        iterative_times.append(time.time() - start_time)

        # Cetak tabel waktu eksekusi
        print_execution_table()

        # Perbarui grafik
        update_graph()

    except ValueError:
        print("Masukkan nilai n yang valid!")




        # Cetak tabel waktu eksekusi