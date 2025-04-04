#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstdint>
#include "RGB.hpp"

using namespace std;

// Function declarations
bool fileExists(const string &filename);
bool processImage(const string &imagePath, vector<vector<RGB>> &image);
bool errorValidation(const string &errorMethod);
void inputHandler(string &inputImagePath, vector<vector<RGB>> &image, string &errorMethod,
                  float &threshold, int &minBlockSize, float &targetCompression, string &outputImagePath);
void saveModifiedImage(const vector<vector<RGB>>& image, const string& outputImagePath);

#endif // UTILS_H
