#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
    int size; 
    Node(int k) : key(k), left(NULL), right(NULL), height(1), size(1) {}
};

int height(Node* n) { return n ? n->height : 0; }
int getSize(Node* n) { return n ? n->size : 0; }

int balanceFactor(Node* n) {
    return height(n->left) - height(n->right);
}

void updateNode(Node* n) {
    if (!n) return;
    n->height = max(height(n->left), height(n->right)) + 1;
    n->size = getSize(n->left) + getSize(n->right) + 1;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateNode(y);
    updateNode(x);
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateNode(x);
    updateNode(y);
    return y;
}

Node* insert(Node* root, int key) {
    if (!root) return new Node(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);

    updateNode(root);

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

int kthSmallest(Node* root, int k) {
    if (!root) return -1;

    int leftSize = getSize(root->left);

    if (k == leftSize + 1)
        return root->key;
    else if (k <= leftSize)
        return kthSmallest(root->left, k);
    else
        return kthSmallest(root->right, k - leftSize - 1);
}

int kthLargest(Node* root, int k) {
    return kthSmallest(root, getSize(root) - k + 1);
}

int main() {
    Node* root = NULL;
    int arr[] = {10, 5, 15, 3, 7, 12};
    for(int i = 0; i < 6; i++)
        root = insert(root, arr[i]);

    int k = 3;

    int kthSmall = kthSmallest(root, k);
    int kthLarge = kthLargest(root, k);

    cout << "K = " << k << endl;
    cout << k << "th Smallest Key: " << kthSmall << endl;
    cout << k << "th Largest Key: " << kthLarge << endl;
    cout << "Left Subtree Height: " << height(root->left) << endl;
    cout << "Right Subtree Height: " << height(root->right) << endl;

    return 0;
}
