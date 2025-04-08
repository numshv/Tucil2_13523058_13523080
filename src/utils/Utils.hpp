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

bool fileExists(const string &filename);
bool hasValidExtension(const string& filename);
string trim(const string &s);
string getNonEmptyLine(const string &prompt);
bool processImage(const string &imagePath, vector<vector<RGB>> &image);
bool isValidErrorMethod(const string &errorMethod);
bool isValidThreshold(const string &errorMethod, float threshold);
void inputHandler(string &inputImagePath, vector<vector<RGB>> &image, string &errorMethod,
                  float &threshold, int &minBlockSize, float &targetCompression, string &outputImagePath);
void saveCompressedImage(const std::vector<std::vector<RGB>>& image, const std::string& outputImagePath);

#endif
