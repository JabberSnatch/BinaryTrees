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
#include "NodeTree.hpp"
#include "ArrayTree.hpp"

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
    NodeTree nTree;

#if 1
    for(int i = 0; i < 10; ++i)
    {
        nTree.insert(i);    
    }

#if 1
    ArrayTree aTree(nTree);
    aTree.dumpToStdout();
    std::cout << aTree.to_str() << std::endl;
    assert(aTree.check(0));
    std::cout << "Check 1 Ok" << std::endl;
#endif

#if 1
    int subTree = aTree.degraph(1);
    std::cout << "aTree._root=" << aTree.getRoot() << std::endl;
    aTree.dumpToStdout();
    std::cout << aTree.to_str() << std::endl;
    assert(aTree.check(0));
    std::cout << "Check 2 Ok" << std::endl;
#endif

#if 1
    std::cout << aTree.regraph(1, aTree.getRoot()) << std::endl;
    std::cout << "aTree._root=" << aTree.getRoot() << std::endl;
    aTree.dumpToStdout();
    std::cout << aTree.to_str() << std::endl;
    assert(aTree.check(0));
    std::cout << "Check 3 Ok" << std::endl;
#endif

    //std::cout << aTree.SPR_rec(3) << std::endl;
    //std::cout << aTree.to_str() << std::endl;

    #if 0
    std::cout << nTree.to_str() << std::endl;
    nTree.SPR_list(nTree.nodeAt(3));
    std::cout << nTree.to_str() << std::endl;
    #endif

#else

    for(int i = 0; i < 1000; ++i)
    {
        nTree.insert(i);
    }
    std::cout << nTree.check() << std::endl;
    std::cout << nTree.to_str() << std::endl;

    #if 0
    Node* n = nTree.nodeAt(3);
    n->degraph();

    std::cout << nTree.to_str() << std::endl;
    std::cout << n->getParent()->to_str() << std::endl;

    nTree.nodeAt(1)->regraph(n);

    std::cout << nTree.to_str() << std::endl; 
    #else
    Node* n = nTree.nodeAt(5);
    std::cout << n->getParent()->to_str() << std::endl;
    nTree.SPR_list(n);
    std::cout << nTree.to_str() << std::endl;
    #endif


#endif

#endif

    return 0;
}

