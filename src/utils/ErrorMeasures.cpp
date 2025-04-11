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


// Calculate SSIM between two blocks
float calculateSSIM(const std::vector<std::vector<RGB>>& image1, 
    const std::vector<std::vector<RGB>>& uniformBlock,
    int x, int y, int width, int height) {
    const float C1 = 6.5025f;   // (0.01 * 255)^2
    const float C2 = 58.5225f;  // (0.03 * 255)^2

    // Weights for RGB channels
    const float wR = 0.299f;
    const float wG = 0.587f;
    const float wB = 0.114f;

    // Initialize variables for mean calculation
    float sumR1 = 0, sumG1 = 0, sumB1 = 0;
    float sumR2 = 0, sumG2 = 0, sumB2 = 0;
    float sumR1R2 = 0, sumG1G2 = 0, sumB1B2 = 0;
    float sumR1Sq = 0, sumG1Sq = 0, sumB1Sq = 0;
    float sumR2Sq = 0, sumG2Sq = 0, sumB2Sq = 0;

    int count = 0;

    // Calculate sums for means, variances and covariances
    for (int j = 0; j < height && j < uniformBlock.size() && y + j < image1.size(); j++) {
    for (int i = 0; i < width && i < uniformBlock[j].size() && x + i < image1[y + j].size(); i++) {
    float r1 = image1[y + j][x + i].r;
    float g1 = image1[y + j][x + i].g;
    float b1 = image1[y + j][x + i].b;

    float r2 = uniformBlock[j][i].r;
    float g2 = uniformBlock[j][i].g;
    float b2 = uniformBlock[j][i].b;

    // Sum for means
    sumR1 += r1;
    sumG1 += g1;
    sumB1 += b1;

    sumR2 += r2;
    sumG2 += g2;
    sumB2 += b2;

    // Sum for variances
    sumR1Sq += r1 * r1;
    sumG1Sq += g1 * g1;
    sumB1Sq += b1 * b1;

    sumR2Sq += r2 * r2;
    sumG2Sq += g2 * g2;
    sumB2Sq += b2 * b2;

    // Sum for covariances
    sumR1R2 += r1 * r2;
    sumG1G2 += g1 * g2;
    sumB1B2 += b1 * b2;

    count++;
    }
    }

    if (count == 0) return 0.0f;

    // Calculate means
    float meanR1 = sumR1 / count;
    float meanG1 = sumG1 / count;
    float meanB1 = sumB1 / count;

    float meanR2 = sumR2 / count;
    float meanG2 = sumG2 / count;
    float meanB2 = sumB2 / count;

    // Calculate variances and covariances
    float varR1 = (sumR1Sq / count) - (meanR1 * meanR1);
    float varG1 = (sumG1Sq / count) - (meanG1 * meanG1);
    float varB1 = (sumB1Sq / count) - (meanB1 * meanB1);

    float varR2 = (sumR2Sq / count) - (meanR2 * meanR2);
    float varG2 = (sumG2Sq / count) - (meanG2 * meanG2);
    float varB2 = (sumB2Sq / count) - (meanB2 * meanB2);

    float covarR = (sumR1R2 / count) - (meanR1 * meanR2);
    float covarG = (sumG1G2 / count) - (meanG1 * meanG2);
    float covarB = (sumB1B2 / count) - (meanB1 * meanB2);

    // Calculate SSIM for each channel
    float ssimR = ((2 * meanR1 * meanR2 + C1) * (2 * covarR + C2)) / 
    ((meanR1 * meanR1 + meanR2 * meanR2 + C1) * (varR1 + varR2 + C2));

    float ssimG = ((2 * meanG1 * meanG2 + C1) * (2 * covarG + C2)) / 
    ((meanG1 * meanG1 + meanG2 * meanG2 + C1) * (varG1 + varG2 + C2));

    float ssimB = ((2 * meanB1 * meanB2 + C1) * (2 * covarB + C2)) / 
    ((meanB1 * meanB1 + meanB2 * meanB2 + C1) * (varB1 + varB2 + C2));

    // Calculate weighted SSIM
    float ssimRGB = wR * ssimR + wG * ssimG + wB * ssimB;

    return ssimRGB;
}

bool ssim(const std::vector<std::vector<RGB>>& image, int x, int y, int width, int height, 
    float threshold, RGB &mean) {
    // Calculate mean color of the block
    float sumR = 0, sumG = 0, sumB = 0;
    int count = 0;

    for (int j = y; j < y + height && j < image.size(); j++) {
    for (int i = x; i < x + width && i < image[j].size(); i++) {
    sumR += image[j][i].r;
    sumG += image[j][i].g;
    sumB += image[j][i].b;
    count++;
    }
    }

    if (count == 0) return false;

    // Set the mean color
    mean.r = static_cast<int>(sumR / count);
    mean.g = static_cast<int>(sumG / count);
    mean.b = static_cast<int>(sumB / count);

    // Create a uniform block with the mean color
    std::vector<std::vector<RGB>> uniformBlock(height, std::vector<RGB>(width, mean));

    // Calculate SSIM between original block and uniform block
    float ssimValue = calculateSSIM(image, uniformBlock, x, y, width, height);

    // Return true if SSIM is above threshold (higher similarity means block can be compressed)
    return ssimValue > threshold;
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