// Copyright 2025 NNTU-CS
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>
#include "tree.h"

int main() {
    // Пример работы
    std::vector<char> in = {'1', '2', '3'};
    PMTree tree(in);

    std::cout << "All permutations:" << std::endl;
    std::vector<std::vector<char>> perms = getAllPerms(tree);
    for (size_t i = 0; i < perms.size(); ++i) {
        std::cout << i + 1 << ": ";
        for (char c : perms[i]) std::cout << c;
        std::cout << std::endl;
    }

    std::cout << "\nGet by number:" << std::endl;
    std::vector<char> p1 = getPerm1(tree, 2);
    std::vector<char> p2 = getPerm2(tree, 3);
    
    std::cout << "getPerm1(2): ";
    for (char c : p1) std::cout << c;
    std::cout << std::endl;
    
    std::cout << "getPerm2(3): ";
    for (char c : p2) std::cout << c;
    std::cout << std::endl;

    // Эксперимент для графика
    std::ofstream data("result/data.csv");
    data << "n,getAllPerms,getPerm1,getPerm2" << std::endl;

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int n = 3; n <= 10; ++n) {
        std::vector<char> chars;
        for (int i = 0; i < n; ++i) {
            chars.push_back('a' + i);
        }
        
        PMTree t(chars);
        
        int totalPerms = 1;
        for (int i = 2; i <= n; ++i) totalPerms *= i;
        std::uniform_int_distribution<> dis(1, totalPerms);
        int randNum = dis(gen);
        
        auto start = std::chrono::high_resolution_clock::now();
        t.getAllPerms();
        auto end = std::chrono::high_resolution_clock::now();
        auto timeAll = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        
        start = std::chrono::high_resolution_clock::now();
        t.getPerm1(randNum);
        end = std::chrono::high_resolution_clock::now();
        auto time1 = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        
        start = std::chrono::high_resolution_clock::now();
        t.getPerm2(randNum);
        end = std::chrono::high_resolution_clock::now();
        auto time2 = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        
        data << n << "," << timeAll << "," << time1 << "," << time2 << std::endl;
        std::cout << "n=" << n << " done" << std::endl;
    }
    
    data.close();
    
    // Python скрипт для графика
    std::ofstream plot("result/plot.py");
    plot << "import pandas as pd\n"
         << "import matplotlib.pyplot as plt\n"
         << "import numpy as np\n\n"
         << "df = pd.read_csv('data.csv')\n"
         << "plt.figure(figsize=(10, 6))\n"
         << "plt.plot(df['n'], df['getAllPerms'], 'ro-', label='getAllPerms')\n"
         << "plt.plot(df['n'], df['getPerm1'], 'bs-', label='getPerm1 (перебор)')\n"
         << "plt.plot(df['n'], df['getPerm2'], 'g^-', label='getPerm2 (навигация)')\n"
         << "plt.yscale('log')\n"
         << "plt.xlabel('n (количество элементов)')\n"
         << "plt.ylabel('Время (микросекунды)')\n"
         << "plt.title('Зависимость времени выполнения от n (лог. масштаб)')\n"
         << "plt.legend()\n"
         << "plt.grid(True, alpha=0.3)\n"
         << "plt.savefig('plot.png', dpi=150, bbox_inches='tight')\n"
         << "plt.show()\n";
    plot.close();

    return 0;
}
