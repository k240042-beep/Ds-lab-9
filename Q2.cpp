#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
    Node(int k) : key(k), left(NULL), right(NULL), height(1) {}
};

int height(Node* n) {
    return n ? n->height : 0;
}

int balanceFactor(Node* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

Node* insert(Node* root, int key) {
    if (!root) return new Node(key);
    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    root->height = max(height(root->left), height(root->right)) + 1;
    int bf = balanceFactor(root);
    if (bf > 1 && key < root->left->key)
        return rightRotate(root);
    if (bf < -1 && key > root->right->key)
        return leftRotate(root);
    if (bf > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (bf < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void preOrder(Node* root) {
    if (!root) return;
    cout << root->key << " ";
    preOrder(root->left);
    preOrder(root->right);
}

int main() {
    Node* root = NULL;
    int students[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++)
        root = insert(root, students[i]);
    root = insert(root, 15);
    preOrder(root);
}
