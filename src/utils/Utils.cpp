#define STB_IMAGE_IMPLEMENTATION
#include <bits/stdc++.h>
#include "../includes/stb_image.h"
using namespace std;
#include "Utils.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../includes/stb_image_write.h"

// Function to check if a file exists
bool fileExists(const string &filename) {
    ifstream file(filename);
    return file.good();
}

// Function to process image into 2D vector of RGB using stb_image.h
bool processImage(const string &imagePath, vector<vector<RGB>> &image) {
    int width, height, channels;

    // Load image using stb_image (returns raw pixel data)
    unsigned char *data = stbi_load(imagePath.c_str(), &width, &height, &channels, 3);
    if (!data) {
        cerr << "Error: Could not load image: " << imagePath << endl;
        return false;
    }

    // Resize vector to match image dimensions
    image.resize(height, vector<RGB>(width));

    // Iterate through each pixel (stbi_load stores RGB in a 1D array)
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int index = (i * width + j) * 3; // Each pixel has 3 channels (RGB)
            image[i][j] = {data[index], data[index + 1], data[index + 2]};
        }
    }

    // Free image data after processing
    stbi_image_free(data);
    return true;
}

bool errorValidation(const string &errorMethod) {
    // List of valid error calculation methods
    const vector<string> validMethods = {"variance", "mad", "mean absolute deviation", "max pixel difference", "mpd", "entropy", "ssim"};
    return find(validMethods.begin(), validMethods.end(), errorMethod) == validMethods.end();
}

bool isValidThreshold(const string &errorMethod, float threshold) {
    if (errorMethod == "variance") {
        return threshold > 0 && threshold <= 65025;
    } else if (errorMethod == "mad" || errorMethod == "mean absolute deviation") {
        return threshold > 0 && threshold <= 255;
    } else if (errorMethod == "mpd") {
        return threshold >= 0 && threshold <= 255;
    } else if (errorMethod == "entropy") {
        return threshold >= 0 && threshold <= 8;
    } else if (errorMethod == "ssim"){
        return threshold >= -1 && threshold <= 1;
    }
    else{
        cerr << "Threshold is not in valid range." << endl;
        return false;
    }
}

// Function to handle input and process the image
void inputHandler(string &inputImagePath, vector<vector<RGB>> &image, string &errorMethod,
                  float &threshold, int &minBlockSize, float &targetCompression, string &outputImagePath) {
    cout << "Enter input image path: ";
    cin >> inputImagePath;
    while (!fileExists(inputImagePath)) {
        cout << "File not found."<<endl;
        cout << "Enter input image path: ";
        cin >> inputImagePath;
    }

    // TODO: CHECK IF DIR DOESN'T MESS WITH THE ROOT DIR OF THE DEVICE
    cout << "Enter output image path: ";
    cin >> outputImagePath;
    
    cout << "Select error calculation method" << endl<< "(Variance, Mean Absolute Deviation (MAD), Max Pixel Difference, Entropy): " <<endl;
    cin >> errorMethod;
    transform(errorMethod.begin(), errorMethod.end(), errorMethod.begin(),
              [](unsigned char c) { return tolower(c); });
    while(errorValidation(errorMethod)) {
        cout << "Invalid method. Enter again: ";
        cin >> errorMethod;
        transform(errorMethod.begin(), errorMethod.end(), errorMethod.begin(),
                  [](unsigned char c) { return tolower(c); });
    }
    
    cout << "Enter threshold value: ";
    cin >> threshold;
    while (!isValidThreshold(errorMethod, threshold)) {
        cout << "Threshold is not in valid range." << endl;
        cout << "Enter threshold value: ";
        cin >> threshold;
    }

    cout << "Enter minimum block size: ";
    cin >> minBlockSize;
    while (minBlockSize <= 1) {
        cout << "Block size must be greater than 1."<<endl;
        cout << "Enter minimum block size: ";
        cin >> minBlockSize;
    }


    // INI TEH BONUS
    cout << "Enter target compression percentage (0-1): ";
    cin >> targetCompression;
    while (targetCompression < 0 || targetCompression > 1) {
        cout << "Not valid." <<endl;
        cout << "Enter target compression percentage (0-1): ";
        cin >> targetCompression;
    }

    // Load and process image into 2D vector
    if (!processImage(inputImagePath, image)) {
        cerr << "Image processing failed. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }
}

// void saveModifiedImage(const vector<vector<RGB>>& image, const string& outputImagePath) {
//     if (image.empty() || image[0].empty()) {
//         cerr << "Error: Empty image data. Cannot save.\n";
//         return;
//     }

//     int height = image.size();
//     int width = image[0].size();

//     // Create a flat buffer for image data (RGB format)
//     vector<uint8_t> data(height * width * 3);

//     for (int i = 0; i < height; ++i) {
//         for (int j = 0; j < width; ++j) {
//             const RGB& pixel = image[i][j];
//             int index = (i * width + j) * 3;
//             data[index + 0] = min(pixel.r + 50, 255); // R
//             data[index + 1] = min(pixel.g + 50, 255); // G
//             data[index + 2] = min(pixel.b + 50, 255); // B
//         }
//     }

//     // Write image as PNG
//     if (!stbi_write_png(outputImagePath.c_str(), width, height, 3, data.data(), width * 3)) {
//         cerr << "Failed to write image to: " << outputImagePath << endl;
//     } else {
//         cout << "Image successfully saved to: " << outputImagePath << endl;
//     }
// }

void saveCompressedImage(const std::vector<std::vector<RGB>>& image, const std::string& outputImagePath) {
    if (image.empty() || image[0].empty()) {
        std::cerr << "Error: Empty image data. Cannot save.\n";
        return;
    }

    const int height = image.size();
    const int width = image[0].size();

    // Create a flat buffer for image data (RGB format)
    std::vector<uint8_t> data(height * width * 3);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            const RGB& pixel = image[i][j];
            int index = (i * width + j) * 3;
            data[index + 0] = pixel.r; // R
            data[index + 1] = pixel.g; // G
            data[index + 2] = pixel.b; // B
        }
    }

    // Write image as PNG
    if (!stbi_write_png(outputImagePath.c_str(), width, height, 3, data.data(), width * 3)) {
        std::cerr << "Failed to write image to: " << outputImagePath << std::endl;
    } else {
        std::cout << "Compressed image saved to: " << outputImagePath << std::endl;
    }
}
