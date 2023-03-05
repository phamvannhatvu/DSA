//Pass problem: https://leetcode.com/problems/balance-a-binary-search-tree/description/
//Solution: https://leetcode.com/problems/balance-a-binary-search-tree/submissions/909725788/
#ifndef AVL_TREE_H
#define AVL_TREE_H

template<class T>
class AVLTree
{
public:
    class BalancedNode
    {
    public:
        int height;
        BalancedNode *parent;
        BalancedNode *left;
        BalancedNode *right;
        T value;
        BalancedNode(const T &value) : value(value), height(1), parent(nullptr), left(nullptr), right(nullptr) 
        {

        }
    };
private:
    BalancedNode *root;
    void rotateLeft(BalancedNode*);
    void rotateRight(BalancedNode*);
    void inOrderTranverse(BalancedNode*);
    void updateHeight(BalancedNode*);
    int getBalanceFactor(BalancedNode*);
    void balanceTree(BalancedNode*);
public:
    void insert(const T &item);
    void remove(const T &item);
    void inOrderTranverse();
    AVLTree() : root(nullptr)
    {

    }
    ~AVLTree()
    {
        while (root != nullptr) remove(root->value);
    }
};

template<class T>
void AVLTree<T>::inOrderTranverse(BalancedNode *root)
{
    if (root == nullptr) return;
    inOrderTranverse(root->left);
    std::cout << root->value << "(";
    std::cout << (root->parent == nullptr ? -1 : root->parent->value) << ',';
    std::cout << (root->left == nullptr ? -1 : root->left->value) << ',';
    std::cout << (root->right == nullptr ? -1 : root->right->value) << ") ";
    inOrderTranverse(root->right);
}

template<class T>
void AVLTree<T>::inOrderTranverse()
{
    inOrderTranverse(root);
}

template<class T>
void AVLTree<T>::remove(const T &item) 
{    
    if (root == nullptr) return;
    if (root->left == nullptr && root->right == nullptr)
    {
        if (root->value == item)
        {   
            delete root;
            root = nullptr;
        }
        return;
    }

    BalancedNode *node = root;
    BalancedNode *parent = nullptr;
    while (node != nullptr && node->value != item)
    {
        parent = node;
        if (node->value > item)
        {
            node = node->left;
        }else
        {
            node = node->right;
        }
    }

    if (node == nullptr) return;
    
    BalancedNode *deletedNode = node;
    if (node->left == nullptr)
    {
        if (parent != nullptr)
        {
            if (parent->left == node) 
            {
                parent->left = node->right;
            }else
            {
                parent->right = node->right;
            }
        }else root = node->right;
        if (node->right != nullptr) node->right->parent = parent;
    }else if (node->right == nullptr)
    {
        if (parent != nullptr)
        {
            if (parent->left == node)
            {
                parent->left = node->left;
            }else
            {
                parent->right = node->left;
            }
        }else root = node->left;
        node->left->parent = parent;
    }else
    {
        BalancedNode* predecessor = node->left;
        BalancedNode* predecessorParent = node;

        while (predecessor->right != nullptr)
        {
            predecessorParent = predecessor;
            predecessor = predecessor->right;
        }
        
        node->value = predecessor->value;
        if (predecessorParent->left == predecessor)
        {
            predecessorParent->left = predecessor->left;
        }else
        {
            predecessorParent->right = predecessor->left;
        }
        if (predecessor->left != nullptr) predecessor->left->parent = predecessorParent;
        deletedNode = predecessor;
        parent = predecessorParent;
    }
    delete deletedNode;
    updateHeight(parent);
    balanceTree(parent);
}

template<class T>
void AVLTree<T>::insert(const T &item) 
{
    if (root == nullptr) 
    {
        root = new BalancedNode(item);
        return;
    }
    BalancedNode* node = root;
    BalancedNode* parent = nullptr;

    while (node != nullptr) 
    {
        parent = node;
        if (node->value > item)
        {
            node = node->left;
        }else 
        {
            node = node->right;
        }
    }
    
    if (parent->value > item) 
    {
        parent->left = new BalancedNode(item);
        parent->left->parent = parent;
    }else
    {
        parent->right = new BalancedNode(item);
        parent->right->parent = parent;
    }
    updateHeight(parent);
    balanceTree(parent);
}

template<class T>
void AVLTree<T>::balanceTree(BalancedNode *node)
{
    while (node != nullptr) 
    {
        int balanceFactor = getBalanceFactor(node);
        //out of balance at right subtree 
        if (balanceFactor == 2)
        {
            if (getBalanceFactor(node->right) == -1)
            {
                rotateRight(node->right);
                rotateLeft(node);
            }else
            {
                rotateLeft(node);
            }
            node = node->parent;
        }else if (balanceFactor == -2)
        {
            if (getBalanceFactor(node->left) == 1)
            {
                rotateLeft(node->left);
                rotateRight(node);
            }else 
            {
                rotateRight(node);
            }
            node = node->parent;
        }
        updateHeight(node->parent);
        node = node->parent;
    }

    while (root->parent != nullptr) root = root->parent;
}

template<class T>
void AVLTree<T>::rotateLeft(BalancedNode* root)
{
    BalancedNode* rightNode = root->right;
    
    root->right = rightNode->left;
    if (root->right != nullptr) root->right->parent = root;

    rightNode->left = root;
    rightNode->parent = root->parent;
    if (root->parent != nullptr)
    {
        if (root->parent->left == root)
        {
            root->parent->left = rightNode;
        }else
        {
            root->parent->right = rightNode;
        }
    }
    root->parent = rightNode;

    updateHeight(root);
    updateHeight(root->parent);
}

template<class T>
void AVLTree<T>::rotateRight(BalancedNode* root)
{
    BalancedNode* leftNode = root->left;

    root->left = leftNode->right;
    if (root->left != nullptr) root->left->parent = root;

    leftNode->right = root;
    leftNode->parent = root->parent;
    if (root->parent != nullptr)
    {
        if (root->parent->left == root)
        {
            root->parent->left = leftNode;
        }else
        {
            root->parent->right = leftNode;
        }
    }
    root->parent = leftNode;

    updateHeight(root);
    updateHeight(root->parent);
}

template<class T>
void AVLTree<T>::updateHeight(BalancedNode* root)
{
    if (root == nullptr) return;
    root->height = (root->left == nullptr ? 0 : root->left->height) + 1;
    if (root->height < (root->right == nullptr ? 0 : root->right->height) + 1)
    {
        root->height = (root->right == nullptr ? 0 : root->right->height) + 1;
    }
}

template<class T>
int AVLTree<T>::getBalanceFactor(BalancedNode* root)
{
    return ((root->right == nullptr ? 0 : root->right->height) - (root->left == nullptr ? 0 : root->left->height));
}
#endif