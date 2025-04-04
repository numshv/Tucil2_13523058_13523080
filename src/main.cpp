#include <bits/stdc++.h>
using namespace std;
#include "Utils.hpp"
#include <chrono>

int main(){
    string inputImagePath, errorMethod, outputImagePath;
    vector<vector<RGB>> image;
    float threshold, targetCompression;
    int minBlockSize;

    // Handle input and process the image
    inputHandler(inputImagePath, image, errorMethod, threshold, minBlockSize, targetCompression, outputImagePath);

    auto start = chrono::high_resolution_clock::now();

    //TODO: Implement rekursi di sini

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    // cout << "Execution time: " << duration.count() << " ms" << endl;

    // Just to test if it's possible to modify and save it to a new file
    saveModifiedImage(image, outputImagePath);

    //TODO: output handler

    return 0;
}