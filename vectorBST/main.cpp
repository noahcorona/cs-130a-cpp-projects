#include <iostream>
#include <vector>

using namespace std;

class BST {
public:
    vector<int> tree;

    BST() {
        // we have 1024 MB, 4 bytes per int -> ~256,000,000 max size of vector
        tree = vector<int>(100000000);
    }

    BST(int size) {
        tree = vector<int>(size);
    }

    int insert(const int key) {
        int depth = 0, i = 0;

        while (tree.at(i) != 0) {
            if (tree.at(i) < key) {
                i = 2 * i + 1;
            } else {
                i = 2 * i;
            }
            
            ++depth;
        }

        tree.at(i) = key;

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