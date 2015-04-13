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

ArrayTree::ArrayTree(const Node& n)
    :_nodeCount(n.size())
{
    _blockCount = _nodeCount / _blockSize + (_nodeCount % _blockSize!=0);

    _parents = new int[_nodeCount];
    _lefts = new int[_nodeCount];
    _rights = new int[_nodeCount];
    _data = new int[_nodeCount];
}

