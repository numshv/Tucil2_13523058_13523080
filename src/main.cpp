#include <bits/stdc++.h>
using namespace std;
#include "Utils.hpp"
#include "QuadTree.hpp"
#include <chrono>

int main(){
    string inputImagePath, errorMethod, outputImagePath;
    vector<vector<RGB>> image;
    std::vector<std::vector<RGB>> imageOri = image;
    float threshold, targetCompression;
    int minBlockSize;

    // Handle input and process the image
    inputHandler(inputImagePath, image, errorMethod, threshold, minBlockSize, targetCompression, outputImagePath);

    auto start = chrono::high_resolution_clock::now();

    //TODO: Implement rekursi di sini
    QuadTree qt;
    qt.nodeCount = 0;
    qt.maxDepth = 0;
    qt.root = new QuadTreeNode();

    QuadTreeNode qtn;
    if (errorMethod == "ssim"){
        qtn.buildNodeSSIM(qt.root, imageOri, image, 0, 0, image[0].size(), image.size(), threshold, qt.maxDepth, qt.nodeCount);
    }
    else{
        qtn.buildNode(qt.root, image, 0, 0, image[0].size(), image.size(), threshold, qt.maxDepth, qt.nodeCount, errorMethod);
    }
    std::vector<std::vector<RGB>> compressedImage = image;
    qt.reconstructImage(compressedImage);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    // cout << "Execution time: " << duration.count() << " ms" << endl;

    // Just to test if it's possible to modify and save it to a new file
    saveCompressedImage(compressedImage, outputImagePath);

    //TODO: output handler

    return 0;
}