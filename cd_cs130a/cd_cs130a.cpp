// 
// Noah Corona
// CS 130A
// cd_cs130a.cpp
// 

#include <iostream>
#include <sstream>
#include <string>
#include <math.h>
#include <vector>

using namespace std;

class HashMap {
private:
    vector<vector<int>> map;
public:
    HashMap() {};
    HashMap(int size) {
        map = vector<vector<int>>(size, vector<int>());
    }

    const int hash(const int key) {
        return (key % 2000003);
    }

    void insert(const int key) {
        int a = hash(key);
        map.at(a).push_back(key);
    }

    const bool contains(const int key) {
        int a = hash(key);

        for (auto& k : map.at(a)) {
            if (k == key)
                return true;
        }

        return false;
    }
};


int main()
{
    HashMap map(2000003);

    string line;
    string nStr;

    getline(cin, line);

    istringstream iss(line);
    getline(iss, nStr, ' ');

    int n = stoi(nStr);

    for (int i = 0; i < n; i++) {
        getline(cin, line);
        map.insert(stoi(line));
    }

    int sum = 0;

    while (line != "0 0") {
        getline(cin, line);
        if (line != "0 0" && map.contains(stoi(line))) {
            ++sum;
        }
    }

    cout << sum << endl;
}