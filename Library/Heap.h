#ifndef _HEAP_DATA_STRUCTURE_
#define _HEAP_DATA_STRUCTURE_

#include <cstring>
#include <iostream>

using std::cout;
using std::swap;

template<class T>
class Heap
{
private:
    T *data;
    int capacity;
    int size;
    void enlarge()
    {
        T *newData = new T[2 * capacity];
        std::memcpy(newData, data, capacity * sizeof(T));
        capacity = 2 * capacity;
        delete[] data;
        data = newData;
    }

    void reheapUp(int index)
    {
        int parentIndex = (index - 1) / 2;
        if (parentIndex >= 0 && data[parentIndex] < data[index])
        {
            swap(data[parentIndex], data[index]);
            reheapUp(parentIndex);
        }
    }

    void reheapDown(int index)
    {
        int leftIndex = 2 * index + 2;
        int rightIndex = 2 * index + 1;
        if (leftIndex < size && data[index] < data[leftIndex] && data[rightIndex] < data[leftIndex])
        {
            swap(data[index], data[leftIndex]);
            reheapDown(leftIndex);
        }else if (rightIndex < size && data[index] < data[rightIndex])
        {
            swap(data[index], data[rightIndex]);
            reheapDown(rightIndex);
        }
    }
public:
    Heap(int capacity = 10) : capacity(capacity), size(0)
    {
        data = new T[capacity];
    }
    
    ~Heap()
    {
        delete[] data;
    }

    void push(const T& item)
    {
        if (size == capacity) enlarge();
        data[size] = item;
        reheapUp(size);
        ++size;
    }

    void pop()
    {
        if (size == 0) return;
        --size;
        swap(data[0], data[size]);
        reheapDown(0);
    }

    void printArray()
    {
        for (int i = 0; i < size; ++i)
        {
            cout << data[i] << ' ';
        }
        cout << '\n';
    }

    int getSize()
    {
        return size;
    }
};

#endif