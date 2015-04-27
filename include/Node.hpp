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

    void insert(int E);

    void degraph();
    bool regraph(Node* child);

    bool check() const;
    bool nodeCheck() const;

    const Node* findRoot() const;
    int descendantCount() const;

    Node* nodeAt(int num);
    
    void setData(int data) {_data = data;}

    int getData() const {return _data;}
    Node* getParent() {return _parent;}
    Node* getLeft() {return _left;}
    Node* getRight() {return _right;}

    bool isFree() const {return _free;}
    bool isOrphan() const {return _parent == nullptr;}
    bool isLeftFree() const {return _left == nullptr;}
    bool isRightFree() const {return _right == nullptr;}

    int size() const {return findRoot()->descendantCount()+1;}

    Node::NodeIter* begin() {return new Node::NodeIter(this);}
    std::string to_str();

    void SPR_ite(Node* noeud);
    void SPR_rec(Node* noeud);

private:
    void _setParent(Node* parent) {_parent = parent;}

    Node* _parent;
    Node* _left;
    Node* _right;

    int _data;
    bool _free;

    static std::mt19937 rng;
    static std::uniform_int_distribution<int> binaryPick;

    int _SPR_rec(Node* noeud, int count);
    std::string _to_str(std::string acc, int depth);
    int _nodeAt(int num);

public:
    class NodeIter
    {
        friend class Node;

    public:
        void begin() {_index = 0;}
        Node* getNext() {return _root->nodeAt(_index++);}
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
