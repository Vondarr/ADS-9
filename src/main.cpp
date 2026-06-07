// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <cstdint>
#include <ctime>
#include <fstream>
#include "tree.h"

int main() {
  std::vector<char> src = {'1', '2', '3'};
  PMTree myTree(src);

  std::vector<std::vector<char>> perms = getAllPerms(myTree);
  for (std::vector<char>& perm : perms) {
    for (char sym : perm) std::cout << sym;
    std::cout << "\n";
  }

  std::srand(static_cast<unsigned>(std::time(0)));
  std::ofstream out("result/data.csv");
  out << "n,all,p1,p2\n";

  for (int sz = 1; sz <= 10; ++sz) {
    std::vector<char> letters;
    for (int idx = 0; idx < sz; ++idx)
      letters.push_back(static_cast<char>('1' + idx));

    PMTree myTree2(letters);
    int64_t factVal = 1;
    for (int mult = 2; mult <= sz; ++mult) factVal *= mult;
    int target = std::rand() % factVal + 1;

    auto start1 = std::chrono::high_resolution_clock::now();
    getAllPerms(myTree2);
    auto end1 = std::chrono::high_resolution_clock::now();

    auto start2 = std::chrono::high_resolution_clock::now();
    getPerm1(myTree2, target);
    auto end2 = std::chrono::high_resolution_clock::now();

    auto start3 = std::chrono::high_resolution_clock::now();
    getPerm2(myTree2, target);
    auto end3 = std::chrono::high_resolution_clock::now();

    double timeAll = std::chrono::duration<double, std::micro>(end1 - start1).count();
    double timeP1 = std::chrono::duration<double, std::micro>(end2 - start2).count();
    double timeP2 = std::chrono::duration<double, std::micro>(end3 - start3).count();

    out << sz << "," << timeAll << "," << timeP1 << "," << timeP2 << "\n";
    std::cout << sz << "\t" << timeAll << "\t" << timeP1 << "\t" << timeP2 << "\n";
  }
  out.close();
  return 0;
}
