# Laporan Final Project Struktur Data - Dien Fadillah Prihardini (5024241051)

```markdown
# Simulasi Bola dengan Brute Force & QuadTree

Proyek ini adalah simulasi bola bergerak dalam sebuah window menggunakan SFML (Simple and Fast Multimedia Library).
Program ini membandingkan dua metode deteksi tabrakan antar bola:
1. Brute Force — semua bola dibandingkan satu per satu  
2. QuadTree — pencarian tetangga dipercepat dengan membagi ruang menjadi empat bagian

Tujuan utama proyek ini adalah memahami perbedaan performa kedua algoritma terutama saat jumlah bola besar (hingga 10.000 bola).

---

## Fitur Utama
- Bola bergerak otomatis dengan kecepatan acak
- Ukuran bola seragam
- Tabrakan dengan dinding
- Tabrakan antar bola (elastic collision)
- Dua mode algoritma collision:
  - Brute Force (O*n²*)
  - QuadTree (O*n log n*)
- Mudah switch algoritma dengan mengganti 1 variabel

## Struktur Folder

project/
│── src/
│    ├── main.cpp
│    ├── Ball.cpp
│    └── Ball.hpp
│── Makefile
└── README.md

## 🧩 Penjelasan File

### **Ball.hpp & Ball.cpp**
Berisi class `Ball` yang mengatur:
- posisi
- kecepatan
- radius
- update gerakan
- tabrakan dengan batas window
- menggambar bola ke layar

### **main.cpp**
Berfungsi sebagai inti program:
- membuat jendela SFML
- generate bola-bola
- update posisi tiap frame
- menjalankan deteksi tabrakan
- memilih algoritma (Brute Force atau QuadTree)
- render semua bola

### **QuadTree**
Didefinisikan di `main.cpp`. Digunakan untuk mempercepat pencarian bola yang lokasinya saling berdekatan.

---

## 🧠 Ringkasan Algoritma Collision

### 🔹 1. **Brute Force**
Semua bola dicek satu per satu:

```

for i = 0..n
for j = i+1..n
cek tabrakan bola i dan j

```

- **Sederhana**
- **Sangat lambat untuk >1000 bola**
- Kompleksitas: **O(n²)**

---

### 🔹 2. **QuadTree**
Ruang dijadikan grid dinamis:

```

┌───────┬───────┐
│   NW  │   NE  │
├───────┼───────┤
│   SW  │   SE  │
└───────┴───────┘

```

- Hanya bola dalam area kecil yang dibandingkan
- Lebih cepat signifikan untuk jumlah bola besar
- Kompleksitas: **O(n log n)**

---

## ⚖️ Brute Force vs QuadTree

| Algoritma     | Kecepatan | Kelebihan | Kekurangan |
|---------------|-----------|-----------|------------|
| Brute Force   | ❌ Lambat | Mudah dipahami | Tidak cocok > 1000 bola |
| QuadTree      | ✅ Cepat  | Efisien sampai 10.000 bola | Implementasi lebih rumit |

Hasil umum:
- **Brute Force 10.000 bola** → sangat lag  
- **QuadTree 10.000 bola** → masih playable  

---

## 🛠 Cara Install SFML

### **Ubuntu / WSL**
```

sudo apt update
sudo apt install libsfml-dev

```

---

## 🧪 Cara Compile

### **Manual**
```

g++ main.cpp Ball.cpp -o bola 
-lsfml-graphics -lsfml-window -lsfml-system

```

### Jalankan:
```

./bola

````

---

## 🔀 Cara Mengubah Algoritma yang Dipakai

Di `main.cpp`:

```cpp
bool useQuadTree = true;  // gunakan QuadTree
// bool useQuadTree = false;  // pakai Brute Force
````

---

## 📷 (Opsional) Screenshot

Tambahkan di repo jika mau:

```
![preview](img/sim.png)
```

---

## 👤 Author

**Dien Fadillah Prihardini**

---

```

---

Kalau kamu mau:
- bikin **README versi Bahasa Inggris**, atau  
- tambah **diagram**,  
- atau buat **laporan PDF siap print**,  

tinggal bilang aja!
```
