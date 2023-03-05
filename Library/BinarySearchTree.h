#ifndef BINARY_SEARCH_TREE
#include <iostream>

template <class T>
class BSTree
{
public:
    class Node
    {
    public:
        Node *left;
        Node *right;
        T value;
        Node (const T &value) : left(nullptr), right(nullptr), value(value) {}
    };
private:
    Node *root = nullptr;
    int count = 0;
    void inOrderTranverse(Node*);
public:
    virtual void remove(const T&);
    virtual void insert(const T&);
    void inOrderTranverse();
    bool contain(const T&);
    int getSize();
    bool isEmpty();
    void clear();
    ~BSTree();
};

template <class T>
void BSTree<T>::remove(const T &value)
{
    if (root == nullptr) return;
    if (count == 1 && root->value == value)
    {
        delete root;
        root = nullptr;
        count = 0;
        return;
    }

    Node *parent = nullptr;
    Node *current = root;
    while (current != nullptr)
    {
        if (value < current->value)
        {
            parent = current;
            current = current->left;
        }else if (value > current->value)
        {
            parent = current;
            current = current->right;
        }else
        {
            if (current->left == nullptr)
            {
                if (parent == nullptr) root = root->right;
                else if (parent->left == current) parent->left = current->right;
                else parent->right = current->right;
                delete current;
            }else if (current->right == nullptr)
            {
                if (parent == nullptr) root = root->left;
                else if (parent->left == current) parent->left = current->left;
                else parent->right = current->left;
                delete current;
            }else
            {
                Node *leftChild = current->left;
                parent = current;
                while (leftChild->right != nullptr)
                {
                    parent = leftChild;
                    leftChild = leftChild->right;
                }
                std::swap(leftChild->value, current->value);
                if (parent->left == leftChild) parent->left = leftChild->left;
                else parent->right = leftChild->left;
                delete leftChild;
            }
            --count;
            return;
        }
    }
}

template<class T>
void BSTree<T>::insert(const T &value)
{
    if (root == nullptr)
    {
        root = new Node(value);
        count = 1;
        return;
    }

    Node *node = root;
    Node *parent = nullptr;
    while  (node != nullptr)
    {
        parent = node;
        if (value < node->value)
        {
            node = node->left;
        }else node = node->right;
    }
    if (value < parent->value)
    {
        parent->left = new Node(value);
    }else parent->right = new Node(value);
    ++count;
}

template <class T>
void BSTree<T>::inOrderTranverse()
{
    inOrderTranverse(root);
    std::cout << '\n';
}

template<class T>
void BSTree<T>::inOrderTranverse(Node *root)
{
    if (root == nullptr) return;
    inOrderTranverse(root->left);
    std::cout << root->value << "(";
    std::cout << (root->left == nullptr ? -1 : root->left->value) << ',';
    std::cout << (root->right == nullptr ? -1 : root->right->value) << ") ";
    inOrderTranverse(root->right);
}

template<class T>
bool BSTree<T>::contain(const T &value)
{
    Node *current = root;
    while (current != nullptr)
    {
        if (value < current->value)
        {
            current = current->left;
        }else if (value > current->value)
        {
            current = current->right;
        }else return true;
    }
    return false;
}

template <class T>
int BSTree<T>::getSize()
{
    return count;
}

template <class T>
bool BSTree<T>::isEmpty()
{
    return count == 0;
}

template <class T>
void BSTree<T>::clear()
{
    while (count > 0) remove(root->value);
}

template <class T>
BSTree<T>::~BSTree()
{
    clear();
}

#endif