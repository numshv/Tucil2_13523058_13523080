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
    qt.nodeCount = 0;
    qt.maxDepth = 0;
    qt.root = new QuadTreeNode();

    QuadTreeNode qtn;
    qtn.buildNode(qt.root, image, 0, 0, image[0].size(), image.size(), threshold, qt.maxDepth, qt.nodeCount, errorMethod);
    std::vector<std::vector<RGB>> compressedImage = image;
    qt.reconstructImage(compressedImage);

    // Rekursi selesai
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    // Just to test if it's possible to modify and save it to a new file
    saveCompressedImage(compressedImage, outputImagePath);

    outputHandler(outputImagePath, inputImagePath, qt, duration);

    return 0;
}