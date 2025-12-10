#pragma once
#include <string>

using std::string;

class WasteCategoryTree {
private:
    struct Node {
        string category;
        Node* left;
        Node* right;
        Node(const string& c) : category(c), left(nullptr), right(nullptr) {}
    };
    Node* root;

    Node* insertNode(Node* node, const string& category);
    void inOrder(Node* node) const;
    void clear(Node* node);

public:
    WasteCategoryTree();
    ~WasteCategoryTree();
    void insert(const string& category);
    void display() const; 
};
