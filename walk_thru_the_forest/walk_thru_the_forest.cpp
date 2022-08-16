#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int m;                                      // m = number of paths
int n;                                      // n = number of intersections ( 1 < N <= 1000) )
int distances[1001];                        // distances from the root for index 1-1000 (0 is meaningless)
int paths[1001];                            // number of paths connecting to index
vector<pair<int, int>> connections[1001];   // array of vectors storing pairs in form (distance, index)

class maxHeap {
public:
    vector<pair<int, int>> heap;
    int size;

    maxHeap() {
        heap = vector<pair<int, int>>();
        heap.push_back(make_pair(0,0));
        size = 0;
    }

    // getter functions for indices of parent, left, right

    // return -1 if root
    const int parent(const int child) {
        return (child / 2 == 0 ? -1 : child / 2);
    }

    // return -1 if index out of range (no child exists)
    const int left(const int parent) {
        return (2 * parent > size ? -1 : 2 * parent);
    }

    // return -1 if index out of range (no child exists)
    const int right(const int parent) {
        return (2 * parent + 1 > size ? -1 : 2 * parent + 1);
    }

    const bool empty() {
        return size == 0;
    }

    // swap two heap elements with indices x and y
    void swap(int x, int y) {
        pair<int, int> tmp = heap[x];
        heap[x] = heap[y];
        heap[y] = tmp;
    }

    int max(int index_a, int index_b) {
        if ((index_a <= 0 || index_a > size) && (index_b <= 0 || index_b > size))
            return 0;
        else if (index_a <= 0 || index_a > size)
            return index_b;
        else if (index_b <= 0 || index_b > size)
            return index_a;
        else if (heap[index_a].first > heap[index_b].first)
            return index_a;
        else
            return index_b;
    }

    // add new element to heap
    void insert(const int data, const int data2) {
        // add insert at the "back" of tree
        // to maintain completeness
        heap.push_back(make_pair(data, data2));

        // fix any potential violations of heap property
        bubbleUp(++size);
    }

    // fix heap property upward from index i
    void bubbleUp(const int i) {
        // start at i and recursively go up while violations exist
        if (i > 0 && parent(i) >= 0 && heap[parent(i)].first < heap[i].first) {
            // swap i and parent node
            swap(i, parent(i));

            // recursively call parent
            bubbleUp(parent(i));
        }
    }

    // fix heap property downward from index i
    void bubbleDown(const int i) {
        int largerChild = left(i);
        int smallerChild = right(i);

        largerChild = max(largerChild, smallerChild);

        // continue on while the larger child
        // exists and there is a violation
        if (largerChild > 0 && heap[largerChild].first > heap[i].first) {
            // swap node at index i with the larger of its children
            swap(i, largerChild);

            // recursively call the larger child
            bubbleDown(largerChild);
        }

    }

    pair<int, int> pop() {
        pair<int, int> deleteVal;

        if (size > 0) {
            deleteVal = heap[1];
            // swap root with last element
            swap(1, size);

            // remove what was the root and decrement size
            heap.pop_back();
            --size;

            // bubble down from new root
            bubbleDown(1);
        }

        return deleteVal;
    }

    const pair<int, int> peek() {
        return (size > 0 ? heap[1] : make_pair(0, 0));
    }
};

void findPaths(int startIndex) {
    int currentIndex, connectionIndex, distance, nodeDistance;

    // we add pairs (index, distance) to the max heap
    maxHeap heap;

    // insert starting node (home) to heap with distance 0 from home
    heap.insert(startIndex, 0);

    // initialize distances array to maximum possible distance
    for (size_t i = 1; i <= n; i++) 
        distances[i] = 2147483647;

    // distance from home (starting index) to itself is 0
    // so we set it to 0
    distances[startIndex] = 0;

    // heap is empty once all paths have been traversed
    while (!heap.empty()) {
        // in the heap, first element of pair is the index, second is its distance from home
        currentIndex = heap.peek().first;
        distance = heap.peek().second;

        // remove element from heap
        heap.pop();

        // check if distance home from current node is at least as far as we have
        // traveled (from the start = node 2)
        if (distances[currentIndex] >= distance) {
            // go through each of the connections to the current node
            for (size_t i = 0; i < connections[currentIndex].size(); ++i) {
                // set connectionIndex to the node currentIndex is connected to
                connectionIndex = connections[currentIndex][i].first;

                // nodeDistance is the distance from current to connection
                nodeDistance = connections[currentIndex][i].second;

                // check if to distance from connected node -> home is at least the 
                // distance from the current node -> home + distance between the nodes
                if (distances[connectionIndex] > distances[currentIndex] + nodeDistance) {
                    // update the distance of the connected node (add length of edge that connects)
                    distances[connectionIndex] = distances[currentIndex] + nodeDistance;
                    // add node and distance to heap
                    heap.insert(connectionIndex, distances[connectionIndex]);
                }
            }
        }

    }
}

// initially we set all paths to -1, with the exception
// of the last node which will have value 1
int getNumberOfPaths(int currentIndex) {
    // base case: either we reached office (paths[1] = 1) or a visited node
    if (paths[currentIndex] != -1)
        return paths[currentIndex];

    // otherwise: count number of paths using connections array and
    // distances array
    int numPaths = 0;
    int connectionIndex;

    // for each node connected to the current node
    for (int i = connections[currentIndex].size() - 1; i >= 0; --i) {
        // get index of connected node
        connectionIndex = connections[currentIndex][i].first;

        // check if connected node is further from
        // the start (home = node 2) than current node
        if (distances[connectionIndex] > distances[currentIndex]) 
            numPaths += getNumberOfPaths(connectionIndex);
    }

    // update paths array with new number of paths for this node
    paths[currentIndex] = numPaths;

    return numPaths;
}

int main() {
    cin >> n;

    // while we don't receive a 0 as input for n
    while (n != 0) {

        cin >> m;

        int currentIndex, connectionIndex, distance;

        for (size_t i = 1; i <= m; i++) {
            cin >> currentIndex >> connectionIndex >> distance;

            connections[currentIndex].push_back(make_pair(connectionIndex, distance));
            connections[connectionIndex].push_back(make_pair(currentIndex, distance));
        }

        findPaths(2);
        
        for (size_t i = 0; i < 1001; ++i)
            paths[i] = -1;

        paths[1] = 1;

        cout << getNumberOfPaths(2) << endl;

        for (int i = 1; i <= n; i++) 
            connections[i].clear();

        cin >> n;

    }

    return 0;
}