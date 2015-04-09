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

    bool check();
    bool nodeCheck();

    Node* findRoot();

    bool isOrphan() const;
    bool isLeftFree() const;
    bool isRightFree() const;

    int nbDescendants();
    Node* nodeAt(int* num);
    
    std::string to_str();

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

};


#endif // __NODE_H_INCLUDED__
