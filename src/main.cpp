#include <bits/stdc++.h>
using namespace std;
#include "Utils.hpp"

int main(){
    string inputImagePath, errorMethod, outputImagePath;
    vector<vector<RGB>> image;
    float threshold, targetCompression;
    int minBlockSize;

    // Handle input and process the image
    inputHandler(inputImagePath, image, errorMethod, threshold, minBlockSize, targetCompression, outputImagePath);

    // Just to test if it's possible to modify and save it to a new file
    saveModifiedImage(image, outputImagePath);

    return 0;
}