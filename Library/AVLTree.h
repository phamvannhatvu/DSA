#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "BinarySearchTree.h"

enum class BanlanceFactor
{
    LEFT_HIGHER,
    RIGHT_HIGHER,
    EQUAL_HEIGHT
};

template<class T>
class AVLTree : public BSTree<T>
{
public:
    class BalancedNode : public BSTree<T>::Node
    {
    public:
        BanlanceFactor balanceFactor;
        BalancedNode(const T &value) : BSTree<T>::Node(value), balanceFactor(BanlanceFactor::EQUAL_HEIGHT) {}
    };
private:
    BalancedNode* insert(BalancedNode*, const T&, bool&);
    BalancedNode* remove(BalancedNode*, const T&, bool&, bool);
    BalancedNode* leftBalanceOnRemove(BalancedNode*, bool&);
    BalancedNode* rightBalanceOnRemove(BalancedNode*, bool&);
    BalancedNode* leftBalance(BalancedNode*, bool&);
    BalancedNode* rightBalance(BalancedNode*, bool&);
    BalancedNode* rotateLeft(BalancedNode*);
    BalancedNode* rotateRight(BalancedNode*);
    void inOrderTranverse(BalancedNode*);
public:
    void insert(const T &item) override;
    void remove(const T &item) override;
    void inOrderTranverse();
};

template<class T>
void AVLTree<T>::inOrderTranverse(BalancedNode *root)
{
    if (root == nullptr) return;
    inOrderTranverse((BalancedNode*)root->left);
    std::cout << root->value << "(";
    std::cout << (root->left == nullptr ? -1 : root->left->value) << ',';
    std::cout << (root->right == nullptr ? -1 : root->right->value) << ',';
    std::cout << (int)root->balanceFactor << ") ";
    inOrderTranverse((BalancedNode*)root->right);
}

template<class T>
void AVLTree<T>::inOrderTranverse()
{
    inOrderTranverse((BalancedNode*) BSTree<T>::getRoot());
}

template<class T>
void AVLTree<T>::remove(const T &item) 
{    
    bool isShorter = false;
    BSTree<T>::setRoot(remove((BalancedNode*)BSTree<T>::getRoot(), item, isShorter, false));
}

template<class T>
void AVLTree<T>::insert(const T &item) 
{
    bool isTaller = false;
    BSTree<T>::setRoot(insert((BalancedNode*)BSTree<T>::getRoot(), item, isTaller));
}

template<class T>
typename AVLTree<T>::BalancedNode* AVLTree<T>::remove(BalancedNode* root, const T& item, bool &isShorter, bool founded)
{
    if (root == nullptr)
    {
        isShorter = false;
        return nullptr;
    }else if (item < root->value)
    {
        root->left = remove((BalancedNode*)root->left, item, isShorter, founded);
        if (isShorter)
        {
            root = rightBalanceOnRemove(root, isShorter);
        }
    }else if (item > root->value || (founded && root->right != nullptr))
    {
        root->right = remove((BalancedNode*)root->right, item, isShorter, founded);
        if (isShorter)
        {
            root = leftBalanceOnRemove(root, isShorter);
        }
    }else
    {
        BalancedNode* deletedNode = root;
        if (root->right == nullptr)
        {
            BalancedNode* newNode = (BalancedNode*)root->left;
            isShorter = true;
            delete deletedNode;
            return newNode;
        }else if (root->left == nullptr)
        {
            BalancedNode* newNode = (BalancedNode*)root->right;
            isShorter = true;
            delete deletedNode;
            return newNode;
        }else
        {
            BalancedNode* predec = (BalancedNode*)root->left;
            while (predec->right != nullptr) 
            {
                predec = (BalancedNode*)predec->right;
            }
            
            root->value = predec->value;
            root->left = remove((BalancedNode*)root->left, predec->value, isShorter, 1);
            if (isShorter)
            {
                root = rightBalanceOnRemove(root, isShorter);
            }
        }
    }
    return root;
}

