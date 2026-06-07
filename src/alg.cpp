// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "tree.h"
#include <vector>
#include <algorithm>

namespace {

long long fact(int n) {
  long long res = 1;
  for (int i = 2; i <= n; ++i) res *= i;
  return res;
}

void walk(PMTree::Node* node, std::vector<char>& curr,
          std::vector<std::vector<char>>& accum) {
  if (node->down.empty()) {
    accum.push_back(curr);
    return;
  }
  for (PMTree::Node* nxt : node->down) {
    curr.push_back(nxt->val);
    walk(nxt, curr, accum);
    curr.pop_back();
  }
}

void goDown(PMTree::Node* node, int order, std::vector<char>& out) {
  if (node->down.empty()) return;
  int branchCount = static_cast<int>(node->down.size());
  long long perBranch = fact(branchCount - 1);
  int chosenIdx = static_cast<int>((order - 1) / perBranch);
  int nextOrder = static_cast<int>((order - 1) % perBranch) + 1;
  if (chosenIdx < 0 || chosenIdx >= branchCount) return;
  PMTree::Node* selected = node->down[chosenIdx];
  out.push_back(selected->val);
  goDown(selected, nextOrder, out);
}

}  // namespace

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
  std::vector<std::vector<char>> result;
  std::vector<char> current;
  if (tree.top) walk(tree.top, current, result);
  return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  std::vector<std::vector<char>> all = getAllPerms(tree);
  if (num < 1 || num > static_cast<int>(all.size())) return {};
  return all[num - 1];
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  std::vector<char> result;
  if (!tree.top || tree.top->down.empty()) return {};
  int totalBranches = static_cast<int>(tree.top->down.size());
  long long totalPerms = fact(totalBranches);
  if (num < 1 || num > totalPerms) return {};
  goDown(tree.top, num, result);
  return result;
}
