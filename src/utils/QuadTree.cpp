#include "QuadTree.hpp"
#include <iostream>
#include <vector>
#include <cmath>

QuadTreeNode::QuadTreeNode(): x(0), y(0), width(0), height(0), isLeaf(true),
                              topLeft(nullptr), topRight(nullptr),bottomLeft(nullptr), bottomRight(nullptr) {}

// TODO: Implement the buildQuadtree function
