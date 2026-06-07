// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <algorithm>

class PMTree {
 public:
  struct Node {
    char val;
    std::vector<Node*> down;
    explicit Node(char v) : val(v) {}
  };

  Node* top;

  explicit PMTree(const std::vector<char>& src) {
    top = new Node('\0');
    std::vector<char> sortedSrc = src;
    std::sort(sortedSrc.begin(), sortedSrc.end());
    construct(top, sortedSrc);
  }

  ~PMTree() { clear(top); }

 private:
  void construct(Node* curNode, std::vector<char> remaining) {
    for (size_t idx = 0; idx < remaining.size(); ++idx) {
      Node* newNode = new Node(remaining[idx]);
      curNode->down.push_back(newNode);
      std::vector<char> nextRemaining = remaining;
      nextRemaining.erase(nextRemaining.begin() + idx);
      construct(newNode, nextRemaining);
    }
  }

  void clear(Node* curNode) {
    if (!curNode) return;
    for (Node* child : curNode->down) clear(child);
    delete curNode;
  }
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
