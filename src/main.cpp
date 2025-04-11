#include <bits/stdc++.h>
using namespace std;
#include "Utils.hpp"
#include "QuadTree.hpp"
#include <chrono>

int main(){
    string inputImagePath, errorMethod, outputImagePath;
    vector<vector<RGB>> image;
    float threshold, targetCompression, bestThreshold;
    int minBlockSize, maxDepth, nodeCount;

    // Handle input and process the image
    inputHandler(inputImagePath, image, errorMethod, threshold, minBlockSize, targetCompression, outputImagePath);

    // Start menghitung waktu eksekusi
    auto start = chrono::high_resolution_clock::now();

    QuadTree qt;

    //Implementasi rekursi di sini
    if(targetCompression == 0){
        vector<vector<RGB>> imageOri = image;
        if (errorMethod == "ssim"){
            qt.buildTree(image, imageOri, threshold, errorMethod, minBlockSize);
        }
        else{
            qt.buildTree(image, threshold, errorMethod, minBlockSize);
        }
        maxDepth = qt.maxDepth;
        nodeCount = qt.nodeCount;
        qt.reconstructImage(image);
        saveCompressedImage(image, outputImagePath);
    } else {
        if(errorMethod == "ssim"){
            vector<vector<RGB>> imageOri = image;
            bestThreshold = ssimPercentageCompression(image, imageOri, inputImagePath, outputImagePath, errorMethod, minBlockSize, targetCompression, maxDepth, nodeCount);
            qt.buildTree(image, imageOri, bestThreshold, errorMethod, minBlockSize);
        } else{ 
            bestThreshold = standardPercentageCompression(image, inputImagePath, outputImagePath, errorMethod, minBlockSize, targetCompression, maxDepth, nodeCount);
            qt.buildTree(image, bestThreshold, errorMethod, minBlockSize);
        }
    }

    // Rekursi selesai
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    outputHandler(outputImagePath, inputImagePath, maxDepth, nodeCount, duration);

    return 0;
}