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
Node::SPR(Node* noeud){
    noeud->degraph();
    Node * nodeActual=this;
    bool fin=false,remonte=false;
    while(fin==false)
    {
        if(remonte)// si on est en train de remonter
        {
            std::cout << "plop4" << std::endl;
            remonte=false;
            if(nodeActual->_parent!=nullptr)//si on est pas a la racine
            {
                if(nodeActual->_parent->_right!=nodeActual)//si on est dans le fils gauche
                {
                    if(nodeActual->_parent->_right!=nullptr)// si le fils droit est libre
                    {
                        nodeActual=nodeActual->_parent->_right;
                    }
                    else// s'il n'y a pas de fils droit
                    {
                        nodeActual=nodeActual->_parent;
                        remonte=true;
                    }
                }
                else//si on est dans le fils droit
                {
                    nodeActual=nodeActual->_parent;
                    remonte=true;
                }
            }
            else
            {
                fin =true;
            }
        }
    
        else
        {
            if(nodeActual==nullptr)
                std::cout << "pas normal" << std::endl;
            if(nodeActual->regraph(noeud))
            {
                std::cout << nodeActual->to_str() << std::endl;
                //std::cout << nodeActual->_right << std::endl;
                //std::cout << nodeActual->_left << std::endl;
                noeud->degraph();
            }
            if(nodeActual->_left!=nullptr)// si on peut aller a gauche
            {
                nodeActual=nodeActual->_left;
            }
            else if (nodeActual->_right!=nullptr)// si on peut aller a droite
            {
                nodeActual=nodeActual->_right;
            }
            else if((nodeActual->_parent)->_parent==nullptr)//si on est juste après la racine
            {
                if((nodeActual->_parent)->_right==nodeActual)   //si on est a droite
                {
                    fin =true;
                }
                else                                    //si on est a gauche
                {
                    if((nodeActual->_parent)->_right!=nullptr)
                    {
                        nodeActual=(nodeActual->_parent)->_right;
                    }
                    else
                    {
                        fin=true;              
                    }
                }
            }
            else if(nodeActual==((nodeActual->_parent)->_right))//si on est a droite du noeud _parent
            {
                remonte=true;
                nodeActual=nodeActual->_parent;
            }
            else// si on est a gauche du noeud _parent
            {
                if((nodeActual->_parent)->_right!=nullptr)
                {
                    std::cout << nodeActual->to_str() << std::endl;
                    nodeActual=(nodeActual->_parent)->_right;
                }
                else
                {
                    std::cout << "plop3" << std::endl;
                    nodeActual=nodeActual->_parent;
                    remonte=true;                
                }
            }
        }
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

