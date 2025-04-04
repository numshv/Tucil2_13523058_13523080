#include "QuadTreeNode.hpp"
#include <iostream>
#include <vector>
#include <cmath>

QuadTreeNode::QuadTreeNode()
    : topLeft(nullptr), topRight(nullptr), bottomLeft(nullptr), bottomRight(nullptr),
      x(0), y(0), width(0), height(0), isLeaf(true), meanColor{0, 0, 0} {}

// TODO: Implement the buildNode function
void QuadTreeNode::buildNode(QuadTreeNode*& node, const std::vector<std::vector<RGB>>& image,
  int x, int y, int width, int height, float threshold,
  int& maxDepth, int& nodeCount, const std::string& errorMethod)
  {
      if (!node) return;

      node->x = x;
      node->y = y;
      node->width = width;
      node->height = height;

      bool isUniform = errorValidation(errorMethod, image, x, y, width, height, threshold, node->meanColor);

      if (isUniform || width <= 4 || height <= 4){
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
      buildNode(node->topLeft, image, x, y, halfWidth, halfHeight, threshold, maxDepth, nodeCount, errorMethod);

      node->topRight = new QuadTreeNode();
      buildNode(node->topRight, image, x + halfWidth, y, rightWidth, halfHeight, threshold, maxDepth, nodeCount, errorMethod);

      node->bottomLeft = new QuadTreeNode();
      buildNode(node->bottomLeft, image, x, y + halfHeight, halfWidth, bottomHeight, threshold, maxDepth, nodeCount, errorMethod);

      node->bottomRight = new QuadTreeNode();
      buildNode(node->bottomRight, image, x + halfWidth, y + halfHeight, rightWidth, bottomHeight, threshold, maxDepth, nodeCount, errorMethod);
      
      nodeCount ++;
  }
