#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <iostream>
#include <vector>
#include "RGB.hpp"
#include "ErrorMeasures.hpp"

struct QuadTreeNode {
    // Pointer ke anak
    QuadTreeNode* topLeft;
    QuadTreeNode* topRight;
    QuadTreeNode* bottomLeft;
    QuadTreeNode* bottomRight;

    // Properti simpul
    int x, y, width, height;
    bool isLeaf;

    // Constructor (hanya deklarasi di sini)
    QuadTreeNode();

    // Ini yang rekursif yaw
    void buildQuadtree(QuadTreeNode*& node, const vector<vector<RGB>>& image, int x, int y, int width, int height, float threshold);
};



#endif