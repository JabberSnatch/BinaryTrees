/*
 * =====================================================================================
 *
 *       Filename:  node.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/04/2015 09:52:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Samuel BOURASSEAU (SB), samuel.bourasseau@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "Node.hpp"

#include <cassert>

using namespace std;

mt19937 Node::rng = mt19937(random_device()());
uniform_int_distribution<int> Node::binaryPick = uniform_int_distribution<int>(0, 1);

Node::Node(int data)
    :_parent(nullptr), _left(nullptr), _right(nullptr), _data(data)
{}

void
Node::insert(int E)
{
    if(_left == nullptr)
    {
        _left = new Node(E);
    }
    else if(_right == nullptr)
    {
        _right = new Node(E);
    }
    else
    {
        int side = binaryPick(rng);        

        if(side == 0)
        {
            _left->insert(E);
        }
        if(side == 1)
        {
            _right->insert(E);
        }
    }
}

void 
Node::degraph()
{
    if(!isOrphan())
    {
        if(_parent->_left == this)
        {
            _parent->_left = nullptr;
        }
        if(_parent->_right == this)
        {
            _parent->_right = nullptr;
        }

        _parent = nullptr;
    }
}

bool
Node::regraph(Node* child)
{
    bool success = false;

    if(child->isOrphan())
    {
        if(isLeftFree())
        {
            _left = child;
            _left->_parent = this;        
            success = true;
        }
        else if(isRightFree())
        {
            _right = child;
            _right->_parent = this;
            success = true;
        }
    }

#if DEBUG
    assert(findRoot()->check());
#endif

    return success;
}

//NOTE: check is supposed to be called on the root of a tree
bool 
Node::check()
{
    bool RES = false;

    if(isOrphan())
    {
        RES = true;
        RES &= nodeCheck();
    }

    return RES;
}

bool 
Node::nodeCheck()
{
    bool RES = false;
    
    if(isLeftFree() && isRightFree())
    {
        RES = true;
    }
    else
    {
        if(!isLeftFree())
        {
            if(_left->_getParent() == this)
            {
                RES = true;
                RES &= _left->nodeCheck();
            }
        }

        if(!isRightFree())
        {
            if(_right->_getParent() == this)
            {
                RES = true;
                RES &= _right->nodeCheck();
            }
        }
    }

    return RES;
}

Node*
Node::findRoot()
{
    Node* target = this;
    
    while(!target->isOrphan())
    {
        target = target->_parent;
    }

    return target;
}

bool
Node::isOrphan()
{
    return (_parent == nullptr);
}

bool
Node::isLeftFree()
{
    return (_left == nullptr);
}

bool
Node::isRightFree()
{
    return (_right == nullptr);
}

int 
Node::nbDescendants()
{
    int nb=0;

    if(_left!=nullptr)
    {
        nb += 1+ _left->nbDescendants();
    }
    if(_right!=nullptr)
    {
        nb += 1+ _right->nbDescendants();
    }

    return nb;
}

Node*
Node::nodeAt(int *num)
{
    if(*num==0)
        return this;
    else{
        Node* res;
        if(_left!= nullptr){
            (*num)--;
            res=_left->nodeAt(num);
            if(res!=nullptr)
                return res;
        }
        if(_right!= nullptr){
            if(*num!=0)
                (*num)--;
            res=_right->nodeAt(num);
            if(res!=nullptr)
                return res;
        }
    }
    return nullptr;
}

std::string
Node::to_str()
{
    return _to_str("", 0);
}

Node*
Node::_getParent()
{
    return _parent;
}

void
Node::_setParent(Node* parent)
{
    _parent = parent;
}

string
Node::_to_str(string acc, int depth)
{
    for(int i = 0; i < depth; ++i)
    {
        acc += " ";
    }

    acc += "+->" + to_string(_data) + "\n";

    if(_left != nullptr)
    {
        acc = _left->_to_str(acc, depth+1);
    }
    if(_right != nullptr)
    {
        acc = _right->_to_str(acc, depth+1);
    }

    return acc;
}


