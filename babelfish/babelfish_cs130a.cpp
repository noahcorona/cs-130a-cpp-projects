// 
// Noah Corona
// CS 130A
// babelfish_cs130a.cpp
// 

#include <iostream>
#include <sstream>
#include <string>
#include <math.h>
#include <vector>

using namespace std;

/*

Idea:
1. create map that utilizes a string hash function
   for addressing
    - the key is the foreign word
    - the value is the english word
2. to translate a word, then we just need to
    access the correct location in our map
3. loop through message and call translate function
    on each word

To handle collisions we store a key, value pair inside a vector

The hash function takes the sum over all characters of the
product of the ascii values str[i] and (max_str_len - i - 1)^i

This prevents issues such as "ab" == "ba" when summing ascii values

*/

class HashMap {
private:
    vector<vector<pair<string, string>>> map;
public:
    HashMap(const int size) {
        map = vector<vector<pair<string, string>>>(size, vector<pair<string, string>>());
    }

    void insert(const string& strKey, const string& value) {
        int key = strHash(strKey);
        map[key].push_back(make_pair(strKey, value));
    }

    const int strHash(const string& str) {
        int n = 10;
        int sum = 0;
        int size = str.size();

        for (int i = 0; i < size; i++) {
            int k = str[i];
            sum += k * pow(n - i - 1, i);
        }

        return sum;
    }

    const string translate(string& strKey) {
        // for the row of entries that hash to strKey
        for (auto& x : map.at(strHash(strKey))) {
            if (strHash(strKey) != strHash(x.first)) {
                return "eh";
            }

            if (x.first == strKey) {
                return x.second;
            }
        }

        return "eh";
    }
};


int main()
{
    // sum n=1->10 of 255*(10-n-1)^n = 709155
    // so we cannot possibly hash to a higher value
    HashMap map(709155);

    // read all lines of input until blank line encountered
    string line;
    string keyStr;
    string valueStr;

    while (getline(cin, line) && (line != "")) {
        istringstream iss(line);
        getline(iss, valueStr, ' ');
        getline(iss, keyStr, ' ');
        map.insert(keyStr, valueStr);
    }

    // translate all lines of input until no more input
    while (cin >> keyStr) {
        cout << map.translate(keyStr) << endl;
    }
}