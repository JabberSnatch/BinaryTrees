/*
 * =====================================================================================
 *
 *       Filename:  node_statique.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  13/04/2015 09:52:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Samuel BOURASSEAU (SB), samuel.bourasseau@gmail.com
 *                  Rodolphe CHARLOT, charlot.rodolphe@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
 
 
 #include "Node_statique.hpp"


using namespace std;

mt19937 Node_s::rng = mt19937(random_device()());
uniform_int_distribution<int> Node_s::binaryPick = uniform_int_distribution<int>(0, 1);

int* Node_s::_parent=nullptr;
int* Node_s::_left=nullptr;
int* Node_s::_right=nullptr;
int* Node_s::_data=nullptr;
int Node_s::_maxSize=-1;//counter

Node_s::Node_s(int parent, int left, int right, int data)
{
    if(_maxSize==-1)
    {
        if(parent!=-1)
        {
            cerr << "Erreur : parent vide demandé en racine" << endl;
        }
        else
        {
            _parent=(int*)malloc(5*sizeof(int));
            _left=(int*)malloc(5*sizeof(int));
            _right=(int*)malloc(5*sizeof(int));
            _data=(int*)malloc(5*sizeof(int));
            _maxSize=4;
            
            _parent[0]=parent;
            _left[0]=left;
            _right[0]=right;
            _data[0]=data;
        }
    }
    else
    {
        //ajoutNode(parent,left, right, data);
        //insert here addNode function
    }
}

string
Node_s::to_str()
{
    return _to_str("",0,0);
}

string
Node_s::_to_str(string acc, int depth, int numNode)
{
    if(numNode>_maxSize)
    {
        return "";
    }
    else
    {
        for(int i = 0; i < depth; ++i)
        {
            acc += " ";
        }

        acc += "+->" + to_string(_data[numNode]) + "\n";

        if(_left[numNode] != -1)
        {
            acc = _to_str(acc, depth+1,_left[numNode]);
        }
        if(_right[numNode] != -1)
        {
            acc = _to_str(acc, depth+1,_right[numNode]);
        }

        return acc;
    }
}


