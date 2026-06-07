// Copyright 2022 NNTU-CS
#include "tree.h"

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <locale>
#include <vector>

namespace {

int64_t fact(int n) {
  int64_t f = 1;
  for (int i = 2; i <= n; ++i) f *= i;
  return f;
}

void traverse(PMTree::Node* node, std::vector<char>& cur,
             std::vector<std::vector<char>>& out) {
  if (node->down.empty()) {
    out.push_back(cur);
    return;
  }
  for (PMTree::Node* child : node->down) {
    cur.push_back(child->val);
    traverse(child, cur, out);
    cur.pop_back();
  }
}

void navigate(PMTree::Node* node, int num, std::vector<char>& res) {
  if (node->down.empty()) return;
  int k = static_cast<int>(node->down.size());
  int64_t sub = fact(k - 1);
  int idx = static_cast<int>((num - 1) / sub);
  int rem = static_cast<int>((num - 1) % sub) + 1;
  if (idx < 0 || idx >= k) return;
  PMTree::Node* chosen = node->down[idx];
  res.push_back(chosen->val);
  navigate(chosen, rem, res);
}

}  // namespace

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
  std::vector<std::vector<char>> out;
  std::vector<char> cur;
  if (tree.top) traverse(tree.top, cur, out);
  return out;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  std::vector<std::vector<char>> all = getAllPerms(tree);
  if (num < 1 || num > static_cast<int>(all.size())) return {};
  return all[num - 1];
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  std::vector<char> res;
  if (!tree.top || tree.top->down.empty()) return {};
  int k = static_cast<int>(tree.top->down.size());
  int64_t total = fact(k);
  if (num < 1 || num > total) return {};
  navigate(tree.top, num, res);
  return res;
}
