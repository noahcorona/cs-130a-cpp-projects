#include <iostream>

using namespace std;

bool verbose = 1;

int max(int a, int b) {
    if (a >= b)
        return a;
    else
        return b;
}

// Algorithm 1
// O(n^3) algorithm
// 3 nested loops exhausting all possible combinations
int max_subsequence_1(const int *numArr, const int size) {
    int m = -999999;

    for (int a = 0; a < size; a++) {

        if(verbose) cout << "a: " << a << endl;

        for (int b = a; b < size; b++) {
            if (verbose) cout << "   b: " << b << endl;

            int s = 0;

            for (int i = a; i <= b; i++) {
                s += numArr[i];
            }

            m = max(s, m);

            if (verbose) cout << "       s: " << s << endl;
        }
    }

    return m;
}

// Algorithm 2
// O(n^2) algorithm
// 2 nested loops exhausting all possible combinations
int max_subsequence_2(const int* numArr, const int size) {
    int m = -999999;

    for (int a = 0; a < size; a++) {

        if (verbose) cout << "a: " << a << endl;

        int s = 0;

        for (int b = a; b < size; b++) {
            if (verbose) cout << "   b: " << b << endl;

            s += numArr[b];
            m = max(s, m);

            if (verbose) cout << "   s: " << s << endl;
        }
    }

    return m;
}




int main()
{
    const int nums[] = { -10, 8, -9, -7, 10, -4, -1, 6, 3, 8, 9, -7, 9, 1, -1, 10, -5, 9, 5, 6 };
    const int size = sizeof(nums) / sizeof(nums[0]);
    
    cout << endl << endl << max_subsequence_1(nums, size) << endl;

    return 0;
}