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

#include <string>
#include <random>

class Node;

class ArrayTree
{
public:
    ArrayTree();
    ArrayTree(Node&);
    ArrayTree(const ArrayTree&) = delete;
    ArrayTree& operator =(const ArrayTree&) = delete;
    ~ArrayTree() = default;

    void SPR_ite(Node* noeud) = delete;
    void SPR_rec(Node* noeud) = delete;

    void insert(int E);

    void degraph() = delete;
    bool regraph(Node* child) = delete;

    bool isLeftFree(int index) {return _lefts[index] == -1;}
    bool isRightFree(int index) {return _rights[index] == -1;}

    std::string to_str();
    void dumpToStdout();

private:
    void _load(Node* n);
    void _increaseStorage(); //Enlarges storage by one block

    std::string _to_str(std::string acc, int depth, int index);

    int _storageSize() {return _blockCount * _blockSize;}

    int _blockCount;
    int _blockSize = 5;
    int _nodeCount;

    int* _parents = nullptr;
    int* _lefts = nullptr;
    int* _rights = nullptr;
    int* _data = nullptr;

    static std::mt19937 rng;
    static std::uniform_int_distribution<int> binaryPick;

};

#endif // ARRAYTREE_H_INCLUDED

