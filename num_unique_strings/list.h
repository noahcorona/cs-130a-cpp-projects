#ifndef LIST_H
#define LIST_H

#include <string>
#include <iostream>

class node {
public:
    std::string data;
    node* next;

    node() {
        data = "";
        next = nullptr;
    }
};

class list {
private:
    node *head, *tail;
    int count;
public: 
    list();

    // insert to back of list
    void insert(std::string data);

    // search and remove given string
    void remove(std::string data);

    // remove first element in list
    void removeHead();

    // remove last element in list
    void removeTail();

    // print the list
    void print();
};

#endif