#include "QuadTree.hpp"
#include "ErrorMeasures.hpp"

QuadTree::QuadTree() : root(nullptr), maxDepth(0), nodeCount(0) {}

QuadTree::~QuadTree() {
    destroyTree(root);
}

void QuadTree::destroyTree(QuadTreeNode* node) {
    if (node == nullptr) return;

    // Rekursif hapus semua anak
    destroyTree(node->topLeft);
    destroyTree(node->topRight);
    destroyTree(node->bottomLeft);
    destroyTree(node->bottomRight);

    delete node;
}
void QuadTree::buildTree(const std::vector<std::vector<RGB>>& image, float threshold, const std::string& errorMethod){
    root = new QuadTreeNode();
    maxDepth = 0;
    nodeCount = 0;

    root->buildNode(root, image, 0, 0, image[0].size(), image.size(), threshold, maxDepth, nodeCount, errorMethod);
}

// ini baru, buat simpan gambarnya supaya ngga besar
void QuadTree::reconstructImage(std::vector<std::vector<RGB>>& image) {
    if (!root) return;
    reconstructRecursive(root, image);
}

void QuadTree::reconstructRecursive(QuadTreeNode* node, std::vector<std::vector<RGB>>& image) {
    if (node->isLeaf) {
        // Fill the entire region with mean color
        for (int y = node->y; y < node->y + node->height; ++y) {
            for (int x = node->x; x < node->x + node->width; ++x) {
                image[y][x] = node->meanColor;
            }
        }
    } else {
        reconstructRecursive(node->topLeft, image);
        reconstructRecursive(node->topRight, image);
        reconstructRecursive(node->bottomLeft, image);
        reconstructRecursive(node->bottomRight, image);
    }
}
