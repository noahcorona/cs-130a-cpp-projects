#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

int strHash(string str, int maxSize) {
    int n = maxSize;
    int sum = 0;
    int size = str.size();

    for (int i = 0; i < size; i++) {
        int k = str[i];
        sum += k * pow(n - i - 1, i);
    }

    return sum;
}

int main()
{
    string s;
    getline(cin, s);
    const int size = s.length();

    // create NxN matrix of hash values

    vector< vector<unsigned long long int> > subStrHashes;
    subStrHashes.resize(size, vector<unsigned long long int>());

    // hash all possible substrings and
    // store in 2D vector where

    for (int i = 0; i < size; i++) {

        // build substr char-by-char
        string substr;

        int j = i;

        while (j < size) {
            substr += s.at(j);
            subStrHashes[i].push_back(strHash(substr, size));
            j++;
        }
    }

    // get number of queries

    string strQueries;
    getline(cin, strQueries);
    int queries = stoi(strQueries);

    // output hash value for query

    for (int i = 0; i < queries; ++i) {
        int l = (int) cin.get() - '0';
        cin.get();
        int r = (int) cin.get() - '0' - 1;
        cin.get();

        cout << subStrHashes[l][r - l] << endl;
    }
}