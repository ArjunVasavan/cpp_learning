#include <cstddef>
#include <iostream>
using namespace  std;

class Node {
    public:
        int data;
        Node* next;
        Node(int val);
};

class LinkedList {
    private:
        Node* head;
    public:
        LinkedList();
        ~LinkedList();
        void insertEnd(int val);
        void deleteFront();
        void display();
};

LinkedList::LinkedList() : head(nullptr) {};

void LinkedList::insertEnd(int val ) {
    Node* newNode = new Node(val);
    if ( head == nullptr ) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void LinkedList::deleteFront() {
    if ( head == nullptr ) {
        return;
    }
    Node* temp = head;
    head = head->next;
    delete temp;
}

void LinkedList::display() {
    Node* temp = head;
    while ( temp != nullptr) {
        std::cout << "Data -> " << temp->data << std::endl;
        temp = temp->next;
    }
}

LinkedList:: ~LinkedList() {
    Node* temp = head;
    while ( temp != nullptr ) {
        Node* next = temp->next;
        delete temp;
        temp = next;
    }
}

Node::Node(int val) : data(val), next(nullptr) {}

int main() {

    LinkedList list;

    list.insertEnd(10);
    list.insertEnd(20);
    list.insertEnd(30);
    list.insertEnd(40);
    
    list.display();

    list.deleteFront();
    list.display();

}
