/*
 * =====================================================================================
 *
 *       Filename:  NodeTree.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  20/05/2015 15:40:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Samuel BOURASSEAU (SB), samuel.bourasseau@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "NodeTree.hpp"

#include <cassert>
#include <deque>

NodeTree::NodeTree()
{
    _root = new Node(this, nullptr, nullptr, nullptr);
}

NodeTree::NodeTree(const Node& n)
{
    _root = new Node(n);
    _root->_setTree(this);
}

NodeTree::NodeTree(const NodeTree& nt)
    :_root(nt._root->clone())
{
    _root->_setTree(this);
}

void
NodeTree::insert(int E)
{
    Node* node = _root->insert(E);
    node->_setTree(this);
}

void
NodeTree::insertBalanced(int E)
{
    Node* node = _root->insertBalanced(E);
    node->_setTree(this);
}

void
NodeTree::insertNLeaves(int n)
{
    delete _root;
    _root = new Node(this, nullptr, nullptr, nullptr);

    Node* node;

    for(int i = 0; i < n-1; i++)
    {
        // Choose a random leaf
        node = _root;
        while(!node->isLeftFree() || !node->isRightFree())
        {
            if(!node->isLeftFree() && !node->isRightFree())
            {
                int side = Node::binaryPick(Node::rng);
                node = (side == 0) ? node->getLeft() : node->getRight();
            }
            else if(!node->isLeftFree())
            {
                node = node->getLeft();
            }
            else if(!node->isRightFree())
            {
                node = node->getRight();
            }
        }

        node->insertLeaf();
    }

    int count = 0;
    for(Node::NodeIter* it = _root->begin(); it->hasNext();)
    {
        Node* n = it->getNext();
        n->setData(count++);
    }
}

void
NodeTree::insertNBalanced(int n)
{
    delete _root;
    _root = new Node(this, nullptr, nullptr, nullptr);

    std::deque<Node*> nodes;
    for(int i = 0; i < n; i++)
    {
        nodes.push_back(new Node(this, nullptr, nullptr, nullptr));
    }

    while(nodes.size() > 2)
    {
        Node* A = nodes.front();
        nodes.pop_front();
        Node* B = nodes.front();
        nodes.pop_front();

        Node* parent = new Node(this, nullptr, A, B);
        nodes.push_back(parent);

        A->_parent = parent;
        B->_parent = parent;
    }

    Node* A = nodes.front();
    nodes.pop_front();
    Node* B = nodes.front();
    nodes.pop_front();

    _root->_left = A;
    _root->_right = B;
    A->_parent = _root;
    B->_parent = _root;

    int count = 0;
    for(Node::NodeIter* it = _root->begin(); it->hasNext();)
    {
        Node* n = it->getNext();
        n->setData(count++);
    }
}

bool
NodeTree::check() const
{
    return _root->check();
}

Node*
NodeTree::nodeAt(int num)
{
    return _root->nodeAt(num);
}

// Can only change root to a node that already is in the tree
void
NodeTree::setRoot(Node* n)
{
    // Should the node not be made root if it has parent or should it be orphaned ?
#if 0
    if(n->isOrphan())
    {
        _root = n;
    }
#else
    //TODO : check if the _tree correspond to this
    n->_parent = nullptr;
    _root = n;
#endif
}

int
NodeTree::leafCount()
{
    return _root->leafCount();
}

std::vector<Node*>
NodeTree::SPR_list_init(Node* noeud)
{
    std::vector<Node*> nodes;

    noeud->degraph();
#if DEBUG
    //std::cout << noeud->to_str() << std::endl;
#endif

    for(Node::NodeIter* it = _root->begin(); it->hasNext();)
    {
        Node* n = it->getNext();
        if(n)
        {
            nodes.push_back(n);
        }
    }

    return nodes;
}

void
NodeTree::SPR_list(Node* noeud, std::vector<Node*>& nodes)
{
    int count = 0;

    for(unsigned int i = 0; i < nodes.size(); ++i)
    {
        if(nodes[i]->regraph(noeud))
        {
            count++;
        }
        noeud->degraph();
    }

#if DEBUG
    std::cout << count << "degraph/regraph" << std::endl;
#endif

}

void
NodeTree::SPR_rec(Node* noeud)
{
    noeud->degraph();
    _root->SPR_rec(noeud);
}

void
NodeTree::SPR_ite(Node* noeud)
{
    noeud->degraph();
    _root->SPR_ite(noeud);
}
