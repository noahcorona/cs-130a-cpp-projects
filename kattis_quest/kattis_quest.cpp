#include <iostream>
#include <string>
#include <vector>

using namespace std;

class maxHeap {
public:
    vector<int> heap;

    maxHeap() {
        heap = vector<int>();
        heap.push_back(0);
    }

    // getter functions for indices of parent, left, right

    // return -1 if root
    const int parent(const int child) {
        return (child / 2 == 0 ? -1 : child / 2);
    }

    // return -1 if index out of range (no child exists)
    const int left(const int parent) {
        return (2 * parent >= heap.size() ? -1 : 2 * parent);
    }

    // return -1 if index out of range (no child exists)
    const int right(const int parent) {
        return (2 * parent + 1 >= heap.size() ? -1 : 2 * parent + 1);
    }

    int max(int index_a, int index_b) {
        if (index_a <= 0 && index_b <= 0)
            return 0;
        else if (index_a <= 0)
            return index_b;
        else if (index_b <= 0)
            return index_a;
        else if (heap[index_a] >= heap[index_b])
            return index_a;
        else
            return index_b;
    }

    // add new element to heap
    void insert(const int data) {
        // add insert at the "back" of tree
        // to maintain completeness
        heap.push_back(data);

        // fix any potential violations of heap property
        bubbleUp(heap.size() - 1);
    }

    // remove the root, swap with last element in heap
    // and restore heap property by bubbling down from
    // the root
    int popMax() {
        int tmp = -1;

        if (heap.size() > 1) {
            // swap root with last element
            tmp = heap[1];
            heap[1] = heap.back();
            heap.pop_back();
            if(heap.size() > 1)
                bubbleDown(1);
        }

        return tmp;
    }

    // verify heap property holds for our MAX heap
    // if not, swap elements upward and recursively
    // continue upward until there is no violation
    void bubbleUp(const int i) {
        // note that heap[0] is NOT the root, it has no use
        if (i > 0 && parent(i) > 0 && heap[parent(i)] < heap[i]) {
            // swap tmp and parent node
            int tmp = heap[i];
            heap[i] = heap[(parent(i))];
            heap[parent(i)] = tmp;

            // recursively call parent
            bubbleUp(parent(i));
        }
    }

    // verify heap property holds for our MAX heap
    // if not, swap elements and recursively
    // continue downward until there is no violation

    // this is a max heap. we want to ensure 
    // parent > child so we choose the larger
    // child to swap with
    void bubbleDown(const int i) {
        int largerChild = left(i);
        int smallerChild = right(i);

        // get the larger child of the left/right
        // children of i
        largerChild = max(largerChild, smallerChild);
        
        // continue on while the larger child
        // exists and there is a violation
        if (largerChild > 0 && largerChild < heap.size()
            && i < heap.size() && heap[largerChild] > heap[i]) {
            // swap tmp and larger child
            int tmp = heap[i];
            heap[i] = heap[largerChild];
            heap[largerChild] = tmp;

            // recursively call the larger child
            bubbleDown(largerChild);
        }
    }
};

// this class ties together our AVL tree and
// max heap classes, and allows for an easy
// implementation of the QuestLog class
class node {

public:
    node* parent;
    node* left;
    node* right;
    int height;

    int energy;
    maxHeap goldRewards;

    // one node represents all quests that require
    // the same energy, with the max heap of the
    // node containing all of the gold rewards
    node(int newEnergy) {
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        height = 1;

        energy = newEnergy;
        goldRewards = maxHeap();
    }
};

// AVL tree of quests indexed by energy
// the gold rewards are stored as max heap
// for quick access to highest one
class BST {

public:

    node* root;

    BST() {
        root = nullptr;
    }

    // returns address of node with energy E
    // if none exist, returns nullptr
    node* search(const int E) {
        node* temp = root;

        while (temp != nullptr && temp->energy != E) {
            if (temp->energy > E) {
                temp = temp->left;
            } else if(temp->energy < E) {
                temp = temp->right;
            }
        }

        return temp;
    }

    // returns a pointer to the inserted node
    // if node exists with energy E, then this
    // simply returns the address of the existing
    // node (like search)
    node* insert(const int E) {
        node* temp = root;

        // case 1: quest log is empty
        // case 2: node with energy E already exists
        // case 3: node with energy E does not exist
        
        if (temp == nullptr) {
            // case 1
            root = new node(E);
            return root;
        } else {
            node* trail = nullptr;
            
            while (temp != nullptr && temp->energy != E) {
                trail = temp;

                if (temp->energy > E) {
                    temp = temp->left;
                } else if (temp->energy < E) {
                    temp = temp->right;
                }
            }

            if (temp != nullptr) {
                // case 2
                // temp now points to node with energy E
                return temp;
            } else {
                // case 3
                // temp points to nullptr
                // trail points to node we will insert on
                node* newNode = new node(E);
                if (trail->energy < E) {
                    trail->right = newNode;
                } else {
                    trail->left = newNode;
                }
                
                newNode->parent = trail;

                return newNode;
            }

            return temp;
        }
    }

