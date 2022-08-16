#include "list.h"

// default constructor
list::list() {
    head = nullptr;
    tail = nullptr;
    count = 0;
}

// insert to back of list
void list::insert(std::string data) {
    node* temp = new node;

    temp->data = data;
    temp->next = nullptr;

    if (head == nullptr) {
        head = temp;
        tail = temp;
        temp = nullptr;
    } else {
        tail->next = temp;
        tail = temp;
    }

    ++count;
};

// search and remove given string
void list::remove(std::string data) {
    node* temp = new node;
    node* prev = new node;

    temp = head;
    prev = nullptr;

    // make sure list is not empty
    while (temp != nullptr) {

        if (temp->data == data) {
            break;
        } else {
            prev = temp;
            temp = temp->next;
        }
    }

    if (temp == nullptr)
        std::cout << "Element is not in list" << std::endl;
    else {

        // first element in list is to be deleted
        if (prev == nullptr) {

            // is this the only element in list?
            if (tail == temp)
                tail = nullptr;

            head = temp->next;

            delete temp;

            --count;
        } else { // element is elsewhere in list

            // if we are removing last element in list, next is nullptr
            if (temp->next == nullptr)
                tail = nullptr;

            // re-link the list
            prev->next = temp->next;

            delete temp;

            --count;
        }
    }

}

// remove first element in list
void list::removeHead() {
    node* temp = new node;

    temp = head;
    head = head->next;

    delete temp;

    --count;
}

// remove last element in list
void list::removeTail() {
    node* current = new node;
    node* prev = new node;
    current = head;

    while (current->next != nullptr) {
        prev = current;
        current = current->next;
    }

    tail = prev;
    prev->next = nullptr;
    delete current;

    --count;
}

// print the list
void list::print() {
    node* temp = new node;
    temp = head;

    while (temp != nullptr) {
        std::cout << temp->data << "\t";
        temp = temp->next;
    }
}