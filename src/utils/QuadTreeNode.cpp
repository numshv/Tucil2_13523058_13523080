#include "QuadTreeNode.hpp"
#include <iostream>
#include <vector>
#include <cmath>

QuadTreeNode::QuadTreeNode()
    : topLeft(nullptr), topRight(nullptr), bottomLeft(nullptr), bottomRight(nullptr),
      x(0), y(0), width(0), height(0), isLeaf(true), meanColor{0, 0, 0} {}

// TODO: Implement the buildNode function