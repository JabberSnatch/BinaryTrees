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

NodeTree::NodeTree()
{
    _root = new Node();
    _root->_setTree(this);
}

NodeTree::NodeTree(const Node& n)
{
    _root = new Node(n);
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
    assert(n->getTree() == this);
    // Should the node not be made root if it has parent or should it be orphaned ?
#if 0
    if(n->isOrphan())
    {
        _root = n;
    }
#else
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
    std::cout << noeud->to_str() << std::endl;
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
    int expectedSize = size()+nodes.size();

    for(unsigned int i = 0; i < nodes.size(); ++i)
    {
        if(nodes[i]->regraph(noeud))
        {
#if DEBUG
            assert(expectedSize = size());
#endif
            count++;
        }
        noeud->degraph();
    }

#if DEBUG
    std::cout << count << "degraph/regraph" << std::endl;
#endif

}

