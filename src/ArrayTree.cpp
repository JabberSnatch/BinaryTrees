/*
 * =====================================================================================
 *
 *       Filename:  ArrayTree.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  13/04/2015 14:18:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Samuel BOURASSEAU (SB), samuel.bourasseau@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "ArrayTree.hpp"

#include <cassert>

#include "Node.hpp"
#include "NodeTree.hpp"

using namespace std;

mt19937 ArrayTree::rng = mt19937(random_device()());
uniform_int_distribution<int> ArrayTree::binaryPick = uniform_int_distribution<int>(0, 1);

ArrayTree::ArrayTree()
{
    _parents = new int[_storageSize()];
    _lefts = new int[_storageSize()];
    _rights = new int[_storageSize()];
    _data = new int[_storageSize()];
    _free = new bool[_storageSize()];

    for(int index = 0; index < _storageSize(); ++index)
    {
        _parents[index] = -1;
        _lefts[index] = -1;
        _rights[index] = -1;
        _data[index] = 0;
        _free[index] = true;
    }
}

ArrayTree::ArrayTree(Node& root)
{
    _load(&root);

#if DEBUG
    assert(check(_root));
#endif
}

ArrayTree::ArrayTree(NodeTree& tree)
{
    _load(tree.getRoot());

#if DEBUG
    assert(check(_root));
#endif
}

ArrayTree::ArrayTree(const ArrayTree& at)
    :_blockCount(at._blockCount), _blockSize(at._blockSize), _nodeCount(at._nodeCount)
{ 
    _parents = new int[_storageSize()];
    _lefts = new int[_storageSize()];
    _rights = new int[_storageSize()];
    _data = new int[_storageSize()];
    _free = new bool[_storageSize()];

    for(int index = 0; index < _storageSize(); ++index)
    {
        _parents[index] = at._parents[index];
        _lefts[index] = at._lefts[index];
        _rights[index] = at._rights[index];
        _data[index] = at._data[index];
        _free[index] = at._free[index];
    }
}

ArrayTree&
ArrayTree::operator =(const ArrayTree& at)
{
    _blockCount = at._blockCount;
    _blockSize = at._blockSize;
    _nodeCount = at._nodeCount;

    if(_parents)
    {
        delete _parents;
        delete _lefts;
        delete _rights;
        delete _data;
        delete _free;
    }

    _parents = new int[_storageSize()];
    _lefts = new int[_storageSize()];
    _rights = new int[_storageSize()];
    _data = new int[_storageSize()];
    _free = new bool[_storageSize()];

    for(int index = 0; index < _storageSize(); ++index)
    {
        _parents[index] = at._parents[index];
        _lefts[index] = at._lefts[index];
        _rights[index] = at._rights[index];
        _data[index] = at._data[index];
        _free[index] = at._free[index];
    }

    return *this;
}

int
ArrayTree::_load(Node* n)
{
    int node = newNode();

    _free[node] = n->isFree();
    _data[node] = n->getData();

    if(!n->isLeftFree())
    {
        int left = _load(n->getLeft());

        _lefts[node] = left;
        _parents[_lefts[node]] = node;
    }
    if(!n->isRightFree())
    {
        int right = _load(n->getRight());

        _rights[node] = right;
        _parents[_rights[node]] = node;
    }

    return node;
}

int
ArrayTree::newNode()
{
    if(_nodeCount >= _storageSize())
    {
        _increaseStorage();
    }

    return _nodeCount++;
}

void
ArrayTree::insert(int E)
{
    bool spotFound = false;
    int index = _root;

    int node = newNode();
        
    while(!spotFound)
    {
        if(_free[index])
        {
            _data[index] = E;
            _free[index] = false;

            spotFound = true;
        }

        else if(isLeftFree(index))
        {
            _lefts[index] = node;
            _parents[_lefts[index]] = index;

            index = _lefts[index];
        }
        else if(isRightFree(index))
        {
            _rights[index] = node;
            _parents[_rights[index]] = index;

            index = _rights[index];
        }

        else
        {
            int side = binaryPick(rng);

            if(side == 0)
            {
                index = _lefts[index];
            }
            if(side == 1)
            {
                index = _rights[index];
            }
        }
    }
}

int
ArrayTree::degraph(int node)
{
    int sibling = -1;

    if(!isOrphan(node))
    {
        if(getLeft(getParent(node))==node)
        {
            sibling = _rights[_parents[node]];

            if(sibling != -1)
            {
                _parents[_rights[_parents[node]]] = _parents[_parents[node]];
                _rights[_parents[node]] = -1;
            }
        }

        if(getRight(getParent(node)) == node)
        {
            sibling = _lefts[_parents[node]];

            if(sibling != -1)
            {
                _parents[_lefts[_parents[node]]] = _parents[_parents[node]];
                _lefts[_parents[node]] = -1;
            }
        }

        if(!isOrphan(getParent(node)))
        {
            if(getLeft(getParent(getParent(node))) == getParent(node))
            {
                _lefts[_parents[_parents[node]]] = sibling;
            }
            if(getRight(getParent(getParent(node))) == getParent(node))
            {
                _rights[_parents[_parents[node]]] = sibling;
            }
        }
        else
        {
            //std::cout << "Parent is root" << std::endl;
            _setRoot(sibling);
        }

        _parents[_parents[node]] = -1;
    }

#if DEBUG
    assert(check(_root));
#endif

    return _parents[node];
}

int
ArrayTree::regraph(int child, int node)
{
    int regraphedNode = _parents[child];

    if(isLeftFree(regraphedNode))
    {
        _lefts[regraphedNode] = node;
    }
    if(isRightFree(regraphedNode))
    {
        _rights[regraphedNode] = node;
    }

    _parents[regraphedNode] = _parents[node];
    if(!isOrphan(node))
    {
        if(getLeft(getParent(node)) == node)
        {
            _lefts[_parents[node]] = regraphedNode;
        }
        if(getRight(getParent(node)) == node)
        {
            _rights[_parents[node]] = regraphedNode;
        }
    }
    _parents[node] = regraphedNode;

    if(node == _root)
    {
        _setRoot(_parents[node]);
    }
    
#if DEBUG
    assert(check(_root));
#endif

    return child;
}

bool
ArrayTree::check(int node) const
{
    bool RES = false;
    //std::cout << "checking node n°" << node << std::endl;

    if(node == _root)
    {
        if(!isOrphan(node))
        {
            std::cout << "root has parent" << std::endl;
            return RES;
        }
    }

    if(isLeftFree(node) && isRightFree(node))
    {
        RES = true;
    }
    else
    {
        if(!isLeftFree(node))
        {
            if(getParent(getLeft(node)) == node)
            {
                RES = true;
                RES &= check(getLeft(node));
            }
            else
            {
                
                std::cout << "left node isn't linked back to current node "<< node << std::endl;
            }
        }

        if(!isRightFree(node))
        {
            if(getParent(getLeft(node)) == node)
            {
                RES = true;
                RES &= check(getRight(node));
            }
            else
            {
                std::cout << "right node isn't linked back to current node" << std::endl;
            }
        }
    }

    return RES;
}

int 
ArrayTree::dataCount()
{
    int res=0;
    for(int i=0;i<_nodeCount;i++)
        res+=_data[i];
    return res;
}

string
ArrayTree::to_str()
{
    return _to_str("", 0, _root);
}

void
ArrayTree::dumpToStdout()
{
    for(int i = 0; i < _storageSize(); ++i)
    {
        std::cout << _parents[i] << "; ";
    }
    std::cout << std::endl;
    for(int i = 0; i < _storageSize(); ++i)
    {
        std::cout << _lefts[i] << "; ";
    }
    std::cout << std::endl;
    for(int i = 0; i < _storageSize(); ++i)
    {
        std::cout << _rights[i] << "; ";
    }
    std::cout << std::endl;
    for(int i = 0; i < _storageSize(); ++i)
    {
        std::cout << _data[i] << "; ";
    }
    std::cout << std::endl;
    for(int i = 0; i < _storageSize(); ++i)
    {
        std::cout << _free[i] << "; ";
    }
    std::cout << std::endl;
}

int
ArrayTree::_load(ArrayTree& source, int sourceNode)
{
    int node = newNode();

    _free[node] = source.isFree(sourceNode);
    _data[node] = source.getData(sourceNode);

    if(!source.isLeftFree(sourceNode))
    {
        int left = _load(source, source.getLeft(sourceNode));

        _lefts[node] = left;
        _parents[_lefts[node]] = node;
    }
    if(!source.isRightFree(sourceNode))
    {
        int right = _load(source, source.getRight(sourceNode));

        _rights[node] = right;
        _parents[_rights[node]] = node;
    }

    return node;
}

void
ArrayTree::_remove(int node)
{
    if(!isLeftFree(node))
    {
        int left = getLeft(node);
        _remove(left);
    }
    if(!isRightFree(node))
    {
        int right = getRight(node);
        _remove(right);
    }

    _data[node] = 0; // NOTE : this should be removed in the templated version

    _free[node] = true;
    _parents[node] = -1;
    _lefts[node] = -1;
    _rights[node] = -1;
    _nodeCount--;
}

void
ArrayTree::_defragment()
{
    for(int i = 0; i < _storageSize(); ++i)
    {
        for(int j = 1; j < _storageSize(); ++j)
        {
            if(_free[j-1] > _free[j])
            {
                _swap(j-1, j);
            }
        }
    }
}

void
ArrayTree::_swap(int nodeA, int nodeB)
{
    // Update the nodes referencing either of these nodes
    if(!isOrphan(nodeA))
    {
        int parent = _parents[nodeA];
        if(_lefts[parent] == nodeA)
        {
            _lefts[parent] = nodeB;
        }
        else if(_rights[parent] == nodeA)
        {
            _rights[parent] = nodeB;
        }
    }
    if(!isLeftFree(nodeA))
    {
        _parents[_lefts[nodeA]] = nodeB;
    }
    if(!isRightFree(nodeA))
    {
        _parents[_rights[nodeA]] = nodeB;
    }

    if(!isOrphan(nodeB))
    {
        int parent = _parents[nodeB];
        if(_lefts[parent] == nodeB)
        {
            _lefts[parent] = nodeA;
        }
        else if(_rights[parent] == nodeB)
        {
            _rights[parent] = nodeA;
        }
    }
    if(!isLeftFree(nodeB))
    {
        _parents[_lefts[nodeB]] = nodeA;
    }
    if(!isRightFree(nodeB))
    {
        _parents[_rights[nodeB]] = nodeA;
    }

    // Then swap
    int tmp[3];
    int data;
    bool free;

    tmp[0] = _parents[nodeA];
    tmp[1] = _lefts[nodeA];
    tmp[2] = _rights[nodeA];
    data = _data[nodeA];
    free = _free[nodeA];

    _parents[nodeA] = _parents[nodeB];
    _lefts[nodeA] = _lefts[nodeB];
    _rights[nodeA] = _rights[nodeB];
    _data[nodeA] = _data[nodeB];
    _free[nodeA] = _free[nodeB];

    _parents[nodeB] = tmp[0];
    _lefts[nodeB] = tmp[1];
    _rights[nodeB] = tmp[2];
    _data[nodeB] = data;
    _free[nodeB] = free;
}

void
ArrayTree::_increaseStorage()
{
    _blockCount++;

    int* buffer;
    
    buffer = new int[_storageSize()];
    for(int i = 0; i < _nodeCount; ++i)
    {
        buffer[i] = _parents[i];
    }
    for(int i = _nodeCount; i < _storageSize(); ++i)
    {
        buffer[i] = -1;
    }
    delete _parents;
    _parents = buffer;

    buffer = new int[_storageSize()];
    for(int i = 0; i < _nodeCount; ++i)
    {
        buffer[i] = _lefts[i];
    }
    for(int i = _nodeCount; i < _storageSize(); ++i)
    {
        buffer[i] = -1;
    }
    delete _lefts;
    _lefts = buffer;

    buffer = new int[_storageSize()];
    for(int i = 0; i < _nodeCount; ++i)
    {
        buffer[i] = _rights[i];
    }
    for(int i = _nodeCount; i < _storageSize(); ++i)
    {
        buffer[i] = -1;
    }
    delete _rights;
    _rights = buffer;

    buffer = new int[_storageSize()];
    for(int i = 0; i < _nodeCount; ++i)
    {
        buffer[i] = _data[i];
    }
    for(int i = _nodeCount; i < _storageSize(); ++i)
    {
        buffer[i] = 0;
    }
    delete _data;
    _data = buffer;

    bool* boolBuffer = new bool[_storageSize()];
    for(int i = 0; i < _nodeCount; ++i)
    {
        boolBuffer[i] = _free[i];
    }
    for(int i = _nodeCount; i < _storageSize(); ++i)
    {
        boolBuffer[i] = true;
    }
    delete _free;
    _free = boolBuffer;
}

string
ArrayTree::_to_str(string acc, int depth, int index)
{ 
    for(int i = 0; i < depth; ++i)
    {
        acc += " ";
    }

    acc += "+->" + to_string(_data[index]) + " _ " + to_string((long int)index) + "\n";

    if(_lefts[index] != -1)
    {
        acc = _to_str(acc, depth+1, _lefts[index]);
    }
    if(_rights[index] != -1)
    {
        acc = _to_str(acc, depth+1, _rights[index]);
    }

    return acc;
}

void
ArrayTree::SPR_rec(int node)
{
    int position = degraph(node);

#if DEBUG
     cout << _SPR_rec(position, _root, 0) << " degraph/regraph" << endl;
#else
    _SPR_rec(position, _root, 0);
#endif
}

int
ArrayTree::_SPR_rec(int subTreeRoot, int currentNode, int count)
{
    int regraphIndex = regraph(subTreeRoot, currentNode);
    if(regraphIndex != -1)
    {
        count++;
        degraph(regraphIndex);
    }   

    if(!isLeftFree(currentNode))
    {
        count = _SPR_rec(subTreeRoot, getLeft(currentNode), count);
    }
    if(!isRightFree(currentNode))
    {
        count = _SPR_rec(subTreeRoot, getRight(currentNode), count);
    }

    return count;
}

void
ArrayTree::SPR_ite(int node)
{
    int i=0;
    int regraphIndex;
    int child=degraph(node);
    int nodeActual=0;
    bool fin=false,remonte=false;
    while(fin==false)
    {
        if(remonte)// si on est en train de remonter
        {
            remonte=false;
            if(getParent(nodeActual)!=-1)//si on est pas a la racine
            {
                if(getRight(getParent(nodeActual))!=nodeActual)//si on est dans le fils gauche
                {
                    if(getRight(getParent(nodeActual))!=-1)// si le fils droit est libre
                    {
                        nodeActual=getRight(getParent(nodeActual));
                    }
                    else// s'il n'y a pas de fils droit
                    {
                        nodeActual=getParent(nodeActual);
                        remonte=true;
                    }
                }
                else//si on est dans le fils droit
                {
                    nodeActual=getParent(nodeActual);
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
            regraphIndex=regraph(child,nodeActual);
            if(regraphIndex!=-1)
            {
                i++;
                degraph(regraphIndex);
            }
            if(getLeft(nodeActual)!=-1)// si on peut aller a gauche
            {
                nodeActual=getLeft(nodeActual);
            }
            else if (getRight(nodeActual)!=-1)// si on peut aller a droite
            {
                nodeActual=getRight(nodeActual);
            }
            else if(getParent(getParent(nodeActual))==-1)//si on est juste après la racine
            {
                if(getRight(getParent(nodeActual))==nodeActual)   //si on est a droite
                {
                    fin =true;
                }
                else                                    //si on est a gauche
                {
                    if(getRight(getParent(nodeActual))!=-1)
                    {
                        nodeActual=getRight(getParent(nodeActual));
                    }
                    else
                    {
                        fin=true;              
                    }
                }
            }
            else if(nodeActual==getRight(getParent(nodeActual)))//si on est a droite du noeud _parent
            {
                remonte=true;
                nodeActual=getParent(nodeActual);
            }
            else// si on est a gauche du noeud _parent
            {
                if(getRight(getParent(nodeActual))!=-1)
                {
                    nodeActual=getRight(getParent(nodeActual));
                }
                else
                {
                    nodeActual=getParent(nodeActual);
                    remonte=true;                
                }
            }
        }
    }
    
    
#if DEBUG
    //number of regraph
    std::cout << i <<" degraph/regraph"<< std::endl;
#endif

}

std::vector<int>
ArrayTree::SPR_list_init(int noeud)
{
    std::vector<int> nodes;

    degraph(noeud);

    _SPR_list_init(_root, nodes);
    return nodes;
}

void
ArrayTree::_SPR_list_init(int noeud, std::vector<int>& nodes)
{
    nodes.push_back(noeud);
    if(!isLeftFree(noeud))
    {
        _SPR_list_init(_lefts[noeud], nodes);
    }
    if(!isRightFree(noeud))
    {
        _SPR_list_init(_rights[noeud], nodes);
    }
}

void
ArrayTree::SPR_list(int noeud, std::vector<int>& nodes)
{
    int count = 0;
    
    for(unsigned int i = 0; i < nodes.size(); i++)
    {
        if(regraph(noeud, nodes[i]))
        {
            count++;
        }
        degraph(noeud);
    }

#if DEBUG
    std::cout << count << "degraph/regraph" << std::endl;
#endif

}


