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

    // Handle input validations and process the image into 2d vector of rgb
    inputHandler(inputImagePath, image, errorMethod, threshold, minBlockSize, targetCompression, outputImagePath);

    // Start the timer
    auto start = chrono::high_resolution_clock::now();

    //Start of quadtree recursion compression 

    QuadTree qt;
    qt.buildTree(image, threshold, errorMethod, minBlockSize);
    qt.reconstructImage(image);

    //End of quadtree recursion compression 

    auto end = chrono::high_resolution_clock::now();
    // Calculate the duration
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    // Save the image to the path
    saveCompressedImage(image, outputImagePath);

    // Print the output
    outputHandler(outputImagePath, inputImagePath, qt, duration);

    return 0;
}