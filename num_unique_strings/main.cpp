#include <iostream>
#include <string>
#include "list.h"

using namespace std;

int main() {
    list strList;

    strList.insert("test1");
    strList.insert("test1");
    strList.insert("test2");
    strList.insert("test2");
    strList.insert("test3");
    strList.insert("test3");
    strList.insert("test4");
    strList.insert("test4");
    strList.insert("test5");
    strList.insert("test5");

    return 0;
}