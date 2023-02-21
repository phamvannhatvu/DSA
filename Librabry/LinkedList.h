#include <iostream>

#ifndef LINKED_LIST
#define LINKED_LIST
template <class T>
class IList
{
public:
    virtual void add(T element) = 0;
    virtual void add(int index, T element) = 0;
    virtual bool removeItem(T element) = 0;
    virtual T removeAt(int index) = 0;
    virtual bool empty() = 0;
    virtual int size() = 0;
    virtual void clear() = 0;
    virtual T get(int index) = 0;
    virtual void set(int index, T value) = 0;
    virtual int indexOf(T element) const = 0;
    virtual bool contains(T item) const = 0;
    virtual void print() = 0;
};

template<class T>
class SLinkedList : public IList<T>
{
public:
    class Node;

private:
    void checkIndex(int index, int lower, int upper);
    Node* findPreNode(int index);

protected:
    Node* head;
    Node* tail;
    int count;

public:
    SLinkedList();
    virtual bool empty();
    virtual void clear();
    virtual int size();
    virtual void add(T element);
    virtual void add(int index, T element);
    virtual T removeAt(int index);
    virtual bool removeItem(T element);
    virtual T get(int index);
    virtual void set(int index, T element);
    virtual int indexOf(T element) const;
    virtual bool contains(T item) const;
    virtual void print();
    void reverse();
    void mergeWith(SLinkedList otherList);
    void deleteFromList(SLinkedList deletedIndexes);
    ~SLinkedList()
    {
        clear();
    }
};

template<class T>
SLinkedList<T>::SLinkedList() 
{
    head = nullptr;
    tail = nullptr;
    count = 0;
}

template<class T>
class SLinkedList<T>::Node
{
public:
    T data;
    Node* next;
    Node(T data = 0) : data(data), next(nullptr) {};
};

template<class T>
bool SLinkedList<T>::empty()
{
    return (count == 0);
}

template<class T>
void SLinkedList<T>::clear()
{
    while (count)
    {
        removeAt(1);
    }
}

template<class T>
int SLinkedList<T>::size()
{
    return count;
}

template<class T>
void SLinkedList<T>::add(T element)
{
    if (empty())
    {
        head = new Node(element);
        tail = head;
    }else
    {
        Node* newNode = new Node(element);
        tail->next = newNode;
        tail = newNode;
    }
    ++count;
}

template<class T>
void SLinkedList<T>::add(int index, T element)
{
    checkIndex(index, 1, count);
    //Empty case is same as add at the end of list
    if (index == count + 1 || empty())
    {
        add(element);
    }else
    {
        Node* newNode = new Node(element);
        if (index == 1)
        {
            newNode->next = head;
            head = newNode;
        }else
        {
            Node* preNode = findPreNode(index);
            newNode->next = preNode->next;
            preNode->next = newNode;
        }
        ++count;
    }  
}

template<class T>
T SLinkedList<T>::removeAt(int index)
{
    //Also check for case delete empty list
    checkIndex(index, 1, count);
    if (index == 1)
    {
        Node* dNode = head;
        T ret_value = dNode->data;
        if (count == 1)
        {
            delete dNode;
            head = tail = nullptr;
        }else
        {
            head = dNode->next;
            delete dNode;
        }
        --count;
        return ret_value;
    }
    Node* preNode = findPreNode(index);
    Node* dNode = preNode->next;
    T ret_value = dNode->data;
    if (index == count)
    {
        tail = preNode;
    }
    preNode->next = dNode->next;
    delete dNode;
    --count;
    return ret_value;
}

template<class T>
bool SLinkedList<T>::removeItem(T element)
{
    int index = indexOf(element);
    if (index == -1) return false;
    removeAt(index);
    return true;
}

template<class T>
T SLinkedList<T>::get(int index)
{
    checkIndex(index, 1, count);
    if (index == 1) return head->data;
    return findPreNode(index)->next->data;
}

template<class T>
void SLinkedList<T>::set(int index, T element)
{
    checkIndex(index, 1, count);
    Node* tmpNode = head;
    while (index--)
    {
        tmpNode = tmpNode->next;
    }
    tmpNode->data = element;
}

template<class T>
int SLinkedList<T>::indexOf(T element) const
{
    Node* tmpNode = head;
    for (int i = 1; i <= count; ++i)
    {
        if (tmpNode->data == element)
        {
            return i;
        }
        tmpNode = tmpNode->next;
    }
    return -1;
}

template<class T>
bool SLinkedList<T>::contains(T item) const
{
    return (indexOf(item) != -1);
}

template<class T>
void SLinkedList<T>::print()
{
    std::cout << "Size: " << size() << '\n';
    Node* tmpNode = head;
    for (int i = 1; i <= count; ++i)
    {
        std::cout << tmpNode->data << ' ';
        tmpNode = tmpNode->next;
    }
    std::cout << '\n';
}

template<class T>
void SLinkedList<T>::reverse()
{
    if (size() <= 1) return;
    Node* current = head->next;
    Node* prev = head;
    tail = head;
    while (current != nullptr)
    {
        Node* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
    tail->next = nullptr;
}

template<class T>
void SLinkedList<T>::mergeWith(SLinkedList<T> otherList)
{
    if (otherList.size() == 0) return;
    if (size() == 0)
    {
        head = new Node(otherList.head->data);
        tail = head;
    }else
    {
        Node* tmp = new Node(otherList.head->data);
        tail->next = tmp;
        tail = tmp;
    }
    Node* otherCurrent = otherList.head->next;
    for (int i = 0; i < otherList.size() - 1; ++i)
    {
        Node* tmp = new Node(otherCurrent->data);
        tail->next = tmp;
        tail = tmp;
        otherCurrent = otherCurrent->next;
    }
    count += otherList.size();
}

template<class T>
void SLinkedList<T>::deleteFromList(SLinkedList<T> deletedIndexes)
{
    Node* current_element = head;
    Node* current_index = deletedIndexes.head;
    Node* prev_element = nullptr;
    int i = 1;
    while (current_element != nullptr && current_index != nullptr)
    {
        if (i == current_index->data)
        {
            if (prev_element == nullptr)
            {
                head = current_element->next;
                delete current_element;
                current_element = head;
            }else
            {
                prev_element->next = current_element->next;
                delete current_element;
                current_element = prev_element->next;
                if (current_element == nullptr) tail = prev_element;
            }
            current_index = current_index->next;
            --count;
        }else
        {
            prev_element = current_element;
            current_element = current_element->next;
        }
        ++i;
    }
}

template<class T>
void SLinkedList<T>::checkIndex(int index, int lower, int upper)
{
    if (index < lower || index > upper)
    {
        throw std::out_of_range("Index is out of range");
    }
}

template<class T>
typename SLinkedList<T>::Node* SLinkedList<T>::findPreNode(int index)
{
    Node* preNode = head;
    while (index > 2)
    {
        --index;
        preNode = preNode->next;
    }
    return preNode;
}

template<class T>
void deleteItSelf(SLinkedList<T>& list)
{
    SLinkedList<T> clone_list;
    clone_list.mergeWith(list);
    list.deleteFromList(clone_list);
    clone_list.clear();
}
#endif