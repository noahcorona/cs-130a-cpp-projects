#include <iostream>

using namespace std;

class node {
public:
    node* parent;
    node* left;
    node* right;
    int data;

    node() {
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        data = 0;
    }

    node(int newData, node* newParent) {
        data = newData;
        left = nullptr;
        right = nullptr;
        parent = newParent;
    }
};

class BST {
public:
    node* root;

    BST() {
        root = nullptr;
    }

    int insert(const int key) {
        int depth = 0;
        node* temp = root;
        node* prev = temp;

        // check if we are adding the root
        if (temp == nullptr) {
            root = new node(key, nullptr);
        } else {
            // traverse to open spot
            while (temp != nullptr) {
                prev = temp;

                if (temp->data < key) {
                    temp = temp->right;
                } else {
                    temp = temp->left;
                }

                ++depth;
            }

            // point node's parent to prev
            node* newNode = new node(key, prev);
            
            // point prev's child to the new node
            if (prev->data < key)
                prev->right = newNode;
            else
                prev->left = newNode;
        }

        return depth;
    }
};

int main() {
    int x, count = 0;
    cin >> x;

    BST myBST;

    while (cin >> x) {
        count += myBST.insert(x);
        cout << count << "\n";
    }
}