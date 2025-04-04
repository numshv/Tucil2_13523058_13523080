#include "QuadTree.hpp"

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

// TODO: Implement the buildTree function
