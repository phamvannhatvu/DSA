#ifndef BINARY_TREE
#define BINARY_TREE

#include<iostream>

template<class T>
struct Node
{
    Node *left;
    Node *right;
    T value;
    Node(T value) : left(nullptr), right(nullptr), value(value) {}
};

template<class T>
class BinaryTree
{
protected:
    Node<T> *root;
private:
    Node<T> *makeTreeFromList(T arr[], int first, int last)
    {
        if (first > last) return nullptr;

        int mid = (first + last) / 2;
        Node<T> *root = new Node(arr[mid]);
        root->left = makeTreeFromList(arr, first, mid - 1);
        root->right = makeTreeFromList(arr, mid + 1, last);
        return root;
    }

    void inOrderTraversal(Node<T> *root)
    {
        if (root == nullptr) return;
        inOrderTraversal(root->left);
        std::cout << root->value << ' ';
        inOrderTraversal(root->right);
    }

public:  
    BinaryTree() : root(nullptr) {}

    void makeTreeFromList(T arr[], int len)
    {
       root = makeTreeFromList(arr, 0, len - 1);
    }

    virtual void inOrderTraversal()
    {
        inOrderTraversal(root);
    }
};

#endif