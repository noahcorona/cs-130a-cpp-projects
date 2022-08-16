#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
* Awkardness level: min number of seats separating two guests
* that speak the same language
* 
* if nobody speaks the same language, awkwardness level is
* the number of people
* 
* two adjacent seats are said to be separated by 1
* 
* 
*/

class map {
public:
    vector<vector<int>> M;
    int minDiff;
    int guests;

    map(const int numGuests) {
        M = vector<vector<int>>(numGuests, vector<int>({ -1, 0 }));
        minDiff = 1000000001;
        guests = numGuests;
    }

    void insert(const int langNum, const int seatNumber) {

        /*
        case 1: no entries with i = 0 (first lang with given hash)
        case 2: either we have seen this language or we have coliding hashes
        */

        // rehash until langNum matches or no collision
        // once langNum matches, update value

        int row = 0;
        int i = 0;

        while (1) {
            int k = (langNum + i) % guests;

            if (M[k][0] == -1) {
                row = k;
                break;
            } else if (M[k][0] == langNum) {
                row = k;
                break;
            } else
                i++;
        }

        if (M[row][0] == -1) {
            // no keys stored at hash(langNum, i)
            // create entry for language
            M[row][0] = langNum;
        } else if (M[row][0] == langNum) {
            // if hashes match and language numbers do not, collision
            // update entry for language

            // compute new difference
            int newDiff = seatNumber - M[row][1];

            if (newDiff < minDiff) {
                minDiff = newDiff;
            }

            // store position of current element
            M[row][1] = seatNumber;
        }

    }
};

int main()
{
    // get the number of guests
    string nStr;
    cin >> nStr;
    int guests = stoi(nStr);

    // create map
    map M(guests);

    // get the language of each guest
    // input: language spoken by guest seated at position i

    for (int i = 0; i < guests; i++) {
        cin >> nStr;
        M.insert(stoi(nStr), i);
    }

    if (M.minDiff == 1000000001)
        cout << guests << endl;
    else
        cout << M.minDiff << endl;

}
