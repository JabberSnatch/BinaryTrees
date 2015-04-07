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
Node::check()
{
    if(_parent!=nullptr)
        return false;
    else
    {
        if((_left==nullptr)&&(_right==nullptr)){
            return true;
        }
        else{
            if(_left!=nullptr)
            {
                if(_left->_getParent() != this)
                    return false;
            }
            if(_right!=nullptr)
            {
                if(_right->_getParent() != this)
                    return false;
            }
            return (_right->nodeCheck()&&_left->nodeCheck());
        }
    }
}


bool 
Node::nodeCheck(){
    if((_left==nullptr)&&(_right==nullptr)){
        return true;
    }
    else
    {
        bool leftChecked=true,rightChecked=true;
        if(_left!=nullptr)
        {
            if(_left->_getParent()!=this)
                return false;
            leftChecked=_left->nodeCheck();
        }
        if(_right!=nullptr)
        {
            if(_right->_getParent()!=this)
                return false;
            rightChecked=_right->nodeCheck();
        }
        return ( rightChecked && leftChecked );
    }
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

int 
Node::nombreFils()
{
	int nb=0;
	if(_left!=nullptr)
		nb=nb+1+ _left->nombreFils();
	if(_right!=nullptr)
		return (nb+1+ _right->nombreFils());
	return nb;
}

Node*
Node::nodeAt(int *num){
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


Node *  
Node::_getParent()
{
	return _parent;
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

std::string
Node::_to_str(std::string acc, int depth)
{
    for(int i = 0; i < depth; ++i)
    {
        acc += " ";
    }

    acc += "-N:" + std::to_string(_data) + "\n";

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

