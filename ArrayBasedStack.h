#ifndef STACK_ARRAY
#define STACK_ARRAY

#include <stdexcept>
#include "NVStack.h"
template<typename T>
class ArrayBasedStack : public NVStack<T>
{
public:
    ArrayBasedStack() : front(-1), capacity(10), data(new T[10]) {}
    void push(T element)
    {
        if (front == capacity - 1)
        {
            //Decide to double when resized (haven't careful calculate)
            resize(capacity * 2 + 1);
        }
        data[++front] = element;
    }
    T pop()
    {
        if (front == -1)
            throw "Stack is empty";
        return data[front--];
    }
    T top()
    {
        if (front == -1)
            throw "Stack is empty";
        return data[front];
    }
    void clear()
    {
        front = -1;
        delete [] data;
        capacity = 0;
    }
    void resize(int new_capacity)
    {
        T *tmp = new T[new_capacity];
        memcpy(tmp, data, sizeof(T) * (front + 1));
        if (front != -1) delete [] data;
        data = tmp;
        capacity = new_capacity;
    }
    bool empty()
    {
        return (front == -1);
    }
    int size()
    {
        return front + 1;
    }
    void print()
    {
        if (front == -1)
            throw "Stack is empty";
        for (int i = front; i >= 0; --i)
        {
            std::cout << data[i] << ' ';
        }
        std::cout << '\n';
    }
    ~ArrayBasedStack()
    {
        delete[] data;
    }
private:
    int front;
    int capacity;
    T *data;
};

#endif
