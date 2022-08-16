#include <iostream>
#include <vector>

using namespace std;

class maxHeap {
public:
    vector<int> heap;
    int size;

    maxHeap() {
        heap = vector<int>();
        heap.push_back(0);
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

    // swap two heap elements with indices x and y
    void swap(int x, int y) {
        int tmp = heap[x];
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
        else if (heap[index_a] > heap[index_b])
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
        bubbleUp(++size);
    }

    // fix heap property upward from index i
    void bubbleUp(const int i) {
        // start at i and recursively go up while violations exist
        if (i > 0 && parent(i) >= 0 && heap[parent(i)] < heap[i]) {
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
        if (largerChild > 0 && heap[largerChild] > heap[i]) {
            // swap node at index i with the larger of its children
            swap(i, largerChild);

            // recursively call the larger child
            bubbleDown(largerChild);
        }

    }

    int pop() {
        int deleteVal = 0;

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

    const int peek() {
        return (size > 0 ? heap[1] : 0);
    }
};

class minHeap {
public:
    vector<int> heap;
    int size;

    minHeap() {
        heap = vector<int>();
        heap.push_back(0);
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

    // swap two heap elements with indices x and y
    void swap(int x, int y) {
        int tmp = heap[x];
        heap[x] = heap[y];
        heap[y] = tmp;
    }

    int min(int index_a, int index_b) {
        if ((index_a <= 0 || index_a > size) && (index_b <= 0 || index_b > size))
            return 0;
        else if (index_a <= 0 || index_a > size)
            return index_b;
        else if (index_b <= 0 || index_b > size)
            return index_a;
        else if (heap[index_a] < heap[index_b])
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
        bubbleUp(++size);
    }

    // fix heap property upward from index i
    void bubbleUp(const int i) {
        // start at i and recursively go up while violations exist
        if (i > 0 && parent(i) >= 0 && heap[parent(i)] > heap[i]) {
            // swap node at index i and its parent
            swap(i, parent(i));

            // recursively call parent
            bubbleUp(parent(i));
        }
    }

    // fix heap property downward from index i
    void bubbleDown(const int i) {
        int largerChild = left(i);
        int smallerChild = right(i);

        smallerChild = min(smallerChild, largerChild);

        // continue on while the smaller child
        // exists and creates is a violation
        if (smallerChild > 0 && heap[smallerChild] < heap[i]) {
            // swap node at index i and smaller child
            swap(i, smallerChild);

            // recursively call the smaller child
            bubbleDown(smallerChild);
        }

    }

    int pop() {
        int deleteVal = 0;

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

    const int peek() {
        return (size > 0 ? heap[1] : 0);
    }
};

// adds the new element and returns the median
const long long int median(int newElement, maxHeap& left, minHeap& right) {

    if (left.size == right.size) {
        left.insert(newElement);
        right.insert(left.pop());
    } else {
        right.insert(newElement);
        left.insert(right.pop());
    }

    if (right.size > left.size)
        return right.peek();
    else
        return (left.peek() + right.peek()) / 2;
}

int main()
{
    int testCases, n, m;
    scanf_s("%d", &testCases);

    // iterate all test cases
    for (int i = 0; i < testCases; ++i) {
        // we make one min and one max heap
        maxHeap left;
        minHeap right;
        long long int sum = 0;

        scanf_s("%d", &n);

        for (int j = 0; j < n; ++j) {
            scanf_s("%d", &m);

            sum += median(m, left, right);
        }

        cout << sum << endl;
    }
}
