#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;
    Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
public:
    Node* head;
    Node* tail;
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void insertEnd(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = tail = newNode;
            return;
        }
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    void insertFront(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = tail = newNode;
            return;
        }
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    void deleteNode(int val) {
        Node* temp = head;
        while (temp && temp->data != val)
            temp = temp->next;
        if (!temp) return;

        if (temp->prev) temp->prev->next = temp->next;
        else head = temp->next;

        if (temp->next) temp->next->prev = temp->prev;
        else tail = temp->prev;

        delete temp;
    }

    void printForward() {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }

    void printBackward() {
        Node* temp = tail;
        while (temp) {
            cout << temp->data << " -> ";
            temp = temp->prev;
        }
        cout << "NULL\n";
    }
};

int main() {
    DoublyLinkedList dll;
    dll.insertEnd(10);
    dll.insertEnd(20);
    dll.insertEnd(30);
    dll.insertFront(5);

    dll.printForward();   // 5 -> 10 -> 20 -> 30 -> NULL
    dll.printBackward();  // 30 -> 20 -> 10 -> 5 -> NULL

    dll.deleteNode(20);
    dll.printForward();   // 5 -> 10 -> 30 -> NULL

    return 0;
}
