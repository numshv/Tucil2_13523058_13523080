#ifndef UTILS_HPP
#define UTILS_HPP

#include <bits/stdc++.h>
#include "RGB.hpp"
#include "QuadTree.hpp"

using namespace std;

bool fileExists(const string &filename);
bool hasValidExtension(const string& filename);
string trim(const string &s);
string getNonEmptyLine(const string &prompt);
bool processImage(const string &imagePath, vector<vector<RGB>> &image);
bool isValidErrorMethod(const string &errorMethod);
bool isValidThreshold(const string &errorMethod, float threshold);
long long getFileSize(const std::string& path);
int getMaxBlockSize(const std::vector<std::vector<RGB>>& image);
void inputHandler(string &inputImagePath, vector<vector<RGB>> &image, string &errorMethod,
                  float &threshold, int &minBlockSize, float &targetCompression, string &outputImagePath);
void saveCompressedImage(const std::vector<std::vector<RGB>>& image, const std::string& outputImagePath);
float standardPercentageCompression(
    std::vector<std::vector<RGB>>& image,
    const std::string& inputImagePath,
    const std::string& outputImagePath,
    const std::string& errorMethod,
    int minBlockSize,
    float targetCompression,
    int& maxDepth,
    int& nodeCount
);
float ssimPercentageCompression(
    std::vector<std::vector<RGB>>& image1,
    const std::vector<std::vector<RGB>>& image2,
    const std::string& inputImagePath,
    const std::string& outputImagePath,
    const std::string& errorMethod,
    int minBlockSize,
    float targetCompression,
    int& maxDepth,
    int& nodeCount
);
void outputHandler(const string &outputImagePath, const string &inputImagePath, int maxDepth, int nodeCount, std::chrono::milliseconds duration);
#endif
