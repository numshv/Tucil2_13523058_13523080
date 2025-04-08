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

bool mpd(const vector<vector<RGB>>& image, int x, int y, int width, int height, float threshold, RGB &mean){
    float sumR = 0, sumG = 0, sumB = 0;
    int totalPixels = width * height;
    
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
    
    // Find min and max values for each channel
    uint8_t minR = 255, minG = 255, minB = 255;
    uint8_t maxR = 0, maxG = 0, maxB = 0;
    
    for (int i = y; i < y + height; ++i) {
        for (int j = x; j < x + width; ++j) {
            // update min values
            minR = min(minR, image[i][j].r);
            minG = min(minG, image[i][j].g);
            minB = min(minB, image[i][j].b);
            
            // update max values
            maxR = max(maxR, image[i][j].r);
            maxG = max(maxG, image[i][j].g);
            maxB = max(maxB, image[i][j].b);
        }
    }
    
    // Calculate D_c = max(P_i,c) - min(P_i,c) for each channel
    float D_R = maxR - minR;
    float D_G = maxG - minG;
    float D_B = maxB - minB;
    
    float D_RGB = (D_R + D_G + D_B) / 3.0f;
    
    return D_RGB <= threshold;
} 

bool entropy(const vector<vector<RGB>>& image, int x, int y, int width, int height, float threshold, RGB &mean) {
    // Initialize frequency tables for R, G, B channels
    int histR[256] = {0};
    int histG[256] = {0};
    int histB[256] = {0};
    
    int totalPixels = width * height;
    if (totalPixels <= 0) return false;
    
    // Initialize mean values
    int sumR = 0;
    int sumG = 0;
    int sumB = 0;
    
    // Count frequencies and calculate sum
    for (int j = y; j < y + height && j < image.size(); j++) {
        for (int i = x; i < x + width && i < image[j].size(); i++) {
            histR[image[j][i].r]++;
            histG[image[j][i].g]++;
            histB[image[j][i].b]++;
            
            sumR += image[j][i].r;
            sumG += image[j][i].g;
            sumB += image[j][i].b;
        }
    }
    
    // Update mean values
    mean.r = sumR / totalPixels;
    mean.g = sumG / totalPixels;
    mean.b = sumB / totalPixels;
    
    // Calculate entropy for each channel
    float entropyR = 0.0f;
    float entropyG = 0.0f;
    float entropyB = 0.0f;
    
    for (int i = 0; i < 256; i++) {
        if (histR[i] > 0) {
            float probR = (float)histR[i] / totalPixels;
            entropyR -= probR * log2f(probR);
        }
        
        if (histG[i] > 0) {
            float probG = (float)histG[i] / totalPixels;
            entropyG -= probG * log2f(probG);
        }
        
        if (histB[i] > 0) {
            float probB = (float)histB[i] / totalPixels;
            entropyB -= probB * log2f(probB);
        }
    }
    
    float avgEntropy = (entropyR + entropyG + entropyB) / 3.0f;

    return avgEntropy <= threshold;
}

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