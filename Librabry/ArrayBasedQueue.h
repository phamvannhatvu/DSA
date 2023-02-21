#ifndef QUEUE_ARRAY
#define QUEUE_ARRAY

#include "NVQueue.h"
#include <cstring>

template <typename T>
class ArrayBasedQueue : public NVQueue<T>
{
private:
    int front;
    int rear;
    int capacity;
    int count;
    T *data;

    bool full()
    {
        return count == capacity;
    }

    void resize(int newCapacity)
    {
        T *tmp = new T[newCapacity];
        for (int i = 0; i < count; ++i)
        {
            tmp[i] = data[(i + front) % capacity];
        }
        front = 0;
        rear = capacity - 1;
        capacity = newCapacity;
        if (count > 0) delete[] data;
        data = tmp;
    }

    void inc(int &a)
    {
        ++a;
        if (a == capacity) a = 0;
    }

    void dec(int &a)
    {
        --a;
        if (a == -1) a = capacity - 1;
    }
public:
    ArrayBasedQueue(int capacity = 10) : front(0), rear(-1), capacity(capacity), data(new T[capacity]), count(0) {}

    void enQueue(T element)
    {
        if (full())
        {
            resize(capacity * 2 + 1);
        }
        inc(rear);
        data[rear] = element;
        ++count;
    }

    T deQueue()
    {
        if (empty())
            throw "Queue is empty";
        T deQueueData = data[front];
        inc(front);
        --count;
        return deQueueData;
    }

    T top()
    {
        if (empty())
            throw "Queue is empty";
        return data[front];
    }

    void print()
    {
        for (int i = 0; i < count; ++i)
        {
            std::cout << data[(i + front) % capacity] << ' ';
        }
    }

    int size()
    {
        return count;
    }

    bool empty()
    {
        return count == 0;
    }

    void clear()
    {
        front = -1;
        rear = -1;
        count = 0;
        capacity = 0;
        delete[] data;
    }

    ~ArrayBasedQueue()
    {
        clear();
    }
};

#endif