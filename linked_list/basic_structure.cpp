#include <iostream>
using namespace  std;

class Node {
    public:
        int data;
        Node* next;
        Node(int val);
};

Node::Node(int val) : data(val), next(nullptr) {}

int main() {
    
}
