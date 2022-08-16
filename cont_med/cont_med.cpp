#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class minHeap {
public:
    vector<int> heap;

    // getter functions for node relations
    int parentOf(int i) {
        return (i - 1) / 2;
    }

    int leftOf(int i) {
        return (2 * i + 1);
    }

    int rightOf(int i) {
        return (2 * i + 2);
    }

    // bubble down recursively, selecting smaller child
    // while violation exists
    void bubbleDown(int i) {
        int left = leftOf(i);
        int right = rightOf(i);

        int smallest = i;

        if (left < size() && heap[left] < heap[i]) {
            smallest = left;
        }

        if (right < size() && heap[right] < heap[smallest]) {
            smallest = right;
        }

        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            bubbleDown(smallest);
        }
    }

    // bubble up recursively while violation exists
    void bubbleUp(int i) {
        if (i && heap[parentOf(i)] > heap[i]){
            swap(heap[i], heap[parentOf(i)]);

            bubbleUp(parentOf(i));
        }
    }

    int size() {
        return heap.size();
    }

    // add to spot to maintain completeness then
    // bubble up while violations exist
    void push(int key) {
        heap.push_back(key);

        int index = size() - 1;
        bubbleUp(index);
    }

    // returns popped element of 0 if heap is empty
    int pop() {
        int val = 0;

        if (size() > 0) {
            val = heap[0];
            heap[0] = heap.back();
            heap.pop_back();

            bubbleDown(0);

            return val;
        }

    }

    // returns min element of 0 if heap is empty
    int peek() {
        if (size() == 0) {
            return 0;
        }

        return heap.at(0);
    }
};

class maxHeap {
public:
    vector<int> heap;

    // getter functions for node relations
    int parentOf(int i) {
        return (i - 1) / 2;
    }

    int leftOf(int i) {
        return (2 * i + 1);
    }

    int rightOf(int i) {
        return (2 * i + 2);
    }

    // bubble down recursively, selecting larger child
    // while violation exists
    void bubbleDown(int i) {
        int left = leftOf(i);
        int right = rightOf(i);

        int largest = i;

        if (left < size() && heap[left] > heap[i]) {
            largest = left;
        }

        if (right < size() && heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest != i) {
            swap(heap[i], heap[largest]);
            bubbleDown(largest);
        }
    }

    // bubble up recursively
    void bubbleUp(int i) {
        if (i && heap[parentOf(i)] < heap[i]) {
            swap(heap[i], heap[parentOf(i)]);

            bubbleUp(parentOf(i));
        }
    }

    int size() {
        return heap.size();
    }

    // add to spot to maintain completeness then
    // bubble up while violations exist
    void push(int key) {
        heap.push_back(key);

        int index = size() - 1;
        bubbleUp(index);
    }

    // returns popped element or 0 if heap is empty
    int pop() {
        int val = 0;
        if (size() > 0) {
            val = heap[0];
            heap[0] = heap.back();
            heap.pop_back();

            bubbleDown(0);
        }

        return val;
    }
    
    // returns max element or 0 if heap is empty
    int peek() {
        if (size() == 0) {
            return 0;
        }

        return heap.at(0);
    }
};

// insert element so as to maintain "balance" between left and right
// then returns the median using knowledge of the current balance
const long long int median(int newElement, maxHeap& left, minHeap& right) {

    if (left.size() == right.size()) {
        left.push(newElement);
        right.push(left.pop());
    }
    else {
        right.push(newElement);
        left.push(right.pop());
    }

    if (right.size() > left.size())
        return right.peek();
    else
        return (left.peek() + right.peek()) / 2;
}

int main() {
    int n, m;
    int A[100000];
    scanf_s("%d", &n);

    // iterate all test cases
    for (int i = 0; i < n; ++i) {
        // we make one min and one max heap
        maxHeap left;
        minHeap right;
        long long int sum = 0;

        scanf_s("%d", &m);

        for (int j = 0; j < m; ++j) {
            scanf_s("%d", A + i);

            sum += median(A[i], left, right);
        }

        cout << sum << endl;
    }
}
