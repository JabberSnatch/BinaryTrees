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
    _root->insert(E);
    // Should Node's insert return a pointer to the node now holding the data ?
}

void
NodeTree::insertBalanced(int E)
{
    _root->insertBalanced(E);
    // ditto
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
    n->_parent = nullptr;
    _root = n;
#endif
}

int
NodeTree::leafCount()
{
    return _root->leafCount();
}
