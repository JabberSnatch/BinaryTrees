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

#include <string>

class Node
{
public:
    Node(int data = 0);
    Node(const Node&) = delete;
    Node& operator =(const Node&) = delete;
    ~Node() = default;

    //void SPR();

    void degraph();
    bool regraph(Node* child);

    bool isOrphan();
    bool isLeftFree();
    bool isRightFree();
    //bool check();
    
    std::string to_str();

private:
    void _setParent(Node* parent);
    std::string _to_str(std::string acc, int depth);

    Node* _parent;
    Node* _left;
    Node* _right;

    int _data;

};


#endif // __NODE_H_INCLUDED__
