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
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __NODE_H_INCLUDED__
#define __NODE_H_INCLUDED__

class Node
{
public:
    Node();
    Node(const Node&) = delete;
    Node& operator =(const Node&) = delete;
    ~Node() = default;
    bool check();
    bool nodeCheck();

private:
    Node* _parent;
    Node* _left;
    Node* _right;

    int _data;

    Node* getParent();
};

#endif // __NODE_H_INCLUDED__
