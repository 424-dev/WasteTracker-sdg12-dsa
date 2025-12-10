#include "WasteCategoryTree.h"
#include <iostream>

using std::cout;
using std::endl;

WasteCategoryTree::WasteCategoryTree() : root(nullptr) {}
WasteCategoryTree::~WasteCategoryTree() { clear(root); }

void WasteCategoryTree::clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

WasteCategoryTree::Node* WasteCategoryTree::insertNode(Node* node, const string& category) {
    if (!node) return new Node(category);
    if (category < node->category) node->left = insertNode(node->left, category);
    else if (category > node->category) node->right = insertNode(node->right, category);
    
    return node;
}

void WasteCategoryTree::insert(const string& category) {
    root = insertNode(root, category);
}

void WasteCategoryTree::inOrder(Node* node) const {
    if (!node) return;
    inOrder(node->left);
    cout << node->category << '\n';
    inOrder(node->right);
}

void WasteCategoryTree::display() const {
    if (!root) {
        cout << "No categories.\n";
        return;
    }
    inOrder(root);
}
