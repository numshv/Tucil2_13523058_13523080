#ifndef ERRORMEASURES_HPP
#define ERRORMEASURES_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstdint>
#include "RGB.hpp"

using namespace std;


// Function declarations
bool variance(const vector<vector<RGB>>& image, int x, int y, int width, int height, float threshold, RGB &mean);  
bool mad(const vector<vector<RGB>>& image, int x, int y, int width, int height, float threshold, RGB &mean);  
bool mpd(const vector<vector<RGB>>& image, int x, int y, int width, int height, float threshold, RGB &mean);  
bool entropy(const vector<vector<RGB>>& image, int x, int y, int width, int height, float threshold, RGB &mean);  

bool errorValidation(const string &errorMethod, const vector<vector<RGB>>& image, int x, int y, int width, int height, float threshold, RGB &mean);

#endif
