#include <stdexcept>

#include "TreeNode.h"

TreeNode::TreeNode(initializer_list<double> coords) {
  coordinates = coords;
  left = nullptr;
  right = nullptr;
}

const double &TreeNode::operator[](int index) const {
  return coordinates[index];
}

int TreeNode::dimension() const {
  return coordinates.size();
}

const vector<double> &TreeNode::getCoordinates() const {
  return coordinates;
}

TreeNode::~TreeNode() {}