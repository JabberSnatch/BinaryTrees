/*
 * =====================================================================================
 *
 *       Filename:  ArrayTree.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  13/04/2015 13:35:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Samuel BOURASSEAU (SB), samuel.bourasseau@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef ARRAYTREE_H_INCLUDED
#define ARRAYTREE_H_INCLUDED

class Node;

class ArrayTree
{
public:
    ArrayTree() = default;
    ArrayTree(const Node&);
    ArrayTree(const ArrayTree&) = delete;
    ArrayTree& operator =(const ArrayTree&) = delete;
    ~ArrayTree() = default;

    void SPR_ite(Node* noeud) = delete;
    void SPR_rec(Node* noeud) = delete;

    void insert(int E) = delete;

    void degraph() = delete;
    bool regraph(Node* child) = delete;

    int maxSize() {return _blockCount * _blockSize;}

private:
    int _blockCount();
    int _blockSize = 5;
    int _nodeCount;

    int* _parents = nullptr;
    int* _lefts = nullptr;
    int* _rights = nullptr;
    int* _data = nullptr;

};

#endif // ARRAYTREE_H_INCLUDED

