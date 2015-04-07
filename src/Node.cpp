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

Node::Node(int data)
    :_parent(nullptr), _left(nullptr), _right(nullptr), _data(data)
{}


bool 
Node::check(){
	if(_parent!=nullptr)
		return false;
	else{
		if((_left==nullptr)&&(_right==nullptr))
			return true;
		else{
			if(_left!=nullptr){
				if(_left->getParent() != this)
					return false;
			}
			if(_right!=nullptr){
				if(_right->getParent() != this)
					return false;
			}
			return (_right->nodeCheck()&&_left->nodeCheck());
		}
	}
}


bool 
Node::nodeCheck(){
	if((_left==nullptr)&&(_right==nullptr))
		return true;
	else{
		bool leftChecked=true,rightChecked=true;
		if(_left!=nullptr){
			if(_left->getParent()!=this)
				return false;
			leftChecked=_left->nodeCheck();
		}
		if(_right!=nullptr){
			if(_right->getParent()!=this)
				return false;
			rightChecked=_right->nodeCheck();
		}
		return ( rightChecked && leftChecked );
	}
}

Node *  
Node::getParent(){
	return _parent;
	
}

void 
Node::degraph()
{
    if(_parent)
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

    return success;
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

void
Node::_setParent(Node* parent)
{
    _parent = parent;
}

