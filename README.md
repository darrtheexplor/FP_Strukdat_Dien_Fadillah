# Laporan Final Project Struktur Data - Dien Fadillah Prihardini (5024241051)

Simulasi Bola dengan Brute Force & QuadTree

# Pendahuluan
Pada simulasi ini dilakukan perbandingan antara dua metode deteksi tabrakan objek, yaitu Brute Force dan QuadTree. Deteksi tabrakan merupakan komponen penting dalam game, simulasi fisika, dan aplikasi interaktif lainnya. Ketika jumlah objek semakin banyak, algoritma deteksi tabrakan dapat menjadi lambat dan tidak efisien jika tidak menggunakan struktur data yang tepat. Oleh karena itu, proyek ini bertujuan untuk memahami bagaimana kedua metode bekerja, apa perbedaannya, serta bagaimana pengaruhnya terhadap performa ketika jumlah objek meningkat.
Proyek ini adalah simulasi bola bergerak dalam sebuah window menggunakan SFML (Simple and Fast Multimedia Library).
Program ini membandingkan dua metode deteksi tabrakan antar bola:
1. Brute Force — semua bola dibandingkan satu per satu  
2. QuadTree — pencarian tabrakan dipercepat dengan membagi ruang menjadi empat bagian

# Tujuan
Tujuan dari proyek ini adalah:
- Membandingkan cara kerja algoritma Brute Force dan QuadTree dalam mendeteksi tabrakan antar bola.
- Menunjukkan pengaruh jumlah objek terhadap performa masing-masing metode.
- Mengimplementasikan QuadTree sederhana untuk mendukung deteksi tabrakan yang lebih efisien.
- Memberikan pemahaman konsep spasial partitioning untuk optimasi game development.

# Fitur Utama
- Bola bergerak otomatis dengan kecepatan acak
- Tabrakan dengan dinding
- Tabrakan antar bola (elastic collision)
- Dua mode algoritma collision:
  - Brute Force (O(n²))
  - QuadTree (O(n log n))
- Mudah switch algoritma dengan mengganti 1 variabel

# Struktur Folder
project/
|── include/
|    |── bolAA.hpp
│── src/
│    ├── main.cpp
│    └── bolAA.cpp
│── Makefile
└── README.md

# Penjelasan File
bolAA.hpp & bolAA.cpp
Berisi class 'bola' yang mengatur:
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

# QuadTree
Didefinisikan di 'main.cpp'. Digunakan untuk mempercepat pencarian bola yang lokasinya saling berdekatan.

# Ringkasan Algoritma Collision
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

# Kesimpulan:
Pada proyek simulasi ini, algoritma Brute Force dan QuadTree telah berhasil diimplementasikan untuk mendeteksi tabrakan antar bola. Brute Force bekerja sederhana tetapi memiliki kompleksitas tinggi sehingga kurang efisien untuk jumlah objek besar. Sebaliknya, QuadTree membagi ruang dan hanya mengecek objek yang saling berdekatan, sehingga performanya jauh lebih baik dan skalabel. Dengan demikian, QuadTree merupakan pilihan yang lebih tepat untuk simulasi berskala besar, game, dan aplikasi yang memerlukan efisiensi tinggi.