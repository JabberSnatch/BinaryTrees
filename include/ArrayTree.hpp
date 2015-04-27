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

    int newNode(); // Gives back the index of a clear node

    void insert(int E);

    bool isLeftFree(int node) const {return _lefts[node] == -1;}
    bool isRightFree(int node) const {return _rights[node] == -1;}

    std::string to_str();
    void dumpToStdout();

private:
    int _load(Node* n);
    void _increaseStorage(); //Enlarges storage by one block

    std::string _to_str(std::string acc, int depth, int index);

    int _storageSize() {return _blockCount * _blockSize;}

    int _blockCount = 0;
    int _blockSize = 5;
    int _nodeCount = 0;

    int* _parents = nullptr;
    int* _lefts = nullptr;
    int* _rights = nullptr;
    int* _data = nullptr;
    bool* _free = nullptr;

    static std::mt19937 rng;
    static std::uniform_int_distribution<int> binaryPick;

};

#endif // ARRAYTREE_H_INCLUDED

