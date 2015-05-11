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
 *                  Rodolphe CHARLOT, charlot.rodolphe@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "Node.hpp"

#include <cassert>


using namespace std;

mt19937 Node::rng = mt19937(random_device()());
uniform_int_distribution<int> Node::binaryPick = uniform_int_distribution<int>(0, 1);

Node::Node(int data, Node* parent)
    :_parent(parent), _left(nullptr), _right(nullptr), _data(data), _free(false)
{}

Node::Node(const Node& n)
    :_parent(nullptr), _left(nullptr), _right(nullptr), _data(n._data), _free(n.isFree())
{
    if(!n.isLeftFree())
    {
        _left = n._left->clone();
        _left->_parent = this;
    }

    if(!n.isRightFree())
    {
        _right = n._right->clone();
        _right->_parent = this;
    }

#if DEBUG
    assert(findRoot()->check());
#endif

}

Node*
Node::clone()
{
    return new Node(*this);
}

Node&
Node::operator =(const Node& n)
{
    if(this != &n)
    {
        _parent = nullptr;
        _data = n._data;
        _free = n.isFree();

        _left = nullptr;
        if(!n.isLeftFree())
        {
            _left = new Node(*(n._left));
        }

        _right = nullptr;
        if(!n.isRightFree())
        {
            _right = new Node(*(n._right));
        }
    }

    return *this;
}

Node::~Node()
{
    degraph();

    delete _left;
    delete _right;
}

void
Node::insert(int E)
{
    if(_free)
    {
        _data = E;
        _free = false;
    }
    else if(isLeftFree())
    {
        _left = new Node(E, this);
    }
    else if(isRightFree())
    {
        _right = new Node(E, this);
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
            if(_left->getParent() == this)
            {
                RES = true;
                RES &= _left->nodeCheck();
            }
        }

        if(!isRightFree())
        {
            if(_right->getParent() == this)
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


int 
Node::descendantCount() const
{
    int num=0;
    if(!isLeftFree())
    {
        num+=(_left->descendantCount()+1);
    }
    if(!isRightFree())
    {
        num+=(_right->descendantCount()+1);
    }
    return num;
}

Node*
Node::nodeAt(int num)
{
    Node* res=nullptr;
    if(num==0)
        res= this;
    else 
    {
        num--;
        if(!isLeftFree())
        {
            res=_left->nodeAt(num);
            num-=(_left->descendantCount()+1);
        }
        if(!isRightFree()) 
        {
            if(res==nullptr)
            {
                res=_right->nodeAt(num);
            }
        }
    }
    return res;
}

int
Node::dataCount()
{ 
    int res=_data;
    
    if(!isLeftFree())
    {
        res+=_left->dataCount();
    }
    if(!isRightFree())
    {
        res+=_right->dataCount();
    }
    
    return res;
}

int 
Node::nodeCount()
{
    return descendantCount()+1;
}

std::string 
Node::newick()
{
    
    std::string res;
    if(!isLeftFree() & !isRightFree())
    {
        res="(";
        res+=(_left->newick());
        res+=(","+_right->newick());
        res+=")";
    }
    else if(!isLeftFree()& isRightFree())
    {
        res= _left->newick();
    }
    else if(isLeftFree()& !isRightFree())
    {
        res= _left->newick();
    }
    else if(isRightFree() & isLeftFree())
    {
        stringstream ss;
        ss << _data;
        res = ss.str();
    }
    else
    {
    cerr << "erreur dans newick, arbre mal formé" << endl;
    }
    
    return res;
}

string
Node::to_str()
{
    return _to_str("", 0);
}

string
Node::_to_str(string acc, int depth)
{
    for(int i = 0; i < depth; ++i)
    {
        acc += " ";
    }

    acc += "+->" + to_string(_data) + " _ " + to_string((long int)this) + "\n";

    if(!isLeftFree())
    {
        acc = _left->_to_str(acc, depth+1);
    }
    if(!isRightFree())
    {
        acc = _right->_to_str(acc, depth+1);
    }

    return acc;
}

void
Node::SPR_ite(Node* noeud)
{
    int i=0;
    noeud->degraph();
    Node * nodeActual=this;
    bool fin=false,remonte=false;

    while(fin==false)
    {
        if(remonte)// si on est en train de remonter
        {
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
            
            if(nodeActual->regraph(noeud))
            {
                i++;
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
                    nodeActual=(nodeActual->_parent)->_right;
                }
                else
                {
                    nodeActual=nodeActual->_parent;
                    remonte=true;                
                }
            }
        }
    }
    //number of regraph
    //std::cout << i << std::endl;
}

void
Node::SPR_rec(Node* noeud)
{
    //number of regraph
    //std::cout << _SPR_rec(noeud, 0) << std::endl;
    _SPR_rec(noeud, 0);
}

int
Node::_SPR_rec(Node* noeud, int count)
{
    noeud->degraph();
    if(regraph(noeud))
    {
        count++;
    }
    noeud->degraph();

    if(!isLeftFree())
    {
        count = _left->_SPR_rec(noeud, count);
    }
    if(!isRightFree())
    {
        count = _right->_SPR_rec(noeud, count);
    }

    return count;
}

