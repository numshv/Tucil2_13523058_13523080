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
    cout << "[DEBUG] Checking file existence: " << filename << " => " << (file.good() ? "exists" : "not found") << endl;
    return file.good();
}


// Function to check if the file has a valid image extension
bool hasValidExtension(const string& filename) {
    size_t dotPos = filename.find_last_of('.');
    if (dotPos == string::npos || dotPos == filename.length() - 1) {
        return false; // No extension or ends with a dot
    }

    string ext = filename.substr(dotPos + 1);
    transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    return ext == "png" || ext == "jpg" || ext == "jpeg" || ext == "bmp";
}


// Helper function to Trim leading and trailing whitespace
string trim(const string &s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    size_t end = s.find_last_not_of(" \t\n\r");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}

// Helper function to Get non-empty line input
string getNonEmptyLine(const string &prompt) {
    string input;
    do {
        cout << prompt;
        getline(cin, input);
        input = trim(input);
    } while (input.empty());
    return input;
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

bool isValidErrorMethod(const string &errorMethod) {
    // List of valid error calculation methods
    const vector<string> validMethods = {"variance", "mad", "mean absolute deviation", "max pixel difference", "entropy"};
    return find(validMethods.begin(), validMethods.end(), errorMethod) == validMethods.end();
}

bool isValidThreshold(const string &errorMethod, float threshold) {
    if (errorMethod == "variance") {
        return threshold > 0 && threshold <= 65025;
    } else if (errorMethod == "mad" || errorMethod == "mean absolute deviation") {
        return threshold > 0 && threshold <= 255;
    } else if (errorMethod == "max pixel difference") {
        return threshold >= 0 && threshold <= 255;
    } else if (errorMethod == "entropy") {
        return threshold >= 0 && threshold <= 8;
    } else {
        cerr << "Threshold is not in valid range." << endl;
        return false;
    }
}

long long getFileSize(const std::string& path) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file) return -1; // Error opening file
    return file.tellg();  // Returns size in bytes
}

// Function to handle input and process the image
void inputHandler(string &inputImagePath, vector<vector<RGB>> &image, string &errorMethod,
                  float &threshold, int &minBlockSize, float &targetCompression, string &outputImagePath) {

    // Input image path
    cout << "Enter input image path (including the extension) " << endl;
    cout << "Valid extensions: .png, .jpg, .jpeg, .bmp" << endl << endl;

    while (true) {
        inputImagePath = getNonEmptyLine("Image input path: ");
        if (!fileExists(inputImagePath))
            cout << "File not found.\n" << endl;
        else if (!hasValidExtension(inputImagePath))
            cout << "Invalid file extension. Valid extensions: .png, .jpg, .jpeg, .bmp\n";
        else
            break;
    }
    cout << endl;


    // Output image path
    cout << "Enter output image path (including the extension) " << endl;
    cout << "Valid extensions: .png, .jpg, .jpeg, .bmp" << endl << endl;

    while (true) {
        outputImagePath = getNonEmptyLine("Output image path: ");
    
        if (!hasValidExtension(outputImagePath)) {
            cout << "\nInvalid or missing file extension. Please enter a path with one of the following extensions: .png, .jpg, .jpeg, .bmp\n\n";
            continue;
        }
    
        if (fileExists(outputImagePath)) {
            cout << "\nFile already exists. Overwrite? (y/n): ";
            string response;
            getline(cin, response);
            if (!response.empty() && tolower(response[0]) == 'y') break;
        } else {
            break;
        }
    }

    cout << endl;
    

    // Error calculation method
    cout << "Select error calculation method" << endl<< "(Variance, Mean Absolute Deviation (MAD), Max Pixel Difference, Entropy)" <<endl << endl;

    while (true) {
        errorMethod = getNonEmptyLine("Error calculation method: ");
        transform(errorMethod.begin(), errorMethod.end(), errorMethod.begin(), ::tolower);
        if (!isValidErrorMethod(errorMethod)) break;
        cout << "\nInvalid method. Try again.\n";
    }

    cout << endl;
    
    // Threshold value
    while (true) {
        cout << "Enter threshold value: ";
        string line;
        getline(cin, line);
        stringstream ss(line);
        if (ss >> threshold && isValidThreshold(errorMethod, threshold)) break;
        cout << "\nInvalid input. Please enter a valid float value for threshold.\n\n";
    }
    cout << endl;


    // Minimum block size
    while (true) {
        cout << "Enter minimum block size: ";
        string line;
        getline(cin, line);
        stringstream ss(line);
        if (ss >> minBlockSize && minBlockSize > 1) break;
        cout << "\nInvalid input. Please enter an integer greater than 1 for block size.\n\n";
    }
    cout << endl;


    // target compression percentage
    while (true) {
        cout << "Enter target compression percentage (0-1): ";
        string line;
        getline(cin, line);
        stringstream ss(line);
        if (ss >> targetCompression && targetCompression >= 0.0f && targetCompression <= 1.0f) break;
        cout << "\nInvalid input. Please enter a float between 0 and 1.\n\n";
    }
    cout << endl;

    // Load and process image into 2D vector
    if (!processImage(inputImagePath, image)) {
        cerr << "Image processing failed. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }
}

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

void outputHandler(const string &outputImagePath, const string &inputImagePath, QuadTree &quadtree, std::chrono::milliseconds duration){
    cout << "\n\n=========================\n" << endl;
    cout << "Output image successfully rendered to: " << outputImagePath << endl;
    cout << "Compression execution duration: " << duration.count() << " ms" << endl;
    cout << "Input image size: " << getFileSize(inputImagePath) / 1024 << " KB" << endl;
    cout << "Output image size: " << getFileSize(outputImagePath) / 1024 << " KB" << endl;
    cout << "Compression ratio: " << (float)getFileSize(outputImagePath) / getFileSize(inputImagePath) * 100 << "%" << endl;
    cout << "Max depth of quadtree: " << quadtree.maxDepth << endl << endl;
    cout << "Total nodes in quadtree: " << quadtree.nodeCount << endl;
    cout << "=========================\n";
}