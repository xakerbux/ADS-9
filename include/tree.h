// Copyright 2025 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

class PermTree {
 private:
    struct TreeNode {
        char letter;
        std::vector<TreeNode*> branches;
        explicit TreeNode(char ch) : letter(ch) {}
    };

    TreeNode* head;
    std::vector<char> source;

    void expand(TreeNode* node, std::vector<char> available) {
        if (available.empty()) return;
        for (size_t i = 0; i < available.size(); ++i) {
            TreeNode* child = new TreeNode(available[i]);
            node->branches.push_back(child);
            std::vector<char> rest;
            for (size_t j = 0; j < available.size(); ++j) {
                if (j != i) rest.push_back(available[j]);
            }
            expand(child, rest);
        }
    }

    void cleanup(TreeNode* node) {
        if (!node) return;
        for (TreeNode* child : node->branches) {
            cleanup(child);
        }
        delete node;
    }

 public:
    explicit PermTree(const std::vector<char>& items) : source(items) {
        head = new TreeNode(0);
        expand(head, source);
    }

    ~PermTree() {
        cleanup(head);
    }

    TreeNode* getRoot() const {
        return head;
    }

    int getSize() const {
        return source.size();
    }
};

#endif  // INCLUDE_TREE_H_
