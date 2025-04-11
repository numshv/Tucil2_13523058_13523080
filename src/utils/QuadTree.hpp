#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <vector>
#include "QuadTreeNode.hpp"
#include "ErrorMeasures.hpp"

class QuadTree {
public:
    QuadTreeNode* root;
    int maxDepth;   // Kedalaman maksimum pohon
    int nodeCount;  // Jumlah simpul dalam quadtree

    QuadTree();
    ~QuadTree();

    void buildTree(const std::vector<std::vector<RGB>>& image, float threshold, const std::string& errorMethod, int minBlockSize);
    void buildTree(const std::vector<std::vector<RGB>>& image1, const std::vector<std::vector<RGB>>& image2, float threshold, const std::string& errorMethod, int minBlockSize);

    void destroyTree(QuadTreeNode* node);

    // ini baru, buat simpan gambarnya supaya ngga besar
    void reconstructImage(std::vector<std::vector<RGB>>& image);
    void reconstructRecursive(QuadTreeNode* node, std::vector<std::vector<RGB>>& image);

};

#endif
