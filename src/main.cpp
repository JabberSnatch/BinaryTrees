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

#include <cassert>
#include "Node.hpp"

#include "ArrayTree.hpp"

int main(int argc, char* argv[])
{
    std::cout << "YOLO" << std::endl;

    std::chrono::duration<int> s_oneday(60*60*24);
    std::cout << s_oneday.count() << std::endl;

#ifdef RODOLPHE
    while(1){
        Node root(0);
        for(int i = 1; i < 20000; ++i)
        {
            root.insert(i);
        }
        
        Node copy(root);
        Node copy2;

        
        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();
            int nb=25;
            Node* rootNode = root.nodeAt(&nb);
            root.SPR_rec(rootNode);
        end = std::chrono::system_clock::now();
        int elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds>
                                 (end-start).count();
        std::cout << "temps rec: " << elapsed_seconds << std::endl;
        
        
        start = std::chrono::system_clock::now();
            nb=25;
            Node* copyNode = copy.nodeAt(&nb);
            copy.SPR_ite(copyNode);
        end = std::chrono::system_clock::now();
        int elapsed_seconds_2 = std::chrono::duration_cast<std::chrono::milliseconds>
                                 (end-start).count();
        std::cout << "temps it: " << elapsed_seconds_2 << std::endl;
        std::cout << "temps it/rec%: " << ((float)elapsed_seconds_2/(float)elapsed_seconds)*100.0 << std::endl;

        

        delete rootNode;
        delete copyNode;
        
        std::cout << "plop" << std::endl;
    }
#endif 

#ifdef SAMUEL

    Node root(0);

#if 1
    ArrayTree tree;

    tree.dumpToStdout();

    for(int i = 1; i < 10; ++i)
    {
        tree.insert(i);
    }

    tree.dumpToStdout();

    std::cout << tree.to_str() << std::endl;

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

