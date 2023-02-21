#ifndef LINKED_LIST_QUEUE
#define LINKED_LIST_QUEUE

#include "NVQueue.h"

template <typename T>
struct Node
{
    T data;
    Node *next;
};

template <typename T>
class LinkedListBaseQueue : public NVQueue<T>
{
private:
    Node<T> *front;
    Node<T> *rear;
    int count;
public:
    LinkedListBaseQueue() : front(nullptr), rear(nullptr), count(0) {}
    
    void enQueue(T element)
    {
        if (empty())
        {
            front = new Node<T>{element, nullptr};
            rear = front;
        }else
        {
            Node<T> *newNode = new Node<T>{element, nullptr};
            rear->next = newNode;
            rear = newNode;
        }
        ++count;
    }

    T deQueue()
    {
        if (empty())
            throw "Queue is empty";
        Node<T> *tmp = front;
        front = front->next;
        T deleteData = tmp->data;
        delete tmp;
        --count;   
        if (count == 0) rear = nullptr;
        return deleteData;
    }

    T top()
    {
        if (empty())
            throw "Queue is empty";
        return front->data;
    }

    void print()
    {
        if (empty())
            throw "Queue is empty";
        Node<T> *cur = front;
        while (cur != nullptr)
        {
            std::cout << cur->data << ' ';
            cur = cur->next;
        }
        std::cout << '\n';
    }

    void clear()
    {
        while (count > 0)
        {
            deQueue();
        }
    }

    bool empty()
    {
        return (count == 0);
    }

    int size()
    {
        return count;
    }

    ~LinkedListBaseQueue()
    {
        clear();
    }
};

#endif 