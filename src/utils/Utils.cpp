#define STB_IMAGE_IMPLEMENTATION
#include <bits/stdc++.h>
#include "../includes/stb_image.h"
using namespace std;
#include "Utils.hpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../includes/stb_image_write.h"

// mengecek apakah file sudah ada atau belum
bool fileExists(const string &filename) {
    ifstream file(filename);
    return file.good();
}

float highestThreshold(const string& errorMethod){
    if(errorMethod == "1"){
        return 65025.0;
    }
    else if(errorMethod=="2"){
        return 255.0;
    }
    else if(errorMethod=="3"){
        return 255.0;
    }
    else if(errorMethod=="4"){
        return 8.0;
    }
    else{
        return 1.0;
    }
}

float lowestThreshold(const string& errorMethod){
    if(errorMethod == "1"){
        return 0.0;
    }
    else if(errorMethod=="2"){
        return 0.0;
    }
    else if(errorMethod=="3"){
        return 0.0;
    }
    else if(errorMethod=="4"){
        return 0.0;
    }
    else{
        return 0.0;
    }
}


// validasi extention file
bool hasValidExtension(const string& filename) {
    size_t dotPos = filename.find_last_of('.');
    if (dotPos == string::npos || dotPos == filename.length() - 1) {
        return false; 
    }

    string ext = filename.substr(dotPos + 1);
    transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    return ext == "png" || ext == "jpg" || ext == "jpeg" || ext == "bmp";
}


// helper function to trim leading and trailing whitespace
string trim(const string &s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    size_t end = s.find_last_not_of(" \t\n\r");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}

// helper function to Get non-empty line input
string getNonEmptyLine(const string &prompt) {
    string input;
    do {
        cout << prompt;
        getline(cin, input);
        input = trim(input);
    } while (input.empty());
    return input;
}


// function to process image into 2D vector of RGB using stb_image.h
bool processImage(const string &imagePath, vector<vector<RGB>> &image) {
    int width, height, channels;

    // Load image using stb_image (returns raw pixel data)
    unsigned char *data = stbi_load(imagePath.c_str(), &width, &height, &channels, 3);
    if (!data) {
        cerr << "Error: Could not load image: " << imagePath << endl;
        return false;
    }

    // resize vector to match image dimensions
    image.resize(height, vector<RGB>(width));

    // store RGB ke array
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int index = (i * width + j) * 3; // Each pixel has 3 channels (RGB)
            image[i][j] = {data[index], data[index + 1], data[index + 2]};
        }
    }

    // fee image data after processing
    stbi_image_free(data);
    return true;
}

bool isValidErrorMethod(const string &errorMethod) {
    // opsi perhitungan error
    const vector<string> validMethods = {"1", "2", "3", "4", "5"};
    return find(validMethods.begin(), validMethods.end(), errorMethod) == validMethods.end();
}

// validasi threshold
bool isValidThreshold(const string &errorMethod, float threshold) {
    if (errorMethod == "1") {
        return threshold > 0 && threshold <= 65025;
    } else if (errorMethod == "2") {
        return threshold > 0 && threshold <= 255;
    } else if (errorMethod == "3") {
        return threshold >= 0 && threshold <= 255;
    } else if (errorMethod == "4") {
        return threshold >= 0 && threshold <= 8;
    } else if (errorMethod == "5"){
        return threshold > 0 && threshold < 1;
    }
    else {
        cerr << "Threshold is not in valid range." << endl;
        return false;
    }
}

// mencari ukuran dari file gambar
long long getFileSize(const std::string& path) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file) return -1; 
    return file.tellg();  
}

// menghandle semua kebutuhan input
void inputHandler(string &inputImagePath, vector<vector<RGB>> &image, string &errorMethod,
                  float &threshold, int &minBlockSize, float &targetCompression, string &outputImagePath) {
    cout << R"(
 ____  __  ___  ____  _  _  ____  ____      
(  _ \(  )/ __)(_  _)/ )( \(  _ \(  __)   
 ) __/ )(( (__   )(  ) \/ ( )   / ) _)   
