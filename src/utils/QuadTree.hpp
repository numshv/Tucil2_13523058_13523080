#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <vector>
#include "QuadTreeNode.hpp"

class QuadTree {
public:
    QuadTreeNode* root;
    int maxDepth;   // Kedalaman maksimum pohon
    int nodeCount;  // Jumlah simpul dalam quadtree

    QuadTree();
    ~QuadTree();

    void buildTree(const std::vector<std::vector<RGB>>& image, float threshold);
    void destroyTree(QuadTreeNode* node);
};

#endif
