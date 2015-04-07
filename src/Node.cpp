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

Node::Node()
    :_parent(nullptr), _left(nullptr), _right(nullptr), _data(0)
{}



bool Node::check(){
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


bool Node::nodeCheck(){
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

Node* Node::getParent(){
	return _parent;
}

