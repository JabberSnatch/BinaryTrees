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

#include "NodeTree.hpp"

using namespace std;

mt19937 Node::rng = mt19937(random_device()());
uniform_int_distribution<int> Node::binaryPick = uniform_int_distribution<int>(0, 1);

Node::Node(int data, Node* parent)
    :_tree(nullptr), _parent(parent), _left(nullptr), _right(nullptr), _data(data), _free(false)
{}

Node::Node(NodeTree* tree, Node* parent, Node* left, Node* right)
    :_tree(tree), _parent(parent), _left(left), _right(right), _data(0), _free(true)
{}

Node::Node(const Node& n)
    :_tree(nullptr), _parent(nullptr), _left(nullptr), _right(nullptr), _data(n._data), _free(n.isFree())
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
    }

    delete _left;
    delete _right;
}

Node*
Node::insert(int E)
{
    Node* result = nullptr;

    if(_free)
    {
        _data = E;
        _free = false;
        result = this;
    }
    else if(isLeftFree())
    {
        _left = new Node(E, this);
        result = _left;
    }
    else if(isRightFree())
    {
        _right = new Node(E, this);
        result = _right;
    }
    else
    {
        int side = binaryPick(rng);

        if(side == 0)
        {
            result = _left->insert(E);
        }
        if(side == 1)
        {
            result = _right->insert(E);
        }
    }

    return result;
}

Node*
Node::insertBalanced(int E)
{
    Node* result = nullptr;

    if(_free)
    {
        _data = E;
        _free = false;
        result = this;
    }
    else if(isLeftFree())
    {
        _left = new Node(E, this);
        result = _left;
    }
    else if(isRightFree())
    {
        _right = new Node(E, this);
        result = _right;
    }
    else
    {
        if(_right->descendantCount() > _left->descendantCount())
        {
            result = _left->insertBalanced(E);
        }
        else
        {
            result = _right->insertBalanced(E);
        }
    }

    return result;
}

Node*
Node::insertLeaf()
{
    Node* parent = new Node(_tree, _parent, this, nullptr);
    Node* sibling = new Node(_tree, parent, nullptr, nullptr);

    parent->_right = sibling;

    if(!isOrphan())
    {
        if(parent->_parent->_left == this)
        {
            parent->_parent->_left = parent;
        }
        if(parent->_parent->_right == this)
        {
            parent->_parent->_right = parent;
        }
    }
    else
    {
        if(_tree)
        {
            _tree->setRoot(parent);
        }
    }

    _parent = parent;

    return sibling;
}

bool
Node::addChild(Node* noeud)
{
    if(isLeftFree())
    {
        _left=noeud;
        return true;
    }
    else if (isRightFree())
    {
        _right=noeud;
        return true;
    }
    else
    {
        return false;
    }
}

// The parent is degraphed along with the calling node
// The parent's other child is attached to the parent's parent
void 
Node::degraph()
{
    Node* sibling;
    
    if(!isOrphan())
    {
        if(_parent->_left == this)
        {
            sibling = _parent->_right;

            if(sibling)
            {
                _parent->_right->_parent = _parent->_parent;
                _parent->_right = nullptr;
            }
        }

        if(_parent->_right == this)
        {
            sibling = _parent->_left;

            if(sibling)
            {
                _parent->_left->_parent = _parent->_parent;
                _parent->_left = nullptr;
            }
        }

        if(!_parent->isOrphan())
        {
            if(_parent->_parent->_left == _parent)
            {
                _parent->_parent->_left = sibling;
            }
            if(_parent->_parent->_right == _parent)
            {
                _parent->_parent->_right = sibling;
            }
        }
        else
        {
            //std::cout << "Parent is root" << std::endl;
            if(_tree)
            {
                _tree->setRoot(sibling);
            }
        }

        _parent->_parent = nullptr;
    }

#if DEBUG
    if(_tree)
    {
        assert(_tree->check());
    }
    else
    {
        assert(findRoot()->check());
    }
#endif
}


