/*
 * =====================================================================================
 *
 *       Filename:  node.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/04/2015 09:49:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Samuel BOURASSEAU (SB), samuel.bourasseau@gmail.com
 *                  Rodolphe CHARLOT, charlot.rodolphe@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __NODE_H_INCLUDED__
#define __NODE_H_INCLUDED__

#include <string>
#include <random>
#include <iostream>

class Node
{
public:
    class NodeIter;

    Node(int data = 0, Node* parent = nullptr);

    Node(const Node&);
    Node& operator =(const Node&);
    Node* clone();

    ~Node();

    void SPR_ite(Node* noeud);
    void SPR_rec(Node* noeud);

    void insert(int E);

    void degraph();
    bool regraph(Node* child);

    bool check() const;
    bool nodeCheck() const;

    const Node* findRoot() const;

    int nbDescendants() const;
    Node* nodeAt(int* num);
    
    Node::NodeIter* begin() {return new Node::NodeIter(this);}
    std::string to_str();

    int size() const {return findRoot()->nbDescendants()+1;}
    int getData() const {return _data;}

    bool isOrphan() const {return _parent == nullptr;}
    bool isLeftFree() const {return _left == nullptr;}
    bool isRightFree() const {return _right == nullptr;}

private:
    int _SPR_rec(Node* noeud, int count);
    std::string _to_str(std::string acc, int depth);

    Node* _getParent();
    void _setParent(Node* parent);

    Node* _parent;
    Node* _left;
    Node* _right;

    int _data;

    static std::mt19937 rng;
    static std::uniform_int_distribution<int> binaryPick;


public:
    class NodeIter
    {
        friend class Node;

    public:
        void begin() {_index = 0;}
        Node* getNext() {int i = _index++; return _root->nodeAt(&i);}
        bool hasNext() {return _index < _size;}
        void end() {_index = _size-1;}

    private:
        NodeIter(Node* root)
            :_root(root), _index(0), _size(root->size())
        {}

        Node* _root;
        int _index;
        int _size;

    };

};

#endif // __NODE_H_INCLUDED__