template<class T>
typename AVLTree<T>::BalancedNode* AVLTree<T>::leftBalanceOnRemove(BalancedNode* root, bool &isShorter)
{
    if (root->balanceFactor == BanlanceFactor::RIGHT_HIGHER)
    {
        root->balanceFactor = BanlanceFactor::EQUAL_HEIGHT;
    }else if (root->balanceFactor == BanlanceFactor::EQUAL_HEIGHT)
    {
        root->balanceFactor = BanlanceFactor::LEFT_HIGHER;
        isShorter = false;
    }else
    {
        BalancedNode* leftTree = (BalancedNode*)root->left;
        if (leftTree->balanceFactor == BanlanceFactor::RIGHT_HIGHER)
        {
            BalancedNode* rightTree = (BalancedNode*)leftTree->right;
            if (rightTree->balanceFactor == BanlanceFactor::LEFT_HIGHER)
            {
                root->balanceFactor = BanlanceFactor::RIGHT_HIGHER;
                leftTree->balanceFactor = BanlanceFactor::EQUAL_HEIGHT;
            }else if (rightTree->balanceFactor == BanlanceFactor::EQUAL_HEIGHT)
            {
                root->balanceFactor = BanlanceFactor::EQUAL_HEIGHT;
                leftTree->balanceFactor = BanlanceFactor::EQUAL_HEIGHT;
            }else
            {
                root->balanceFactor = BanlanceFactor::EQUAL_HEIGHT;
                leftTree->balanceFactor = BanlanceFactor::LEFT_HIGHER;
            }
            rightTree->balanceFactor = BanlanceFactor::EQUAL_HEIGHT;
            root->left = rotateLeft(leftTree);
            root = rotateRight(root);
        }else
        {
            if (leftTree->balanceFactor == BanlanceFactor::LEFT_HIGHER)
            {
                root->balanceFactor = BanlanceFactor::EQUAL_HEIGHT;
                leftTree->balanceFactor = BanlanceFactor::EQUAL_HEIGHT;
            }else 
            {
                root->balanceFactor = BanlanceFactor::LEFT_HIGHER;
                leftTree->balanceFactor = BanlanceFactor::RIGHT_HIGHER;
                isShorter = false;
            }
            root = rotateRight(root);
        }
    }
    return root;
}

template<class T>
typename AVLTree<T>::BalancedNode* AVLTree<T>::rightBalanceOnRemove(BalancedNode* root, bool &isShorter)
{
    if (root->balanceFactor == BanlanceFactor::LEFT_HIGHER)
    {
        root->balanceFactor = BanlanceFactor::EQUAL_HEIGHT;
    }else if (root->balanceFactor == BanlanceFactor::EQUAL_HEIGHT)
    {
        root->balanceFactor = BanlanceFactor::RIGHT_HIGHER;
        isShorter = false;
    }else
    {
        BalancedNode* rightTree = (BalancedNode*)root->right;
        if (rightTree->balanceFactor == BanlanceFactor::LEFT_HIGHER)
        {
            BalancedNode* leftTree = (BalancedNode*)rightTree->left;
            if (leftTree->balanceFactor == BanlanceFactor::LEFT_HIGHER)
            {
                root->balanceFactor = BanlanceFactor::EQUAL_HEIGHT;
                rightTree->balanceFactor = BanlanceFactor::RIGHT_HIGHER;
            }else if (leftTree->balanceFactor == BanlanceFactor::EQUAL_HEIGHT)
            {
                root->balanceFactor = BanlanceFactor::EQUAL_HEIGHT;
                rightTree->balanceFactor = BanlanceFactor::EQUAL_HEIGHT;
            }else
            {
                root->balanceFactor = BanlanceFactor::LEFT_HIGHER;
                rightTree->balanceFactor = BanlanceFactor::EQUAL_HEIGHT;
            }
            leftTree->balanceFactor = BanlanceFactor::EQUAL_HEIGHT;
            root->right = rotateRight(rightTree);
            root = rotateLeft(root);
        }else
        {
            if (rightTree->balanceFactor == BanlanceFactor::RIGHT_HIGHER)
            {
                root->balanceFactor = BanlanceFactor::EQUAL_HEIGHT;
                rightTree->balanceFactor = BanlanceFactor::EQUAL_HEIGHT;
            }else 
            {
                root->balanceFactor = BanlanceFactor::RIGHT_HIGHER;
                rightTree->balanceFactor = BanlanceFactor::LEFT_HIGHER;
                isShorter = false;
            }
            root = rotateLeft(root);
        }
    }
    return root;
}

