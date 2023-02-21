#include <iostream>
#include "../../Library/BinaryTree.h"

template<class T>
class MorrisInOrderTree : public BinaryTree<T>
{
private:
    void morrisTraverseLast(Node<T> *root)
    {
        Node<T> *p = root;
        while (p != nullptr)
        {
            if (p->left == nullptr)
            {
                std::cout << p->value << ' ';
                p = p->right;
            }else
            {
                Node<T> *tmp = p->left;
                while (tmp->right != nullptr)
                {
                    tmp = tmp->right;
                }
                tmp->right = p;
                tmp = p->left;
                p->left = nullptr;
                p = tmp;
            }
        }
    }
public:
    //only call this method when no more operations need to be executed because it change the construct of the tree
    void morrisTraverseLast()
    {
        morrisTraverseLast(this->root);
    }

    void morrisTraverse()
    {
        Node<T> *p = this->root;

        while (p != nullptr)
        {
            if (p->left == 0)
            {
                std::cout << p->value << ' ';
                p = p->right;
            }else
            {
                Node<T> *tmp = p->left;
                while (tmp->right != p && tmp->right != 0) tmp = tmp->right;
                if (tmp->right == 0)
                {
                    tmp->right = p;
                    p = p->left;
                }else 
                {
                    tmp->right = 0;
                    std::cout << p->value << ' ';
                    p = p->right;
                }
            }
        }
    }
};

