# **Tugas Kecil 2 IF2211 Strategi Algoritma**
Kompresi Gambar dengan Metode QuadTree
<br>

## Table of Contents
- [Contributors](#contributors)
- [Kompresi gambar dengan quadtree](#kompresi-gambar-dengan-quadtree)
- [Bahasa yang digunakan](#bahasa-yang-digunakan)
- [Get Started](#get-started)
- [How To Use It](#how-to-use-it)


## Contributors
<div align="center">

| **NIM**  | **Nama** |
| ------------- |:-------------:|
| 13523058   | Noumisyifa Nabila Nareswari |
| 13523080   | Diyah Susan Nugrahani |

</div>

## Kompresi gambar dengan quadtree

Konsep pemanfaatan quadtree untuk kompresi gambar adalah dengan membagi gambar yang berukuran besar menjadi empat bagian dan mengevaluasi bagian tersebut dengan membandingkan komposisi warna red, green, and blue (RGB) pada piksel-piksel dalam gambar tersebut. Jika bagian tersebut tidak seragam maka bagian tersebut akan terus dibagi hingga mencapai situasi seragam di bagian tersebut atau telah mencapai ukuran minimum yang ditentukan. Penggunaan quadtree ini dapat mengurangi ukuran file gambar tanpa mengorbankan detail penting pada gambar tersebut.

## Bahasa yang digunakan
- C++

## Get Started
- Pastikan C++ Compiler (seperti g++) telah terinstal. Jika belum, anda dapat menginstallnya melalui:
  - **Windows**: install [MinGW](https://www.mingw-w64.org/) atau gunakan [WSL](https://learn.microsoft.com/en-us/windows/wsl/install) untuk mengakses compiler Linux
  - **MacOS**: install Xcode Command Line Tools dengan menjalankan `xcode-select --install`
  - **Linux**: jalankan `sudo apt install g++` di terminal (Debian/Ubuntu)

- Download file .zip pada release terbaru atau clone repository ini secara keseluruhan

## How To Use It

### 1. Menjalankan Program
- Buka CLI yang tersedia pada perangkat anda (command prompt, shell, etc.)
- Arahkan ke direktori utama folder project (root folder)
- Compile program dengan perintah berikut:

#### Untuk **Windows**:
  ```bash
g++ src/main.cpp src/utils/utils.cpp src/utils/QuadTree.cpp src/utils/QuadTreeNode.cpp src/utils/ErrorMeasures.cpp -o bin/main.exe -Isrc/includes -Isrc/utils
  ```

#### Untuk **Linux/macOS**:
  ```bash
g++ src/main.cpp src/utils/utils.cpp src/utils/QuadTree.cpp src/utils/QuadTreeNode.cpp src/utils/ErrorMeasures.cpp -o bin/main -Isrc/includes -Isrc/utils

  ```

- Jalankan program dengan perintah berikut:

#### Untuk **Windows**:
  ```bash
bin\main.exe
  ```

#### Untuk **Linux/macOS**:
  ```bash
./bin/main
  ```

### 2. Input Program
Program ini membutuhkan beberapa input dari pengguna secara interaktif melalui CLI (Command Line Interface). Input harus mengikuti format dan aturan berikut agar proses kompresi dapat berjalan dengan benar.

#### 1. Path Gambar yang Ingin Dikompresi
- Masukkan **path absolut** dari file gambar yang ingin dikompresi.
- File gambar **harus eksis** di path tersebut.
- **Wajib menyertakan ekstensi** file pada path (misal: `C:/Users/username/Pictures/image.png`).
- Hanya file dengan ekstensi berikut yang dapat diproses:
  - `.png`
  - `.jpg`
  - `.jpeg`
  - `.bmp`

#### 2. Path Output Hasil Kompresi
- Masukkan **path absolut** dari file output hasil kompresi.
- Path **tidak boleh sama** dengan path input.
- **Wajib menyertakan ekstensi** file pada path output (misal: `C:/Users/username/Pictures/compressed.jpg`).
- Ekstensi file output **harus** termasuk dalam daftar yang didukung:
  - `.png`
  - `.jpg`
  - `.jpeg`
  - `.bmp`

#### 3. Metode Error Calculation
- Akan ditampilkan daftar opsi metode error di layar.
- Pengguna cukup memilih dengan **memasukkan angka (tanpa titik)** sesuai metode yang diinginkan.
- Contoh input yang valid: `1`, `2`, dst.

#### 4. Nilai Threshold
- Nilai threshold harus berupa angka **sesuai batasan masing-masing metode error**:
  - **Variance**: `0 < threshold ≤ 65025`
  - **Mean Absolute Deviation (MAD)**: `0 < threshold ≤ 255`
  - **Max Pixel Difference**: `0 ≤ threshold ≤ 255`
  - **Entropy**: `0 ≤ threshold ≤ 8`
  - **Structural Similarity Index (SSIM)**: `0 < threshold < 1`

#### 5. Minimum Block Size
- Minimum block size harus berupa **bilangan bulat lebih besar dari 1**.
- Ukuran ini menentukan batas minimum pembagian blok gambar oleh QuadTree.

#### 6. Target Compression Percentage
- Masukkan **nilai desimal antara 0 hingga 1** (inklusif), sesuai dengan persentase kompresi yang diinginkan.
  - Contoh: `0.3` berarti target kompresi adalah 30%.
- Masukkan `0` jika ingin menggunakan **threshold manual** yang telah dimasukkan sebelumnya.
- Masukkan nilai **lebih dari 0** hingga `1` untuk menggunakan target kompresi otomatis.


### 3. Output File
Gambar hasil kompresi akan secara otomatis tersimpan pada absolute output path yang diberikan saat memasukkan input dan informasi terkait proses kompresi (output non-gambar) juga akan secara otomatis ditampilkan di terminal.

### 4. Contoh Alur Program
1. Input gambar yang ingin dikompres
![imgur](https://i.imgur.com/JsstQyk.png)
2. Lengkapi informasi yang diminta seperti absolute path gambar input, absolute path gambar output, metode error, threshold, minimum size block, dan target persentasi kompresi
![imgur](https://i.imgur.com/gzrlLrH.jpg)
3. Program akan memproses gambar tersebut kemudian akan muncul hasil kompresi gambar beserta detail informasi hasil kompresi sebagai berikut:
![imgur](https://i.imgur.com/zIasqfU.jpg)
4. Hasil kompresi gambar yang tersimpan di path output
![imgur](https://i.imgur.com/XkLd5Fl.jpg)
