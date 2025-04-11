#include <bits/stdc++.h>
using namespace std;
#include "Utils.hpp"
#include "QuadTree.hpp"
#include <chrono>

int main(){
    string inputImagePath, errorMethod, outputImagePath;
    vector<vector<RGB>> image;
    float threshold, targetCompression;
    int minBlockSize;

    // Handle input and process the image
    inputHandler(inputImagePath, image, errorMethod, threshold, minBlockSize, targetCompression, outputImagePath);

    // Start menghitung waktu eksekusi
    auto start = chrono::high_resolution_clock::now();

    //Implementasi rekursi di sini
    QuadTree qt;
    vector<vector<RGB>> imageOri = image;
    if (errorMethod == "ssim"){
        qt.buildTree(image, imageOri, threshold, errorMethod, minBlockSize);
    }
    else{
        qt.buildTree(image, threshold, errorMethod, minBlockSize);
    }
    qt.reconstructImage(image);

    // Rekursi selesai
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    // Just to test if it's possible to modify and save it to a new file
    saveCompressedImage(image, outputImagePath);

    outputHandler(outputImagePath, inputImagePath, qt, duration);

    return 0;
}