template<class T>
typename AVLTree<T>::BalancedNode* AVLTree<T>::insert(BalancedNode *root, const T& item, bool& isTaller)
{
    if (root == nullptr)
    {
        root = new BalancedNode(item);
        isTaller = true;
    }else
    {
        if (item < root->value)
        {
            root->left = insert((BalancedNode*)root->left, item, isTaller);
            //left subtree is taller
            if (isTaller)
            {
                if (root->balanceFactor == BanlanceFactor::LEFT_HIGHER)
                {
                    root = leftBalance(root, isTaller);
                }else if (root->balanceFactor == BanlanceFactor::RIGHT_HIGHER)
                {
                    root->balanceFactor = BanlanceFactor::EQUAL_HEIGHT;
                    isTaller = false;
                }else
                {
                    root->balanceFactor = BanlanceFactor::LEFT_HIGHER;
                }
            }
        }else
        {
            root->right = insert((BalancedNode*)root->right, item, isTaller);
            //right subtree is taller
            if (isTaller)
            {
                if (root->balanceFactor == BanlanceFactor::RIGHT_HIGHER)
                {
                    root = rightBalance(root, isTaller);
                }else if (root->balanceFactor == BanlanceFactor::LEFT_HIGHER)
                {
                    root->balanceFactor = BanlanceFactor::EQUAL_HEIGHT;
                    isTaller = false;
                }else
                {
                    root->balanceFactor = BanlanceFactor::RIGHT_HIGHER;
                }
            }
        }
    }
    return root;
}

template<class T>
typename AVLTree<T>::BalancedNode* AVLTree<T>::leftBalance(BalancedNode* root, bool &isTaller)
{
    BalancedNode* leftTree = (BalancedNode*)root->left;
    if (leftTree->balanceFactor == BanlanceFactor::LEFT_HIGHER)
    {
        root->balanceFactor = BanlanceFactor::EQUAL_HEIGHT;
        leftTree->balanceFactor = BanlanceFactor::EQUAL_HEIGHT;
        root = rotateRight(root);
        isTaller = false;
    }else
    {
        BalancedNode* rightTree = (BalancedNode*)leftTree->right;
        if (rightTree->balanceFactor == BanlanceFactor::LEFT_HIGHER)
        {
            root->balanceFactor = BanlanceFactor::RIGHT_HIGHER;
            leftTree->balanceFactor = BanlanceFactor::EQUAL_HEIGHT;
        }else if (rightTree->balanceFactor == BanlanceFactor::EQUAL_HEIGHT)
        {
            root->balanceFactor = BanlanceFactor::EQUAL_HEIGHT;
            leftTree->balanceFactor = BanlanceFactor::EQUAL_HEIGHT;
        }else
        {
            root->balanceFactor = BanlanceFactor::EQUAL_HEIGHT;
            leftTree->balanceFactor = BanlanceFactor::LEFT_HIGHER;
        }
        rightTree->balanceFactor = BanlanceFactor::EQUAL_HEIGHT;
        root->left = rotateLeft(leftTree);
        root = rotateRight(root);
        isTaller = false;
    }   
    return root;
}

template<class T>
typename AVLTree<T>::BalancedNode* AVLTree<T>::rightBalance(BalancedNode* root, bool &isTaller)
{
    BalancedNode* rightTree = (BalancedNode*)root->right;
    if (rightTree->balanceFactor == BanlanceFactor::RIGHT_HIGHER)
    {
        root->balanceFactor = BanlanceFactor::EQUAL_HEIGHT;
        rightTree->balanceFactor = BanlanceFactor::EQUAL_HEIGHT;
        root = rotateLeft(root);
        isTaller = false;
    }else
    {
        BalancedNode* leftTree = (BalancedNode*)rightTree->left;
        if (leftTree->balanceFactor == BanlanceFactor::LEFT_HIGHER)
        {
            root->balanceFactor = BanlanceFactor::EQUAL_HEIGHT;
            rightTree->balanceFactor = BanlanceFactor::RIGHT_HIGHER;
        }else if (leftTree->balanceFactor == BanlanceFactor::EQUAL_HEIGHT)
        {
            root->balanceFactor = BanlanceFactor::EQUAL_HEIGHT;
            rightTree->balanceFactor = BanlanceFactor::EQUAL_HEIGHT;
        }else
        {
            root->balanceFactor = BanlanceFactor::LEFT_HIGHER;
            rightTree->balanceFactor = BanlanceFactor::EQUAL_HEIGHT;
        }
        leftTree->balanceFactor = BanlanceFactor::EQUAL_HEIGHT;
        root->right = rotateRight(rightTree);
        root = rotateLeft(root);
        isTaller = false;
    }   
    return root;
}

template<class T>
typename AVLTree<T>::BalancedNode* AVLTree<T>::rotateLeft(BalancedNode* root)
{
    BalancedNode* rightTree = (BalancedNode*)root->right;
    root->right = rightTree->left;
    rightTree->left = root;
    return rightTree;
}

template<class T>
typename AVLTree<T>::BalancedNode* AVLTree<T>::rotateRight(BalancedNode* root)
{
    BalancedNode* leftTree = (BalancedNode*)root->left;
    root->left = leftTree->right;
    leftTree->right = root;
    return leftTree;
}

#endif