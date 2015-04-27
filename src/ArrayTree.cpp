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

#include "Node.hpp"

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
    // Put the check here
#endif

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
    int index = 0;

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

string
ArrayTree::to_str()
{
    return _to_str("", 0, 0);
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

