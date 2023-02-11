#include <iostream>
#include <vector>
#include <typeinfo>

class Node
{
private:
    Node *next;
    Node *prev;
    int data;
public:
    Node(int data = 0)
    {
        this->data = data;
        next = nullptr;
        prev = nullptr;
    }
    friend class DoublyLinkedList;
};

class DoublyLinkedList
{
private:
    Node *head;
    Node *tail;
    int count;
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {};
    void add(int index, int data)
    {
        if (index == 1)
        {
            Node *tmp = new Node(data);
            tmp->next = head; //Also true for case empty list (head = nullptr)
            if (count == 0) 
            {
                head = tail = tmp;    
            }else
            {
                head->prev = tmp;
                head = tmp;
            }
        }else
        {
            Node *tmp = new Node(data);
            Node *pPre = findNodePre(index);
            if (index == count + 1)
            {
                pPre->next = tmp;
                tmp->prev = pPre;
                tail = tmp;
            }else
            {
                tmp->next = pPre->next;
                pPre->next = tmp;
                tmp->prev = pPre;
                tmp->next->prev = tmp;
            }
        }
        ++count;
    }

    Node *findNodePre(int index)
    {
        if (index == 1) return nullptr;
        Node *current = head;
        while (index-- > 2)
        {
            current = current->next;
        }
        return current;
    }

    int size()
    {
        return count;
    }

    void print()
    {
        std::cout << count << '\n';
        Node *current = head;
        while (current != nullptr)
        {
            std::cout << current->data << ' ';
            current = current->next;
        }
        std::cout << '\n';
    }

    void reversePrint()
    {
        std::cout << count << '\n';
        Node *current = tail;
        while (current != nullptr)
        {
            std::cout << current->data << ' ';
            current = current->prev;
        }
        std::cout << '\n';
    }
};

int main()
{
    DoublyLinkedList dll;
    dll.add(1, 2);
    dll.add(2, 3);
    dll.add(3, 4);
    dll.add(2, 0);
    dll.add(1, 5);
    dll.add(3, 5); 
    dll.print();
    dll.reversePrint();
    return 0;
}