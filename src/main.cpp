// Copyright 2025 NNTU-CS
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>
#include <iomanip>
#include "tree.h"
#include "alg.h"

int main() {
    // Демонстрация для 3 элементов
    std::vector<char> demo = {'1', '2', '3'};
    PermTree demoTree(demo);

    std::cout << "=== Demonstration for 3 elements ===" << std::endl;
    std::vector<std::vector<char>> perms = getAllPerms(demoTree);
    for (size_t i = 0; i < perms.size(); ++i) {
        std::cout << i + 1 << ": ";
        for (char c : perms[i]) std::cout << c;
        std::cout << std::endl;
    }

    std::cout << "\ngetPerm1(1): ";
    for (char c : getPerm1(demoTree, 1)) std::cout << c;
    std::cout << std::endl;

    std::cout << "getPerm2(3): ";
    for (char c : getPerm2(demoTree, 3)) std::cout << c;
    std::cout << std::endl;

    std::cout << "\n=== Performance experiment ===" << std::endl;
    std::cout << "n\tgetAllPerms(ms)\tgetPerm1(ms)\tgetPerm2(ms)" << std::endl;

    std::ofstream report("result/timing.csv");
    report << "n,getAllPerms_us,getPerm1_us,getPerm2_us" << std::endl;

    for (int n = 3; n <= 9; ++n) {
        std::vector<char> symbols;
        for (int i = 0; i < n; ++i) {
            symbols.push_back(static_cast<char>('a' + i));
        }

        PermTree woodland(symbols);

        int totalWays = 1;
        for (int i = 2; i <= n; ++i) totalWays *= i;
        std::mt19937 rng(12345);
        std::uniform_int_distribution<> selector(1, totalWays);
        int lucky = selector(rng);

        auto start = std::chrono::high_resolution_clock::now();
        getAllPerms(woodland);
        auto mid1 = std::chrono::high_resolution_clock::now();
        getPerm1(woodland, lucky);
        auto mid2 = std::chrono::high_resolution_clock::now();
        getPerm2(woodland, lucky);
        auto finish = std::chrono::high_resolution_clock::now();

        double phase1 = std::chrono::duration<double, std::milli>(mid1 - start).count();
        double phase2 = std::chrono::duration<double, std::milli>(mid2 - mid1).count();
        double phase3 = std::chrono::duration<double, std::milli>(finish - mid2).count();

        std::cout << n << "\t" << phase1 << "\t\t" << phase2 << "\t\t" << phase3 << std::endl;
        report << n << "," << phase1 * 1000 << "," << phase2 * 1000 << "," << phase3 * 1000 << std::endl;
    }

    report.close();
    std::cout << "\nResults saved to result/timing.csv" << std::endl;

    return 0;
}
