#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::cout;
using std::cin;
using std::queue;

class Node
{
private:
    vector<int> adjIndex;
    bool isMarked;
    int numEdgeIn;
    bool isFinished;

public:
    Node()
    {
        isMarked = false;
        numEdgeIn = 0;
        isFinished = false;
    }
    
    void addNode(int nodeIndex) 
    {
        adjIndex.push_back(nodeIndex);
    }

    const vector<int>& getAdj() {
        return adjIndex;
    }

    void visit() 
    {
        isMarked = true;
    }

    bool isVisited() 
    {
        return isMarked;
    }

    void updateEdgeIn() 
    {
        ++numEdgeIn;
    }

    void removeOneEdgeIn()
    {
        --numEdgeIn;
    }

    bool isPointIn() 
    {
        return numEdgeIn;
    }

    void finish()
    {
        isFinished = true;
    }

    bool isFinish() 
    {
        return isFinished;
    }
};

void topoDfs(Node* nodeList, int nodeIndex, vector<int>& topoOrder, bool &hasCycle) 
{
    Node &node = nodeList[nodeIndex];
    const vector<int>& adj = node.getAdj();
    node.visit();

    for (auto v: adj) 
    {
        if (!nodeList[v].isVisited())
        {
            topoDfs(nodeList, v, topoOrder, hasCycle);
        }else if (!nodeList[v].isFinish())
        {
            hasCycle = true;
            return;
        }
    }

    node.finish();
    topoOrder.push_back(nodeIndex);
}

void topoBfs(Node *nodeList, int numNodes, vector<int>& topoOrder)
{
    queue<int> q;
    for (int i = 0; i < numNodes; ++i)
    {
        if (!nodeList[i].isPointIn())
        {
            q.push(i);
        }
    }

    while (q.size())
    {
        int u = q.front();
        q.pop();
        topoOrder.push_back(u);
        
        const vector<int> &uAdj = nodeList[u].getAdj();
        for (auto v: uAdj)
        {
            Node &vNode = nodeList[v];
            if (vNode.isPointIn())
            {
                vNode.removeOneEdgeIn();
                if (!vNode.isPointIn())
                {
                    q.push(v);
                } 
            }
        }
    }

    if (topoOrder.size() < numNodes) topoOrder.clear();
}

int main() 
{
    int n, m;
    cin >> n >> m;

    Node *nodes = new Node[n];
    while (m--) 
    {
        int u, v;
        cin >> u >> v;
        nodes[v].addNode(u);
        nodes[u].updateEdgeIn();
    }

    vector<int> topoOrder;
    bool hasCycle = false;
    for (int i = 0; i < n; ++i)
    {
        if (!nodes[i].isVisited() && !nodes[i].isPointIn())
            topoDfs(nodes, i, topoOrder, hasCycle);
    }
    
    cout << "DFS: ";
    if (hasCycle || topoOrder.size() < n)
        topoOrder.clear();
    for (auto v: topoOrder)
        cout << v << ' ';
    
    cout << "\n\nBFS: ";
    topoOrder.clear();
    topoBfs(nodes, n, topoOrder);
    for (auto v: topoOrder)
        cout << v << ' ';
    delete[] nodes;
    return 0;    
}