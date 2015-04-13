/*
 * =====================================================================================
 *
 *       Filename:  node_statique.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  13/04/2015 09:49:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Samuel BOURASSEAU (SB), samuel.bourasseau@gmail.com
 *                  Rodolphe CHARLOT, charlot.rodolphe@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __NODE_H_STATIQUE_INCLUDED__
#define __NODE_H_STATIQUE_INCLUDED__

#include <string>
#include <random>
#include <iostream>

class Node_s
{
public:
    Node_s(int parent=-1, int fils_g=-1, int fils_d=-1,int data=0);
    std::string to_str();
private:
    std::string _to_str(std::string acc, int depth, int numNode);
    
    static int _maxSize; //counter starts at 0
    static int* _parent;
    static int* _left;
    static int* _right;
    static int* _data;
    
    static std::mt19937 rng;
    static std::uniform_int_distribution<int> binaryPick;
    
};
    
#endif // NODE_H_STATIQUE included

