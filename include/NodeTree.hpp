/*
 * =====================================================================================
 *
 *       Filename:  NodeTree.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  18/05/2015 11:23:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Samuel BOURASSEAU (SB), samuel.bourasseau@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __NODETREE_H_INCLUDED__
#define __NODETREE_H_INCLUDED__

class Node;

class NodeTree
{
public:
    NodeTree() = default;
    NodeTree(const Node&);
    ~NodeTree() = default;

    void insert(int E);
    void insertBalanced(int E);

    bool check() const;
    
    Node* nodeAt(int num);

    void setRoot(Node* n);
    Node* getRoot();

    int size() const {return _root->descendantCount()+1;}
    int leafCount();

private:
    Node* _root;
}

#endif // __NODETREE_H_INCLUDED__
