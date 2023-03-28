#ifndef BTREE_DATA_STRUCTURE
#define BTREE_DATA_STRUCTURE

#include <iostream>
#include <queue>
#include <utility>

using std::queue;
using std::cout;
using std::pair;

template<class T>
class Node;

template<class T>
class BTree;

template<class T>
class Entry
{
private:
    Node<T>* rightPtr;
    T value;
    friend class BTree<T>;
public:
    Entry() : value(0), rightPtr(nullptr)
    {

    }
    
    Entry(int value) : value(value), rightPtr(nullptr)
    {

    }

    ~Entry()
    {

    }
};

template<class T>
class Node
{
private:
    int entriesCapacity;
    int entriesSize;
    Node* firstPtr;
    Entry<T>* entries;
    friend class BTree<T>;
public:
    Node(int entriesCapacity = 10) : entriesCapacity(entriesCapacity), 
        entriesSize(0), entries(new Entry<T>[entriesCapacity]), firstPtr(nullptr)
    {
        
    }
    ~Node()
    {
        for (int i = 0; i < entriesSize; ++i)
        {
            delete entries[i];
        }
        delete[] entries;
        if (firstPtr != nullptr)
        {  
            delete firstPtr;
        }
    }
};

template<class T>
class BTree
{
private:
    Node<T> *root;
    int entriesCapacity;

    void addEntryToNotOverflowNode(Node<T> *node, const Entry<T> &newEntry)
    {
        int insertPosition = node->entriesSize;
        while (insertPosition > 0 && node->entries[insertPosition - 1].value >= newEntry.value)
        {
            --insertPosition;
        }

        for (int i = node->entriesSize; i > insertPosition; --i)
        {
            node->entries[i] = node->entries[i - 1];
        }
        node->entries[insertPosition] = newEntry;
        ++node->entriesSize;
    }

    void addEntryToNode(Node<T> *node, Entry<T> &newEntry, bool &isOverflow)
    {
        if (node->entriesSize == node->entriesCapacity)
        {
            int medianPosition = node->entriesSize / 2;
            Node<T> *newNode = new Node<T>(entriesCapacity);
            Entry<T> overflowEntry = node->entries[medianPosition];

            if (newEntry.value <= node->entries[medianPosition].value)
            {
                for (int i = medianPosition; i < node->entriesSize; ++i)
                {
                    newNode->entries[newNode->entriesSize++] = node->entries[i];
                }                
                node->entriesSize = medianPosition;
                addEntryToNotOverflowNode(node, newEntry);
                overflowEntry = node->entries[medianPosition];
                --node->entriesSize;
            }else
            {   
                for (int i = medianPosition + 1; i < node->entriesSize; ++i)
                {
                    newNode->entries[newNode->entriesSize++] = node->entries[i];
                }
                node->entriesSize = medianPosition;
                addEntryToNotOverflowNode(newNode, newEntry);
            }

            node->entries[medianPosition].rightPtr = nullptr;
            newNode->firstPtr = overflowEntry.rightPtr;
            overflowEntry.rightPtr = newNode;
            newEntry = overflowEntry;
            isOverflow = true;
        }else
        {
            addEntryToNotOverflowNode(node, newEntry);
            isOverflow = false;
        }
    }

    void insert(Node<T> *node, const T &value, Entry<T> &overflowEntry, bool &isOverflow)
    {
        if (node->firstPtr != nullptr)
        {
            if (value <= node->entries[0].value)
            {
                insert(node->firstPtr, value, overflowEntry, isOverflow);
            }else
            {
                int insertPosition = node->entriesSize - 1;
                while (node->entries[insertPosition].value >= value)
                {
                    --insertPosition;
                }
                insert(node->entries[insertPosition].rightPtr, value, overflowEntry, isOverflow);
            }
            if (isOverflow)
            {
                addEntryToNode(node, overflowEntry, isOverflow);
            }
        }else
        {
            addEntryToNode(node, overflowEntry, isOverflow);
        }
    }

    void mergeSubTree(Node<T> *node, int mergeIndex, bool &isUnderflow)
    {        
        Node<T> *preNode = (mergeIndex > 0 ? node->entries[mergeIndex - 1].rightPtr : node->firstPtr);
        Node<T> *curNode = node->entries[mergeIndex].rightPtr;
        if (preNode->entriesSize > entriesCapacity / 2)
        {
            T nodeValue = node->entries[mergeIndex].value;
            --preNode->entriesSize;
            node->entries[mergeIndex].value = preNode->entries[preNode->entriesSize].value;
            
            for (int i = curNode->entriesSize; i > 0; --i)
            {
                curNode->entries[i] = curNode->entries[i - 1];
            }
            ++curNode->entriesSize;
            curNode->entries[0].value = nodeValue;
            curNode->entries[0].rightPtr = preNode->entries[preNode->entriesSize].rightPtr;
            preNode->entries[preNode->entriesSize].rightPtr = nullptr;
            isUnderflow = false;
        }else
        {
            node->entries[mergeIndex].rightPtr = curNode->firstPtr;
            curNode->firstPtr = nullptr;
            preNode->entries[preNode->entriesSize++] = node->entries[mergeIndex];
            for (int i = 0; i < curNode->entriesSize; ++i)
            {
                preNode->entries[preNode->entriesSize++] = curNode->entries[i];
                curNode->entries[i].rightPtr = nullptr;
            }
            for (int i = mergeIndex + 1; i < node->entriesSize; ++i)
            {
                node->entries[i - 1] = node->entries[i];
            }
            --node->entriesSize;
            node->entries[node->entriesSize].rightPtr = nullptr;
            isUnderflow = (node->entriesSize < entriesCapacity / 2);
        }
    }

