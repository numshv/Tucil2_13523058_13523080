# **Tugas Kecil 2 IF2211 Strategi Algoritma**
Kompresi Gambar dengan Metode QuadTree
<br>

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

## Bagaimana Cara Menjalankan Program
1. Opsi 1 dapat dilakukan dengan menjalankan file executable yang terdapat pada folder bin
2. Opsi 2 dapat dilakukan dengan mengcompile program ini secara manual
3. Pastikan di komputer anda sudah terpasang C++
4. Clone repository ini lalu jalankan command berikut
```sh
git clone https://github.com/numshv/Tucil2_13523058_13523080.git
cd src
g++ main.cpp utils/utils.cpp utils/QuadTree.cpp utils/QuadTreeNode.cpp utils/ErrorMeasures.cpp -o main.exe -Iincludes -Iutils
```

## Fitur kompresi
Pada program ini terdapat beberapa opsi pendekatan error measurement untuk kompresi gambar, diantaranya :
1. Variance
2. Mean Absolute Deviation (MAD)
3. Max Pixel Difference
4. Entropy
5. Structural Similarity Index (SSIM)

## Cara menggunakan Program
1. Input gambar yang ingin dikompres
![imgur](https://i.imgur.com/JsstQyk.png)
2. Lengkapi informasi terkait metode, threshold, dan minimum size block
![imgur](https://i.imgur.com/gzrlLrH.jpg)
3. Program akan memproses gambar tersebut kemudian akan muncul hasil kompresi gambar beserta detail informasi lainnya
4. Hasil kompresi gambar
![imgur](https://i.imgur.com/XkLd5Fl.jpg)
6. Detail informasi terkait gambar hasil kompresi
![imgur](https://i.imgur.com/zIasqfU.jpg)
