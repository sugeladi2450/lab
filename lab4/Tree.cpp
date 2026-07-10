#include "Tree.h"
#include <algorithm>
#include <cassert>
#include <limits>

#include "Calculator.h"
#include "Comparator.h"
#include "TreeNode.h"

using namespace std;

struct DimComparator {
  int dim;
  DimComparator(int d) : dim(d) {}
  bool operator()(const TreeNode *a, const TreeNode *b) const {
    assert(a->dimension() == b->dimension() && a->dimension() > dim);
    return isLessThan((*a)[dim], (*b)[dim]);
  }
};

TreeNode* TwoDimenTree::buildTree(vector<TreeNode*>& nodes, int depth) {
  if (nodes.empty()) return nullptr;
  int dim = depth % 2;
  sort(nodes.begin(), nodes.end(), DimComparator(dim));
  int mid = nodes.size() / 2;
  TreeNode* node = nodes[mid];
  vector<TreeNode*> leftNodes(nodes.begin(), nodes.begin() + mid);
  vector<TreeNode*> rightNodes(nodes.begin() + mid + 1, nodes.end());
  node->left = buildTree(leftNodes, depth + 1);
  node->right = buildTree(rightNodes, depth + 1);
  return node;
}

void TwoDimenTree::findNearestHelper(TreeNode* cur, const TreeNode& target, int depth,
                                      TreeNode*& guess, double& bestDist,
                                      const DistanceCalculator* calculator) {
  if (cur == nullptr) return;
  int dim = depth % 2;
  double dist = calculator->calculateDistance(*cur, target);
  if (isLessThan(dist, bestDist)) {
    bestDist = dist;
    guess = cur;
  } else if (isEqual(dist, bestDist)) {
    if (isLessThan((*cur)[0], (*guess)[0]) ||
        (isEqual((*cur)[0], (*guess)[0]) && isLessThan((*cur)[1], (*guess)[1]))) {
      guess = cur;
    }
  }
  TreeNode* first;
  TreeNode* second;
  if (isLessThan(target[dim], (*cur)[dim])) {
    first = cur->left;
    second = cur->right;
  } else {
    first = cur->right;
    second = cur->left;
  }
  findNearestHelper(first, target, depth + 1, guess, bestDist, calculator);
  double vertDist = calculator->calculateVerticalDistance(*cur, target, dim);
  if (isLessThan(vertDist, bestDist)) {
    findNearestHelper(second, target, depth + 1, guess, bestDist, calculator);
  }
}

void TwoDimenTree::deleteTree(TreeNode* node) {
  if (node == nullptr) return;
  deleteTree(node->left);
  deleteTree(node->right);
  delete node;
}

TwoDimenTree::TwoDimenTree() {
  root = nullptr;
  calculator = nullptr;
}

TwoDimenTree::~TwoDimenTree() {
  deleteTree(root);
  delete calculator;
}

TreeNode *TwoDimenTree::findNearestNode(const TreeNode &target) {
  TreeNode* guess = nullptr;
  double bestDist = numeric_limits<double>::infinity();
  findNearestHelper(root, target, 0, guess, bestDist, calculator);
  return guess;
}

istream &operator>>(istream &in, TwoDimenTree &tree) {
  string distType;
  in >> distType;
  if (distType == "Manhattan") {
    tree.calculator = new ManhattanDistanceCalculator();
  } else if (distType == "Euclidean") {
    tree.calculator = new EuclideanDistanceCalculator();
  } else if (distType == "Haversine") {
    tree.calculator = new HaversineDistanceCalculator();
  }
  int M;
  in >> M;
  vector<TreeNode*> nodes;
  for (int i = 0; i < M; i++) {
    double x, y;
    in >> x >> y;
    TreeNode* node = new TreeNode({x, y});
    nodes.push_back(node);
  }
  tree.root = TwoDimenTree::buildTree(nodes, 0);
  return in;
}