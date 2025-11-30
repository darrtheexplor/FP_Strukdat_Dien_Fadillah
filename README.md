# Laporan Final Project Struktur Data - Dien Fadillah Prihardini (5024241051)

```markdown
Simulasi Bola dengan Brute Force & QuadTree

Proyek ini adalah simulasi bola bergerak dalam sebuah window menggunakan SFML (Simple and Fast Multimedia Library).
Program ini membandingkan dua metode deteksi tabrakan antar bola:
1. Brute Force — semua bola dibandingkan satu per satu  
2. QuadTree — pencarian tabrakan dipercepat dengan membagi ruang menjadi empat bagian

Tujuan utama proyek ini adalah memahami perbedaan performa kedua algoritma terutama saat jumlah bola besar (hingga 10.000 bola).


Fitur Utama
- Bola bergerak otomatis dengan kecepatan acak
- Tabrakan dengan dinding
- Tabrakan antar bola (elastic collision)
- Dua mode algoritma collision:
  - Brute Force (O(n²))
  - QuadTree (O(n log n))
- Mudah switch algoritma dengan mengganti 1 variabel

Struktur Folder
project/
|── include/
|    |── bolAA.hpp
│── src/
│    ├── main.cpp
│    └── bolAA.cpp
│── Makefile
└── README.md

Penjelasan File

bolAA.hpp & bolAA.cpp
Berisi class `bola` yang mengatur:
- posisi
- kecepatan
- radius
- update gerakan
- tabrakan dengan batas window
- menggambar bola ke layar

main.cpp
Berfungsi sebagai inti program:
- membuat jendela SFML
- generate bola-bola
- update posisi tiap frame
- menjalankan deteksi tabrakan
- memilih algoritma (Brute Force atau QuadTree)
- render semua bola

QuadTree
Didefinisikan di `main.cpp`. Digunakan untuk mempercepat pencarian bola yang lokasinya saling berdekatan.

Ringkasan Algoritma Collision
1. Brute Force
Semua bola dicek satu per satu:
for i = 0..n
for j = i+1..n
cek tabrakan bola i dan j
- Sederhana
- Sangat lambat untuk >1000 bola
- Kompleksitas: O(n²)

2. QuadTree
- Ruang dibagi menjadi 4 grid
- Hanya bola dalam area kecil(grid) yang dibandingkan
- Lebih cepat signifikan untuk jumlah bola besar
- Kompleksitas: O(n log n)

Kesimpulan:
- Brute Force 10.000 bola → sangat lag  
- QuadTree 10.000 bola → masih playable  
