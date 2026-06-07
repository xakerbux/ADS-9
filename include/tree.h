// Copyright 2025 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <algorithm>

class PMTree {
 private:
    struct Node {
        char value;
        std::vector<Node*> children;
        explicit Node(char val) : value(val) {}
    };

    Node* root;
    std::vector<char> elements;
    int fact(int n) {
        int result = 1;
        for (int i = 2; i <= n; ++i) result *= i;
        return result;
    }

    void buildTree(Node* node, std::vector<char> remaining) {
        if (remaining.empty()) return;
        std::sort(remaining.begin(), remaining.end());
        for (size_t i = 0; i < remaining.size(); ++i) {
            Node* child = new Node(remaining[i]);
            node->children.push_back(child);
            std::vector<char> newRemaining;
            for (size_t j = 0; j < remaining.size(); ++j) {
                if (j != i) newRemaining.push_back(remaining[j]);
            }
            buildTree(child, newRemaining);
        }
    }

    void getAll(Node* node, std::vector<char>& current,
                std::vector<std::vector<char>>& result) {
        if (!node) return;
        current.push_back(node->value);
        if (node->children.empty()) {
            result.push_back(current);
        } else {
            for (Node* child : node->children) {
                getAll(child, current, result);
            }
        }
        current.pop_back();
    }

    void getPermByNum(Node* node, std::vector<char>& current,
                      int& counter, int target,
                      std::vector<char>& result, bool& found) {
        if (found) return;
        current.push_back(node->value);
        if (node->children.empty()) {
            counter++;
            if (counter == target) {
                result = current;
                found = true;
            }
        } else {
            for (Node* child : node->children) {
                getPermByNum(child, current, counter, target, result, found);
                if (found) break;
            }
        }
        current.pop_back();
    }

    void destroyTree(Node* node) {
        if (!node) return;
        for (Node* child : node->children) {
            destroyTree(child);
        }
        delete node;
    }

 public:
    explicit PMTree(const std::vector<char>& chars) : elements(chars) {
        root = new Node(0);
        buildTree(root, elements);
    }

    ~PMTree() {
        destroyTree(root);
    }

    std::vector<std::vector<char>> getAllPerms() {
        std::vector<std::vector<char>> result;
        for (Node* child : root->children) {
            std::vector<char> current;
            getAll(child, current, result);
        }
        return result;
    }

    std::vector<char> getPerm1(int num) {
        std::vector<std::vector<char>> all = getAllPerms();
        if (num < 1 || num > static_cast<int>(all.size())) {
            return std::vector<char>();
        }
        return all[num - 1];
    }

    std::vector<char> getPerm2(int num) {
        int total = fact(elements.size());
        if (num < 1 || num > total) {
            return std::vector<char>();
        }
        std::vector<char> result;
        int counter = 0;
        bool found = false;
        for (Node* child : root->children) {
            if (found) break;
            std::vector<char> current;
            getPermByNum(child, current, counter, num, result, found);
        }
        return result;
    }
};

#endif  // INCLUDE_TREE_H_
