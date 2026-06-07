// Copyright 2025 NNTU-CS
#include <vector>
#include "tree.h"

static void factorial(int n, int& result) {
    result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
}

static void collectAll(PermTree::TreeNode* node,
                       std::vector<char>& path,
                       std::vector<std::vector<char>>& storage) {
    if (!node) return;
    if (node->letter != 0) {
        path.push_back(node->letter);
    }
    if (node->branches.empty()) {
        storage.push_back(path);
    } else {
        for (auto* child : node->branches) {
            collectAll(child, path, storage);
        }
    }
    if (node->letter != 0) {
        path.pop_back();
    }
}

static void navigateTo(PermTree::TreeNode* node,
                       std::vector<char>& path,
                       int target,
                       int& counter,
                       std::vector<char>& output,
                       bool& finished) {
    if (finished) return;
    if (node->letter != 0) {
        path.push_back(node->letter);
    }
    if (node->branches.empty()) {
        counter++;
        if (counter == target) {
            output = path;
            finished = true;
        }
    } else {
        for (auto* child : node->branches) {
            navigateTo(child, path, target, counter, output, finished);
            if (finished) break;
        }
    }
    if (node->letter != 0) {
        path.pop_back();
    }
}

std::vector<std::vector<char>> getAllPerms(PermTree& plant) {
    std::vector<std::vector<char>> result;
    std::vector<char> buffer;
    for (auto* child : plant.getRoot()->branches) {
        collectAll(child, buffer, result);
    }
    return result;
}

std::vector<char> getPerm1(PermTree& plant, int index) {
    std::vector<std::vector<char>> all = getAllPerms(plant);
    if (index < 1 || index > static_cast<int>(all.size())) {
        return std::vector<char>();
    }
    return all[index - 1];
}

std::vector<char> getPerm2(PermTree& plant, int index) {
    int total = plant.getSize();
    int maxCount;
    factorial(total, maxCount);
    if (index < 1 || index > maxCount) {
        return std::vector<char>();
    }
    std::vector<char> output;
    int counter = 0;
    bool done = false;
    for (auto* child : plant.getRoot()->branches) {
        if (done) break;
        std::vector<char> path;
        navigateTo(child, path, index, counter, output, done);
    }
    return output;
}