(__)  (__)\___) (__) \____/(__\_)(____)  
                        )" <<endl;
    cout << R"(
  ___  __   _  _  ____  ____  ____  ____  ____  __  __   __ _ 
 / __)/  \ ( \/ )(  _ \(  _ \(  __)/ ___)/ ___)(  )/  \ (  ( \
( (__(  O )/ \/ \ ) __/ )   / ) _) \___ \\___ \ )((  O )/    /
 \___)\__/ \_)(_/(__)  (__\_)(____)(____/(____/(__)\__/ \_)__)
    )"<<endl;
    cout << "\n==============================================================\n" << endl;
    // Input image path
    cout << "Enter input image path (including the extension) " << endl;
    cout << "Valid extensions: .png, .jpg, .jpeg, .bmp" << endl << endl;

    while (true) {
        inputImagePath = getNonEmptyLine("Image input path: ");
        if (!fileExists(inputImagePath))
            cout << "File not found.\n";
        else if (!hasValidExtension(inputImagePath))
            cout << "Invalid file extension. Valid extensions: .png, .jpg, .jpeg, .bmp\n";
        else
            break;
    }

    cout << "\n==============================================================\n" << endl;
    // Output image path
    cout << "Enter output image path (including the extension) " << endl;
    cout << "Valid extensions: .png, .jpg, .jpeg, .bmp" << endl;
    cout << "Output path cannot be the same as input path" << endl;

    while (true) {
        outputImagePath = getNonEmptyLine("Output image path: ");
    
        if (!hasValidExtension(outputImagePath)) {
            cout << "\nInvalid or missing file extension. Please enter a path with one of the following extensions: .png, .jpg, .jpeg, .bmp\n\n";
            continue;
        }

        if (outputImagePath == inputImagePath) {
            cout << "\nOutput path cannot be the same as input path. Please enter a different path.\n\n";
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
    
    cout << "\n==============================================================\n" << endl;
    // error calculation method
    cout << "Select error calculation method (choose the number)" << endl << endl;
    cout <<  "1. Variance" << endl;
    cout <<  "2. Mean Absolute Deviation (MAD)" << endl;
    cout <<  "3. Max Pixel Difference" << endl;
    cout <<  "4. Entropy" << endl;
    cout <<  "5. SSIM" << endl;
    cout << "\n==============================================================\n" << endl;


    while (true) {
        errorMethod = getNonEmptyLine("Error calculation method: ");
        transform(errorMethod.begin(), errorMethod.end(), errorMethod.begin(), ::tolower);
        if (!isValidErrorMethod(errorMethod)) break;
        cout << "\nInvalid method. Try again.\n";
    }

    cout << endl;
    
    // threshold value
    while (true) {
        cout << "Enter threshold value: ";
        string line;
        getline(cin, line);
        stringstream ss(line);
        if (ss >> threshold && isValidThreshold(errorMethod, threshold)) break;
        cout << "\nInvalid input. Please enter a valid float value for threshold.\n\n";
    }
    cout << endl;


    // minimum block size
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
    cout << "\n==============================================================\n" << endl;

    //mengubah gambar menjadi dua dimensi
    if (!processImage(inputImagePath, image)) {
        cerr << "Image processing failed. Exiting..." << endl;
        exit(EXIT_FAILURE);
    }
}

// menyimpan gambar setelah melalui proses divide conquer
void saveCompressedImage(const std::vector<std::vector<RGB>>& image, const std::string& outputImagePath) {
    if (image.empty() || image[0].empty()) {
        std::cerr << "Error: Empty image data. Cannot save.\n";
        return;
    }

    const int height = image.size();
    const int width = image[0].size();

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

    if (!stbi_write_png(outputImagePath.c_str(), width, height, 3, data.data(), width * 3)) {
        std::cerr << "Failed to write image to: " << outputImagePath << std::endl;
    }
}

// bonus percentage
float standardPercentageCompression(
    std::vector<std::vector<RGB>>& image,
    const std::string& inputImagePath,
    const std::string& outputImagePath,
    const std::string& errorMethod,
    int minBlockSize,
    float targetCompression,
    int& maxDepth,
    int& nodeCount
) {
    float low = lowestThreshold(errorMethod);
    float high = highestThreshold(errorMethod);
    float bestThreshold = high;
    float tolerance = 0.01f;
    float precision = 0.001f; // berhenti jika selisih low dan high sudah sangat kecil

    std::vector<std::vector<RGB>> processedImage;

    while ((high - low) > precision) {
        processedImage = image;
        float mid = (low + high) / 2.0f;

        QuadTree qt;
        qt.buildTree(processedImage, mid, errorMethod, minBlockSize);
        qt.reconstructImage(processedImage);

        saveCompressedImage(processedImage, outputImagePath);

        long long inputSize = getFileSize(inputImagePath);
        long long outputSize = getFileSize(outputImagePath);
        float achievedCompression = 1.0f - (float(outputSize) / float(inputSize));

        float diff = std::abs(achievedCompression - targetCompression);

        if (diff <= tolerance) {
            bestThreshold = mid;
            maxDepth = qt.maxDepth;
            nodeCount = qt.nodeCount;
            break;
        }

        if (achievedCompression > targetCompression) {
            high = mid;
        } else {
            low = mid;
        }

        bestThreshold = mid;
        maxDepth = qt.maxDepth;
        nodeCount = qt.nodeCount;
    }

    return bestThreshold;
}


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
) {
    float low = 0.0f;
    float high = 1.0f;
    float bestThreshold = high;
    float tolerance = 0.01f;
    float precision = 0.001f;

    std::vector<std::vector<RGB>> processedImage;

    while ((high - low) > precision) {
        processedImage = image1;
        float mid = (low + high) / 2.0f;

        QuadTree qt;
        qt.buildTree(processedImage, image2, mid, errorMethod, minBlockSize);
        qt.reconstructImage(processedImage);

        saveCompressedImage(processedImage, outputImagePath);

        long long inputSize = getFileSize(inputImagePath);
        long long outputSize = getFileSize(outputImagePath);
        float achievedCompression = 1.0f - float(outputSize) / float(inputSize);

        float diff = std::abs(achievedCompression - targetCompression);

        if (diff <= tolerance) {
            bestThreshold = mid;
            maxDepth = qt.maxDepth;
            nodeCount = qt.nodeCount;
            break;
        }

        // Koreksi arah pencarian
        if (achievedCompression < targetCompression) {
            high = mid; // masih terlalu kecil → kompresi belum cukup → turunkan threshold
        } else {
            low = mid; // kompresi terlalu tinggi → threshold bisa naikkan dikit
        }

        bestThreshold = mid;
        maxDepth = qt.maxDepth;
        nodeCount = qt.nodeCount;
    }

    return bestThreshold;
}

// menghandle output terkait informasi dari hasil kompresi gambar
void outputHandler(const string &outputImagePath, const string &inputImagePath, int maxDepth, int nodeCount, std::chrono::milliseconds duration){
    long long inputSize = getFileSize(inputImagePath)/1024;
    long long outputSize = getFileSize(outputImagePath)/1024;
    cout << "\n==============================================================\n" << endl;
    cout << "Output image successfully rendered to: " << outputImagePath << endl;
    cout << "Compression execution duration: " << duration.count() << " ms" << endl;
    cout << "Input image size: " << inputSize << " KB" << endl;
    cout << "Output image size: " << outputSize << " KB" << endl;
    cout << "Compression ratio: " << (1.0 - (float(outputSize) / float(inputSize))) * 100 << "% reduction" << endl;
    cout << "Max depth of quadtree: " << maxDepth << endl;
    cout << "Total nodes in quadtree: " << nodeCount << endl << endl;
    cout << "\n==============================================================\n" << endl;
}