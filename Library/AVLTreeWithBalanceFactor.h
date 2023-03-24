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

void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}

void printInteger(int &n)
{
    cout << n << " ";
}

template<class T>
class AVLTree
{
public:
    class Node;
private:
    Node *root;
protected:
    int getHeightRec(Node *node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }
public:
    int getHeight()
    {
        return this->getHeightRec(this->root);
    }
    AVLTree() : root(nullptr) {}
    ~AVLTree(){}

    void printTreeStructure()
    {
        int height = this->getHeight();
        if (this->root == NULL)
        {
            cout << "NULL\n";
            return;
        }
        queue<Node *> q;
        q.push(root);
        Node *temp;
        int count = 0;
        int maxNode = 1;
        int level = 0;
        int space = pow(2, height);
        printNSpace(space / 2);
        while (!q.empty())
        {
            temp = q.front();
            q.pop();
            if (temp == NULL)
            {
                cout << " ";
                q.push(NULL);
                q.push(NULL);
            }
            else
            {
                cout << temp->data;
                q.push(temp->pLeft);
                q.push(temp->pRight);
            }
            printNSpace(space);
            count++;
            if (count == maxNode)
            {
                cout << endl;
                count = 0;
                maxNode *= 2;
                level++;
                space /= 2;
                printNSpace(space / 2);
            }
            if (level == height)
                return;
        }
    }

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