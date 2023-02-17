#ifndef DEQUE
#define DEQUE

#include <iostream>

using namespace std;

class Deque {
private:
    class Node {
    private:
        int value;
        Node* left;
        Node* right;
        friend class Deque;
    public:
        Node(int val = 0, Node* l = nullptr, Node* r = nullptr) : value(val), left(l), right(r) { }
    };

private:
    Node* head;
    Node* tail;
    int curSize;

public:
    Deque();
    ~Deque();
    int getSize();
    void pushFront(int item);
    void pushBack(int item);
    int popFront();
    int popBack();
    void clear();
    void printDequeReverse();
    void printDeque();
};

Deque::Deque() : head(nullptr), tail(nullptr), curSize(0) {

}

Deque::~Deque() {
    clear();
}

void Deque::clear() {
    while (curSize > 0)
    {
        popBack();
    }
}

int Deque::getSize() {
    return curSize;
}

void Deque::pushFront(int i) {
    if (curSize == 0)
    {
        head = new Node(i, nullptr, nullptr);
        tail = head;
    }else
    {
        Node *tmp = new Node(i, nullptr, head);
        head->left = tmp;
        head = tmp;
    }
    ++curSize;
}

void Deque::pushBack(int i) {
    if (curSize == 0)
    {
        head = new Node(i, nullptr, nullptr);
        tail = head;
    }else
    {
        Node *tmp = new Node(i, tail, nullptr);
        tail->right = tmp;
        tail = tmp;
    }
    ++curSize;
}

int Deque::popFront() {
    if (curSize == 0) return -1;
    
    int deletedValue = head->value;
    if (curSize == 1)
    {
        delete head;
        head = tail = nullptr;
    }else
    {
        Node *tmp = head;
        head = head->right;
        head->left = nullptr;
        delete tmp;
    }
    --curSize;
    return deletedValue;
}

int Deque::popBack() {
    if (curSize == 0) return -1;

    int deletedValue = tail->value;
    if (curSize == 1)
    {
        delete tail;
        head = tail = nullptr;
    }else
    {
        Node *tmp = tail;
        tail = tail->left;
        tail->right = nullptr;
        delete tmp;
    }
    --curSize;
    return deletedValue;
}

void Deque::printDequeReverse() {
    Node *current = tail;
    while (current != nullptr)
    {
        cout << current->value << ' ';
        current = current->left;
    }
    cout << '\n';
}

void Deque::printDeque() {
    Node *current = head;
    while (current != nullptr)
    {
        cout << current->value << ' ';
        current = current->right;
    }
    cout << '\n';
}

#endif // !DEQUE