#ifndef LINKED_LIST_STACK
#define LINKED_LIST_STACK

#include <iostream>
#include "NVStack.h"

template <typename T>
struct Node
{
    T data;
    Node *next;
};

template <typename T>
class LinkedListBasedStack : public NVStack<T>
{
public:
    LinkedListBasedStack() : front(nullptr), count(0) {};
    void push(T element)
    {
        Node<T> *newNode = new Node<T>{element, nullptr};
        newNode->next = front;
        front = newNode;
        ++count;
    }

    T pop()
    {
        if (empty())
            throw "Stack is empty";
        Node<T> *dltNode = front;
        front = dltNode->next;
        T dltNodeData = dltNode->data;
        delete dltNode;
        --count;
        return dltNodeData;
    }
    
    T top()
    {
        if (empty())
            throw "Stack is empty";
        return front->data;
    }

    void clear()
    {
        while (count > 0)
        {
            pop();
        }
    }

    int size()
    {
        return count;
    }

    bool empty()
    {
        return (count == 0);
    }

    void print()
    {
        Node<T> *current = front;
        while (current != nullptr)
        {
            std::cout << current->data << ' ';
            current = current->next;
        }
        std::cout << '\n';
    }
    
    ~LinkedListBasedStack()
    {
        clear();
    }
private:
    Node<T> *front;
    int count;
};

#endif

