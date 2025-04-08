#ifndef QUADTREE_NODE_HPP
#define QUADTREE_NODE_HPP

#include <vector>
#include "RGB.hpp"
#include "errormeasures.hpp"


struct QuadTreeNode {
    // Pointer ke anak
    QuadTreeNode* topLeft;
    QuadTreeNode* topRight;
    QuadTreeNode* bottomLeft;
    QuadTreeNode* bottomRight;

    int x, y, width, height;
    bool isLeaf;
    RGB meanColor; // Representasi warna rata-rata simpul

    // Constructor
    QuadTreeNode();

    // Rekursif membangun quadtree
    void buildNode(QuadTreeNode*& node, const std::vector<std::vector<RGB>>& image,
                        int x, int y, int width, int height, float threshold, int currentDepth,
                        int& maxDepth, int& nodeCount, const std::string& errorMethod, int minBlockSize);
   
};

#endif 