// NOTE : As degraph takes the parent away with the node, regraph plugs the child's parent
//        above the calling node.
//        The operation is garanteed to work
bool
Node::regraph(Node* child)
{
    bool success = false;
    if(child==this)
    {
        return true;
    }
    Node* regraphedNode;
    if(!child->isOrphan())//vérif si la node qu'on raccroche est la racine, légère modif du code
    {
        regraphedNode = child->_parent;
    }
    else
    {
        regraphedNode=child;
    }
    // Plug the node under the child's parent
    if(regraphedNode->isLeftFree())
    {
        regraphedNode->_left = this;
    }
    else if(regraphedNode->isRightFree())
    {
        regraphedNode->_right = this;
    }
    
    if(!child->isOrphan())//vérif si la node qu'on raccroche est la racine, légère modif du code
    {
        regraphedNode->_parent = _parent;
    }
    else
    {
        regraphedNode->_parent = nullptr;
    }

    if(!isOrphan())
    {
        if(_parent->_left == this)
        {
            _parent->_left = regraphedNode;
        }
        if(_parent->_right == this)
        {
            _parent->_right = regraphedNode;
        }
    }
    _parent = regraphedNode;

    // Change the root of the tree, if the node is assigned to one
    if(_tree)
    {
        if(_tree->getRoot() == this)
        {
            std::cout << "plopa" << std::endl;
            _tree->setRoot(_parent);
        }
    }

    success = true;

#if DEBUG
    if(_tree)
    {
        assert(_tree->check());
    }
    else
    {
        assert(findRoot()->check());
    }
#endif

    return success;
}

//NOTE: check is supposed to be called on the root of a tree
bool 
Node::check() const
{
    bool RES = false;

    if(isOrphan())
    {
        RES = true;
        RES &= nodeCheck();
    }
    else
    {
        std::cout << "root has parent" << std::endl;
    }

    return RES;
}

bool 
Node::nodeCheck() const
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
            else
            {
                std::cout << "left node isn't linked back to current node" << std::endl;
            }
        }

        if(!isRightFree())
        {
            if(_right->getParent() == this)
            {
                RES = true;
                RES &= _right->nodeCheck();
            }
            else
            {
                std::cout << "right node isn't linked back to current node" << std::endl;
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

int
Node::leafCount()
{
    int count = 0;

    for(int index = 0; index < size(); ++index)
    {
        Node* n = nodeAt(index);
        if(n->isLeftFree() && n->isRightFree())
        {
            count++;
        }
    }

    return count;
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
Node::SPR_list_init(Node* noeud)
{
    noeud->degraph();
    for(NodeIter* it = begin(); it->hasNext();)
    {
        Node* n = it->getNext();
        if(n)
        {
            nodes.push_back(n);
        }
    }
}

void
Node::SPR_list(Node* noeud)
{
    int expectedSize = size()+noeud->size();
    int count = 0;

    for(unsigned int i = 0; i < nodes.size(); ++i)
    {
        if(nodes[i]->regraph(noeud))
        {
#if DEBUG
            assert(expectedSize == size());
#endif
            count++;
        }
        noeud->degraph();
    }

#if DEBUG
    std::cout << count << " degraph/regraph" << std::endl;
#endif
}

void
Node::SPR_ite(Node* noeud)
{
    int i=0;
    //Node* copy(noeud);
    
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
            
            nodeActual->regraph(noeud);
            i++;
            noeud->degraph();

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
    
    
    /*if(!(copy->_parent)->addChild(copy))
    {
#if DEBUG
    cout << "le rajout du noeud n'a pas marché" << endl;
#endif    
    }*/
#if DEBUG
    //number of regraph
    std::cout << i <<" degraph/regraph"<< std::endl;
#endif

}

void
Node::SPR_rec(Node* noeud)
{
#if DEBUG
    //number of regraph
    std::cout << _SPR_rec(noeud, 0) << " degraph/regraph"<<std::endl;
#else
    _SPR_rec(noeud, 0);
#endif
}

int
Node::_SPR_rec(Node* noeud, int count)
{
    regraph(noeud);
    count++;
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

