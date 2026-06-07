// Copyright 2025 NNTU-CS
#ifndef INCLUDE_ALG_H_
#define INCLUDE_ALG_H_

#include <vector>
#include "tree.h"

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_ALG_H_
