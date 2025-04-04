#include "ErrorMeasures.hpp"
#include <cmath>

bool variance(const vector<vector<RGB>>& image, int x, int y, int width, int height, float threshold, RGB &mean) {
    float sumR = 0, sumG = 0, sumB = 0;
    int totalPixels = width * height;

    // Compute mean for each color channel
    for (int i = y; i < y + height; ++i) {
        for (int j = x; j < x + width; ++j) {
            sumR += image[i][j].r;
            sumG += image[i][j].g;
            sumB += image[i][j].b;
        }
    }

    mean.r = static_cast<uint8_t>(sumR / totalPixels);
    mean.g = static_cast<uint8_t>(sumG / totalPixels);
    mean.b = static_cast<uint8_t>(sumB / totalPixels);

    // Compute variance for each color channel
    float varR = 0.0f, varG = 0.0f, varB = 0.0f;
    for (int i = y; i < y + height; ++i) {
        for (int j = x; j < x + width; ++j) {
            varR += pow(image[i][j].r - mean.r, 2);
            varG += pow(image[i][j].g - mean.g, 2);
            varB += pow(image[i][j].b - mean.b, 2);
        }
    }

    varR /= totalPixels;
    varG /= totalPixels;
    varB /= totalPixels;

    // Compute mean of overall RGB variance
    float meanVarRGB = (varR + varG + varB) / 3;
    return meanVarRGB <= threshold;
}

bool mad(const vector<vector<RGB>>& image, int x, int y, int width, int height, float threshold, RGB &mean) {
    float sumR = 0, sumG = 0, sumB = 0;
    int totalPixels = width * height;

    // Compute mean for each color channel
    for (int i = y; i < y + height; ++i) {
        for (int j = x; j < x + width; ++j) {
            sumR += image[i][j].r;
            sumG += image[i][j].g;
            sumB += image[i][j].b;
        }
    }

    mean.r = static_cast<uint8_t>(sumR / totalPixels);
    mean.g = static_cast<uint8_t>(sumG / totalPixels);
    mean.b = static_cast<uint8_t>(sumB / totalPixels);

    // Compute Mean Absolute Deviation for each color channel
    float madR = 0.0f, madG = 0.0f, madB = 0.0f;
    for (int i = y; i < y + height; ++i) {
        for (int j = x; j < x + width; ++j) {
            madR += abs(image[i][j].r - mean.r);
            madG += abs(image[i][j].g - mean.g);
            madB += abs(image[i][j].b - mean.b);
        }
    }

    madR /= totalPixels;
    madG /= totalPixels;
    madB /= totalPixels;

    // Compute overall MAD_RGB
    float madRGB = (madR + madG + madB) / 3;
    return madRGB <= threshold;
}

// TODO: Implement the max pixel difference (MPD) function

// TODO: Implement the entropy function

// Ini nanti selama rekursi pakai ini aja langsung
// Langsung masukin tipe error dan thresholdnya
// Warna yang mewakili (mean) juga pass by reference and langsung keisi
bool errorValidation(const string &errorMethod, const vector<vector<RGB>>& image, int x, int y, int width, int height, float threshold, RGB &mean) {
    if (errorMethod == "variance") {
        return variance(image, x, y, width, height, threshold, mean);
    } else if (errorMethod == "mad" || errorMethod == "mean absolute deviation") {
        return mad(image, x, y, width, height, threshold, mean);
    } else if (errorMethod == "max pixel difference") {
        return mpd(image, x, y, width, height, threshold, mean);
    } else{
        return entropy(image, x, y, width, height, threshold, mean);
    }
} 