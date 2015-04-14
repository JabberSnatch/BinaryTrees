/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/04/2015 09:56:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Samuel BOURASSEAU (SB), samuel.bourasseau@gmail.com
 *                  Rodolphe CHARLOT, charlot.rodolphe@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <chrono>
#include <random>
#include <ctime>

#include <cassert>
#include "Node.hpp"

int main(int argc, char* argv[])
{
    std::cout << "YOLO" << std::endl;

    std::chrono::duration<int> s_oneday(60*60*24);
    std::cout << s_oneday.count() << std::endl;

#ifdef RODOLPHE
    while(1){
        Node root(0);
        for(int i = 1; i < 50000; ++i)
        {
            root.insert(i);
        }
        
        Node copy(root);
        Node copy2;

        
        int nb=25;
        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();
            Node* rootNode = root.nodeAt(nb);
            root.SPR_rec(rootNode);
        end = std::chrono::system_clock::now();
        int elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds>
                                 (end-start).count();
        std::cout << "temps rec: " << elapsed_seconds << std::endl;
        
        
        start = std::chrono::system_clock::now();
            Node* copyNode = copy.nodeAt(nb);
            copy.SPR_ite(copyNode);
        end = std::chrono::system_clock::now();
        int elapsed_seconds_2 = std::chrono::duration_cast<std::chrono::milliseconds>
                                 (end-start).count();
        std::cout << "temps it: " << elapsed_seconds_2 << std::endl;
        std::cout << "temps it/rec%: " << ((float)elapsed_seconds_2/(float)elapsed_seconds)*100.0 << std::endl << std::endl;
        delete copyNode;

        

        delete rootNode;
        
    }
#endif 

#ifdef SAMUEL
    Node root(0);

#if 0
    //NOTE(samu): This test case shows how memory is lost when running SPR
    //            Maybe we should consider switching to smart pointer in order to avoid
    //            having to manually free the SPR'ed node

    for(int i = 1; i < 3000; ++i)
    {
        root.insert(i);
    }
    
    Node copy(root);
    Node copy2;

    int nb = 5;
    Node* rootNode = root.nodeAt(nb);
    root.SPR_rec(rootNode);

    Node* copyNode = copy.nodeAt(nb);
    copy.SPR_ite(copyNode);

    delete rootNode;
    delete copyNode;

#else

    for(int i = 1; i < 10; ++i)
    {
        root.insert(i);
    }
    std::cout << root.check() << std::endl;

    for(auto it = root.begin(); it->hasNext();)
    {
        Node* n = it->getNext();

        std::cout << n->getData() << "; ";
    }
    std::cout << std::endl;

    std::cout << root.to_str() << std::endl;

#endif

#endif

    return 0;
}

