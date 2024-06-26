#include <iostream>
#include <string>

using namespace std;

class AVLNode {
public:
    string key;
    string value;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(const string& k, const string& v) : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLNode* root;

    int height(AVLNode* node) {
        return node ? node->height : 0;
    }

    int balanceFactor(AVLNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void updateHeight(AVLNode* node) {
        if (node) {
            node->height = 1 + max(height(node->left), height(node->right));
        }
    }

    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    AVLNode* balance(AVLNode* node) {
        updateHeight(node);

        int balance = balanceFactor(node);

        if (balance > 1) {
            if (balanceFactor(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }
        if (balance < -1) {
            if (balanceFactor(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }

        return node;
    }

    AVLNode* insert(AVLNode* node, const string& key, const string& value) {
        if (!node) {
            return new AVLNode(key, value);
        }

        if (key < node->key) {
            node->left = insert(node->left, key, value);
        } else if (key > node->key) {
            node->right = insert(node->right, key, value);
        } else {
            node->value = value;
        }

        return balance(node);
    }

    AVLNode* minValueNode(AVLNode* node) {
        AVLNode* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    AVLNode* remove(AVLNode* node, const string& key) {
        if (!node) {
            return node;
        }

        if (key < node->key) {
            node->left = remove(node->left, key);
        } else if (key > node->key) {
            node->right = remove(node->right, key);
        } else {
            if (!node->left || !node->right) {
                AVLNode* temp = node->left ? node->left : node->right;

                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }

                delete temp;
            } else {
                AVLNode* temp = minValueNode(node->right);
                node->key = temp->key;
                node->value = temp->value;
                node->right = remove(node->right, temp->key);
            }
        }

        if (!node) {
            return node;
        }

        return balance(node);
    }

    AVLNode* search(AVLNode* node, const string& key) {
        if (!node || node->key == key) {
            return node;
        }

        if (key < node->key) {
            return search(node->left, key);
        }

        return search(node->right, key);
    }

    void inOrder(AVLNode* root) {
        if (root) {
            inOrder(root->left);
            cout << root->key << ": " << root->value << endl;
            inOrder(root->right);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(const string& key, const string& value) {
        root = insert(root, key, value);
    }

    void remove(const string& key) {
        root = remove(root, key);
    }

    string search(const string& key) {
        AVLNode* result = search(root, key);
        return result ? result->value : "Not found";
    }

    void printInOrder() {
        inOrder(root);
    }
};

int main() {
    AVLTree tree;
    tree.insert("apple", "10");
    tree.insert("banana", "20");
    tree.insert("orange", "30");

    cout << "Search apple: " << tree.search("apple") << endl;
    cout << "Search banana: " << tree.search("banana") << endl;
    cout << "Search grape: " << tree.search("grape") << endl;

    tree.remove("banana");
    cout << "Search banana after removal: " << tree.search("banana") << endl;

    cout << "In-order traversal of AVL tree:" << endl;
    tree.printInOrder();

    return 0;
}
