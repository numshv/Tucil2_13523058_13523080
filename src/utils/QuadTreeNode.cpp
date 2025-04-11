#include "QuadTreeNode.hpp"
#include <iostream>
#include <vector>
#include <cmath>

QuadTreeNode::QuadTreeNode()
    : topLeft(nullptr), topRight(nullptr), bottomLeft(nullptr), bottomRight(nullptr),
      x(0), y(0), width(0), height(0), isLeaf(true), meanColor{0, 0, 0} {}

void QuadTreeNode::buildNode(QuadTreeNode*& node, const std::vector<std::vector<RGB>>& image,
    int x, int y, int width, int height, float threshold,
    int currentDepth, int& maxDepth, int& nodeCount, const std::string& errorMethod, int minBlockSize)
{
    // membangun node pada quadtree, objektifnya adalah jika blok masih belum seragam maka blok akan dibagi menjadi empat
    // hal tersebut dilakukan terus menerus secara rekursif hingg blok tersebut seragam atau ukurannya tidak kurang dari minBlockSize
    if (!node) return;

    //inisialisasi
    node->x = x;
    node->y = y;
    node->width = width;
    node->height = height;

    // update maxDepth
    if (currentDepth > maxDepth) {
        maxDepth = currentDepth;
    }

    bool isUniform = errorValidation(errorMethod, image, x, y, width, height, threshold, node->meanColor);

    if (isUniform || width <= minBlockSize || height <= minBlockSize){
        node->isLeaf = true;
        node->topLeft = nullptr;
        node->topRight = nullptr;
        node->bottomLeft = nullptr;
        node->bottomRight = nullptr;
        nodeCount ++;
        return;
    }

    // not uniform, split
    node->isLeaf = false;
    int halfWidth = width / 2;
    int halfHeight = height / 2;
    int rightWidth = width - halfWidth;
    int bottomHeight = height - halfHeight;

    node->topLeft = new QuadTreeNode();
    buildNode(node->topLeft, image, x, y, halfWidth, halfHeight, threshold, currentDepth + 1, maxDepth, nodeCount, errorMethod, minBlockSize);

    node->topRight = new QuadTreeNode();
    buildNode(node->topRight, image, x + halfWidth, y, rightWidth, halfHeight, threshold, currentDepth + 1, maxDepth, nodeCount, errorMethod, minBlockSize);

    node->bottomLeft = new QuadTreeNode();
    buildNode(node->bottomLeft, image, x, y + halfHeight, halfWidth, bottomHeight, threshold, currentDepth + 1, maxDepth, nodeCount, errorMethod, minBlockSize);

    node->bottomRight = new QuadTreeNode();
    buildNode(node->bottomRight, image, x + halfWidth, y + halfHeight, rightWidth, bottomHeight, threshold, currentDepth + 1, maxDepth, nodeCount, errorMethod, minBlockSize);

    nodeCount ++;
}

void QuadTreeNode::buildNodeSSIM(QuadTreeNode*& node, const std::vector<std::vector<RGB>>& image1, const std::vector<std::vector<RGB>>& image2,
    int x, int y, int width, int height, float threshold, int currentDepth, int& maxDepth, int& nodeCount, int minBlockSize)
  {
    // membangun node pada quadtree, objektifnya adalah jika blok masih belum seragam maka blok akan dibagi menjadi empat
    // hal tersebut dilakukan terus menerus secara rekursif hingg blok tersebut seragam atau ukurannya tidak kurang dari minBlockSize
    // untuk SSIM ini akan comparing blok ori dengan blok hasil kompresi
    if (!node) return;

    node->x = x;
    node->y = y;
    node->width = width;
    node->height = height;

    // update maxDepth
    if (currentDepth > maxDepth) {
        maxDepth = currentDepth;
    }

    bool isUniform = ssim(image1, x, y, width, height, threshold, node->meanColor);

    if (isUniform || width <= minBlockSize || height <= minBlockSize){
        node->isLeaf = true;
        node->topLeft = nullptr;
        node->topRight = nullptr;
        node->bottomLeft = nullptr;
        node->bottomRight = nullptr;
        nodeCount ++;
        return;
    }
    // jika nggak uniform, split node jadi empat bagian
    node->isLeaf = false;
    int halfWidth = width / 2;
    int halfHeight = height / 2;
    int rightWidth = width - halfWidth;
    int bottomHeight = height - halfHeight;

    // rekursif membuat empat anak
    node->topLeft = new QuadTreeNode();
    buildNodeSSIM(node->topLeft, image1, image2, x, y, halfWidth, halfHeight, threshold, currentDepth + 1, maxDepth, nodeCount, minBlockSize);

    node->topRight = new QuadTreeNode();
    buildNodeSSIM(node->topRight, image1, image2, x + halfWidth, y, rightWidth, halfHeight, threshold, currentDepth + 1, maxDepth, nodeCount, minBlockSize);

    node->bottomLeft = new QuadTreeNode();
    buildNodeSSIM(node->bottomLeft, image1, image2, x, y + halfHeight, halfWidth, bottomHeight, threshold, currentDepth + 1, maxDepth, nodeCount, minBlockSize);

    node->bottomRight = new QuadTreeNode();
    buildNodeSSIM(node->bottomRight, image1, image2, x + halfWidth, y + halfHeight, rightWidth, bottomHeight, threshold, currentDepth + 1, maxDepth, nodeCount, minBlockSize);

    nodeCount ++;
}