    void remove(Node<T> *node, const T& value, bool &isUnderflow, bool isFounded)
    {
        if (node->firstPtr != nullptr)
        {
            if (isFounded)
            {
                remove(node->firstPtr, value, isUnderflow, isFounded);
                if (isUnderflow)
                {
                    mergeSubTree(node, 0, isUnderflow);
                }
            }else
            {
                if (value <= node->entries[0].value)
                {
                    if (value == node->entries[0].value)
                    {
                        Node<T> *successor = node->entries[0].rightPtr;
                        while (successor->firstPtr != nullptr)
                        {
                            successor = successor->firstPtr;
                        }
                        node->entries[0].value = successor->entries[0].value;
                        remove(node->entries[0].rightPtr, node->entries[0].value, isUnderflow, true);
                        if (isUnderflow)
                        {
                            mergeSubTree(node, 0, isUnderflow);
                        }
                    }else
                    {
                        remove(node->firstPtr, value, isUnderflow, isFounded);
                        if (isUnderflow)
                        {
                            mergeSubTree(node, 0, isUnderflow);
                        }
                    }
                }else
                {
                    int deletedPosition = node->entriesSize - 1;
                    while (node->entries[deletedPosition].value > value)
                    {
                        --deletedPosition;
                    }
                    if (node->entries[deletedPosition].value == value)
                    {
                        Node<T> *predecessor = node->entries[deletedPosition].rightPtr;
                        while (predecessor->firstPtr != nullptr)
                        {
                            predecessor = predecessor->firstPtr;
                        }
                        node->entries[deletedPosition].value = predecessor->entries[0].value;
                        remove(node->entries[deletedPosition].rightPtr, node->entries[deletedPosition].value, isUnderflow, true);
                        if (isUnderflow)
                        {
                            mergeSubTree(node, deletedPosition, isUnderflow);
                        } 
                    }else
                    {
                        remove(node->entries[deletedPosition].rightPtr, value, isUnderflow, isFounded);                       
                        if (isUnderflow)
                        {
                            mergeSubTree(node, deletedPosition, isUnderflow);
                        } 
                    }
                }
            } 
        }else
        {
            int deletedIndex = -1;
            for (int i = 0; i < node->entriesSize; ++i)
            {
                if (node->entries[i].value == value)
                {
                    deletedIndex = i;
                    break;
                }
            }

            if (deletedIndex != -1)
            {
                if (node->entriesSize == entriesCapacity / 2)
                {
                    isUnderflow = true;
                }
                --node->entriesSize;
                for (int i = deletedIndex; i < node->entriesSize; ++i)
                {
                    node->entries[i] = node->entries[i + 1];
                }
            }
        }
    }
public:
    void remove(const T& value)
    {
        bool isUnderflow = false;
        remove(root, value, isUnderflow, false);
        if (root->entriesSize == 0)
        {
            Node<T> *newRoot = root->firstPtr;
            root->firstPtr = nullptr;
            root = newRoot;
        }
    }

    void insert(const T& value)
    {
        if (root == nullptr)
        {
            root = new Node<T>(entriesCapacity);
            root->entriesSize = 1;
            root->entries[0].value = value;
        }else
        {
            Entry<T> newEntry(value);
            bool isOverflow = false;
            insert(root, value, newEntry, isOverflow);
            if (isOverflow)
            {
                Node<T> *newRoot = new Node<T>(entriesCapacity);
                newRoot->entries[0] = newEntry;
                newRoot->entriesSize = 1;
                newRoot->firstPtr = root;
                root = newRoot;
            }
        }
    }

    void print()
    {
        if (root == nullptr)
        {
            cout << "Empty";
            return;
        }
        queue< pair<Node<T>*, int> > q;
        q.push({root, 0});
        int preHeight = -1;
        while (q.size() > 0)
        {
            Node<T>* node = q.front().first;
            int height = q.front().second;
            if (height != preHeight)
            {
                cout << '\n';
                preHeight = height;
            }

            for (int i = 0; i < node->entriesSize; ++i)
            {
                cout << node->entries[i].value << '|';
            }
            q.pop();
            if (node->firstPtr != nullptr)
            {
                q.push({node->firstPtr, height + 1});
                for (int i = 0; i < node->entriesSize; ++i)
                {
                    q.push({node->entries[i].rightPtr, height + 1});
                }
            }
            cout << ' ';
        }
        cout << "\n=========================\n";
    }

    BTree(int entriesCapacity = 10) : root(nullptr), entriesCapacity(entriesCapacity)
    {

    }

    ~BTree()
    {
        // while (root != nullptr)
        //     remove(root->entries[0].value);
    }
};

#endif