//Pass problem: https://leetcode.com/problems/balance-a-binary-search-tree/description/
//Solution: https://leetcode.com/problems/balance-a-binary-search-tree/submissions/921237745/
#ifndef AVL_BALANCE_FACTOR
#define AVL_BALANCE_FACTOR

#include <iostream>
#include <math.h>
#include <queue>

using namespace std;

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

template<class T>
class AVLTree
{
public:
    class Node;
private:
    Node *root;
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree(){}

    Node *rotateLeft(Node *node)
    {
        Node *rightNode = node->pRight;
        node->pRight = rightNode->pLeft;
        rightNode->pLeft = node;
        return rightNode;
    }

    Node *rotateRight(Node *node)
    {
        Node *leftNode = node->pLeft;
        node->pLeft = leftNode->pRight;
        leftNode->pRight = node;
        return leftNode;
    }

    Node *balanceLeft(Node *node, bool &isTaller, bool &isShorter)
    {
        if (node->balance == BalanceValue::RH)
        {
            node->balance = BalanceValue::EH;
            isTaller = false;
            isShorter = true;
        }else if (node->balance == BalanceValue::EH)
        {
            node->balance = BalanceValue::LH;
            isTaller = true;
            isShorter = false;
        }else 
        {
            Node *leftNode = node->pLeft;
            if (leftNode->balance == BalanceValue::LH)
            {
                node->balance = BalanceValue::EH;
                leftNode->balance = BalanceValue::EH;
                node = rotateRight(node);
                isTaller = false;
                isShorter = true;
            }else if (leftNode->balance == BalanceValue::EH)
            {
                node->balance = BalanceValue::LH;
                leftNode->balance = BalanceValue::RH;
                node = rotateRight(node);
                //isTaller = true;
                isShorter = false;
            }else
            {
                Node *rightNode = leftNode->pRight;
                if (rightNode->balance == BalanceValue::LH)
                {
                    node->balance = BalanceValue::RH;
                    leftNode->balance = BalanceValue::EH;
                    isShorter = true;
                    isTaller = false;
                }else if (rightNode->balance == BalanceValue::EH)
                {
                    node->balance = BalanceValue::EH;
                    leftNode->balance = BalanceValue::EH;
                    isShorter = true;
                    isTaller = false;
                }else 
                {
                    node->balance = BalanceValue::EH;
                    leftNode->balance = BalanceValue::LH;
                    isShorter = true;
                    isTaller = false;
                }
                rightNode->balance = BalanceValue::EH;
                node->pLeft = rotateLeft(leftNode);
                node = rotateRight(node);
            }
        }
        return node;
    }

    Node *balanceRight(Node *node, bool &isTaller, bool &isShorter)
    {
        if (node->balance == BalanceValue::LH)
        {
            node->balance = BalanceValue::EH;
            isTaller = false;
            isShorter = true;
        }else if (node->balance == BalanceValue::EH)
        {
            node->balance = BalanceValue::RH;
            isTaller = true;
            isShorter = false;
        }else 
        {
            Node *rightNode = node->pRight;
            if (rightNode->balance == BalanceValue::RH)
            {
                node->balance = BalanceValue::EH;
                rightNode->balance = BalanceValue::EH;
                node = rotateLeft(node);
                isTaller = false;
                isShorter = true;
            }else if (rightNode->balance == BalanceValue::EH)
            {
                node->balance = BalanceValue::RH;
                rightNode->balance = BalanceValue::LH;
                node = rotateLeft(node);
                //isTaller = true;
                isShorter = false;
            }else
            {
                Node *leftNode = rightNode->pLeft;
                if (leftNode->balance == BalanceValue::LH)
                {
                    node->balance = BalanceValue::EH;
                    rightNode->balance = BalanceValue::RH;
                    isShorter = true;
                    isTaller = false;
                }else if (leftNode->balance == BalanceValue::EH)
                {
                    node->balance = BalanceValue::EH;
                    rightNode->balance = BalanceValue::EH;
                    isShorter = true;
                    isTaller = false;
                }else 
                {
                    node->balance = BalanceValue::LH;
                    rightNode->balance = BalanceValue::EH;
                    isShorter = true;
                    isTaller = false;
                }
                leftNode->balance = BalanceValue::EH;
                node->pRight = rotateRight(rightNode);
                node = rotateLeft(node);
            }
        }
        return node;
    }

    Node *add(Node *node, const T& value, bool &isTaller)
    {
        if (node == nullptr)
        {
            node = new Node(value);
            isTaller = true;
        }else if (node->data > value)
        {
            node->pLeft = add(node->pLeft, value, isTaller);
            if (isTaller)
            {
                bool dummyShorter = false;
                node = balanceLeft(node, isTaller, dummyShorter);
            }
        }else 
        {
            node->pRight = add(node->pRight, value, isTaller);
            if (isTaller)
            {
                bool dummyShorter = false;
                node = balanceRight(node, isTaller, dummyShorter);
            }
        }
        return node;
    }

    void add(const T &value)
    {
        if (root == nullptr)
        {
            root = new Node(value);
            return;
        }
        
        bool isTaller = false;
        root = add(root, value, isTaller);
    }

    Node *remove(Node *node, const T& value, bool &isShorter, bool found)
    {
        if (node->data > value)
        {
            node->pLeft = remove(node->pLeft, value, isShorter, found);
            if (isShorter)
            {
                bool dummyTaller = false;
                node = balanceRight(node, dummyTaller, isShorter);
            }
        }else if (node->data < value || (node->data == value && found && node->pRight != nullptr))
        {
            node->pRight = remove(node->pRight, value, isShorter, found);
            if (isShorter)
            {
                bool dummyTaller = false;
                node = balanceLeft(node, dummyTaller, isShorter);
            }
        }else
        {
            if (node->pLeft == nullptr)
            {
                Node *deletedNode = node;
                node = node->pRight;
                isShorter = true;
                delete deletedNode;
            }else if (node->pRight == nullptr)
            {
                Node *deletedNode = node;
                node = node->pLeft;
                isShorter = true;
                delete deletedNode;
            }else
            {
                Node *leftNode = node->pLeft;
                Node *predecessor = leftNode;
                while (predecessor->pRight != nullptr)
                {
                    predecessor = predecessor->pRight;
                }
                node->data = predecessor->data;
                node->pLeft = remove(node->pLeft, node->data, isShorter, true);
                if (isShorter)
                {
                    bool dummyTaller = false;
                    node = balanceRight(node, dummyTaller, isShorter);
                }
            }
        }
        return node;
    }

    void remove(const T &value)
    {
        if (root == nullptr)
        {
            return;
        }
        
        bool isShorter = false;
        bool found = false;
        root = remove(root, value, isShorter, found);
    }

    class Node
    {
    private:
        T data;
        Node *pLeft, *pRight;
        BalanceValue balance;
        friend class AVLTree<T>;

    public:
        Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
        ~Node() {}
    };
};

#endif