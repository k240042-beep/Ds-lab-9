#include <iostream>
using namespace std;

struct Node {
    int key;
    Node *left, *right;
    int height;
    Node(int val) : key(val), left(NULL), right(NULL), height(1) {}
};

int height(Node* n) {
    return (n == NULL) ? 0 : n->height;
}

int getBalance(Node* n) {
    return (n == NULL) ? 0 : height(n->left) - height(n->right);
}

Node* rightRotate(Node* y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x; 
}

Node* leftRotate(Node* x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y; 
}

Node* convertToAVL(Node* root) {
    if (!root) return root;

    root->left = convertToAVL(root->left);
    root->right = convertToAVL(root->right);

    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = getBalance(root);


    if (balance > 1) {
       
        if (getBalance(root->left) < 0)
            root->left = leftRotate(root->left);
        return rightRotate(root);
    }

 
    if (balance < -1) {
        
        if (getBalance(root->right) > 0)
            root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root; 
}


Node* buildTreeA() {
    Node* root = new Node(10);
    root->left = new Node(6);
    root->left->left = new Node(4);
    root->left->right = new Node(8);
    return root;
}


Node* buildTreeB() {
    Node* root = new Node(10);
    root->right = new Node(16);
    root->right->left = new Node(12);
    root->right->right = new Node(18);
    return root;
}

void preOrder(Node* root) {
    if (!root) return;
    cout << root->key << " ";
    preOrder(root->left);
    preOrder(root->right);
}

int main() {
    Node* A = buildTreeA();
    Node* B = buildTreeB();

    A = convertToAVL(A);
    B = convertToAVL(B);

    cout << "AVL (Tree A): ";
    preOrder(A);
    cout << "\nAVL (Tree B): ";
    preOrder(B);
}