    void remove(const int E) {
        node* temp = root;
        node* trail = nullptr;

        while (temp != nullptr && temp->energy != E) {
            trail = temp;

            if (temp->energy > E)
                temp = temp->left;
            else
                temp = temp->right;
        }

        // case 1: no node exists with energy E in tree
        if (temp == nullptr) {
            return;
        }
        // case 2: node is a leaf
        else if (temp->right == nullptr && temp->left == nullptr) {
            if (temp == root) {
                root = nullptr;
            } else {
                if (temp->parent->left == temp) {
                    temp->parent->left = nullptr;
                } else {
                    temp->parent->right = nullptr;
                }
            }

            delete temp;
        }
        // case 3: node has only a left child
        else if (temp->right == nullptr) {
            if (temp == root)
                root = temp->left;
            else {
                if (temp->parent->left == temp) {
                    temp->parent->left = temp->left;    // fix temp's parent to point left child to temp's left child
                    temp->left->parent = temp->parent;  // fix temp's left child to point to parent of temp
                } else {
                    temp->parent->right = temp->left;   // fix temp's parent to point right child to temp's left child
                    temp->left->parent = temp->parent;  // fix temp's left child to point to parent of temp
                }
            }

            delete temp;
        } 
        // case 3: node has only a right child
        else if (temp->left == nullptr) {
            if (temp == root)
                root = temp->right;
            else {
                if (temp->parent->left == temp) {
                    temp->parent->left = temp->right;    // fix temp's parent to point left child to temp's right child
                    temp->right->parent = temp->parent;  // fix temp's left child to point to parent of temp
                } else {
                    temp->parent->right = temp->right;   // fix temp's parent to point right child to temp's right child
                    temp->right->parent = temp->parent;  // fix temp's right child to point to parent of temp
                }
            }

            delete temp;
        }
        // case 4: node has 2 children
        // find the inorder successor, given we know node
        else {
            node* trail = nullptr; // will point to inorder successor
            node* deleteNode = temp; // points to note to be deleted

            // we know temp must have a right child
            temp = temp->right;

            while (temp->left != nullptr) {
                trail = temp;
                temp = temp->left;
            }

            // now temp points to inorder successor
            // trail points to its parent
            // and deleteNode to the node to be deleted
            
            if (trail != nullptr)
                trail->left = temp->right;
            else
                deleteNode->right = temp->right;

            // we delete temp, the inorder successor,
            // swapping the data of the nodes
            deleteNode->goldRewards = temp->goldRewards;
            
            delete temp;
        }
    }
    

    // returns the greatest entry less than E
    // or -1 if there is no such quest
    int greatestLessThanEqTo(node* root, const int E) {
        if (root == nullptr)
            return -1;
        if (root->energy == E)
            return E;
        else if (root->energy <= E) {
            int x = greatestLessThanEqTo(root->right, E);
            if (x == -1)
                return root->energy;
            else
                return x;
        }
        else if (root->energy > E) {
            return greatestLessThanEqTo(root->left, E);
        }
        else return -1;
    }

};

// stores the AVL tree that stores quests by energy
// each node contains max heap of gold rewards
class questLog {

public:

    BST quests;

    // adds quest to questLog
    void add(int energy, int gold) {
        // this creates a node for quests
        // with given energy and points
        // temp to the inserted node
        // or the already-existing node
        node* temp = quests.insert(energy);

        // then add G to the heap at this node
        temp->goldRewards.insert(gold);
    }

    // returns the amount of gold received from completing quest
    int doQuestWithEnergy(int energy) {
        // get node that represents quests with given energy
        node* temp = quests.search(energy);

        int goldEarned = 0;

        // make sure quest exists
        if (temp != nullptr) {
            
            // add gold and remove quest from heap
            goldEarned = temp->goldRewards.popMax();

            // if heap is now effectively empty, remove node
            // from our tree
            if (temp->goldRewards.heap.size() == 1) {
                quests.remove(energy);
            }
        }

        return goldEarned;
    }

    // returns gold accumulated from session
    int completeSession(int X) {
        int goldEarned = 0;

        while (X > 0) {
            /*
            // get the longest quest we can afford with energy X
            node* longestQuest = quests.greatestLessThanEqTo(quests.root, X);

            // get energy this quest takes
            int E = longestQuest->energy;
            */

            int E = quests.greatestLessThanEqTo(quests.root, X);

            // complete quest if we have energy
            if (E > 0 && E < X) {
                // we have energy to complete the quest
                goldEarned += doQuestWithEnergy(E);

                // reduce our remaining energy
                X -= E;
            }
            else 
                break; // no such quests
        }

        return goldEarned;
    }
};

int main() {
    int n;
    cin >> n;

    questLog ql;

    for(int i = 0; i < n; ++i) {
        string cmd;
        cin >> cmd;

        if (cmd == "add") {
            // add quest to quest log
            int energy, gold;
            cin >> energy >> gold;

            ql.add(energy, gold);
        } else {
            // query and complete session
            int energy;
            cin >> energy;

            cout << ql.completeSession(energy) << "\n";
        }
    }
}