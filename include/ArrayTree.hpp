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
    ArrayTree(const ArrayTree&);
    ArrayTree& operator =(const ArrayTree&);
    ~ArrayTree() = default;

    int newNode(); // Gives back the index of a clear node

    void insert(int E);

    ArrayTree degraph(int node);
    int regraph(ArrayTree& child, int node);

    // New versions, degraph let the data inside the arraytree and returns the index of the degraphed node
    // int degraph(int node); 
    // int regraph(int child, int node);

    bool check(int node) const;

    void setData(int node, int data) {_data[node] = data;}

    int getData(int node) const {return _data[node];}
    int getParent(int node) const {return _parents[node];}
    int getLeft(int node) const {return _lefts[node];}
    int getRight(int node) const {return _rights[node];}

    bool isFree(int node) const {return _free[node];}
    bool isOrphan(int node) const {return _parents[node] == -1;}
    bool isLeftFree(int node) const {return _lefts[node] == -1;}
    bool isRightFree(int node) const {return _rights[node] == -1;}

    int size() const {return _nodeCount;}

    std::string to_str();
    void dumpToStdout();

    int SPR_rec(int node);

private:
    int _load(Node* n);
    int _load(ArrayTree& source, int node);

    void _remove(int node);

    void _defragment();
    void _swap(int nodeA, int nodeB);

    void _increaseStorage(); //Enlarges storage by one block
    // TODO : implement a method to fit storage to the stored nodes

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

    int _SPR_rec(ArrayTree& subTree, int node, int count);
};

#endif // ARRAYTREE_H_INCLUDED

