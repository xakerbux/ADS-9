// Copyright 2025 NNTU-CS
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>
#include "tree.h"

int main() {
    std::vector<char> init = {'1', '2', '3'};
    PMTree example(init);

    std::vector<std::vector<char>> variants = getAllPerms(example);
    for (const auto& seq : variants) {
        for (char c : seq) std::cout << c;
        std::cout << "  ";
    }
    std::cout << "\n\n";

    std::vector<char> first = getPerm1(example, 1);
    std::cout << "getPerm1(1): ";
    for (char c : first) std::cout << c;
    std::cout << std::endl;

    std::vector<char> second = getPerm2(example, 2);
    std::cout << "getPerm2(2): ";
    for (char c : second) std::cout << c;
    std::cout << std::endl;

    return 0;
}
