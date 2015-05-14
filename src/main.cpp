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
#include "TestEnv.hpp"

#include "ArrayTree.hpp"

void debug()
{
#ifdef RODOLPHE
    std::vector<bool> floatBoolList={false,true,true,true,true,false};
    std::vector<float> floatList={15000,2,true,true,true};
    TestEnv myTest(RECVSLIST,floatList,floatBoolList);
    myTest.runTest();
        
#endif 

#ifdef SAMUEL
    Node root;

#if 0
    ArrayTree tree;

    tree.dumpToStdout();

    for(int i = 0; i < 11; ++i)
    {
        tree.insert(i);
    }

    //tree.dumpToStdout();

    std::cout << tree.to_str() << std::endl;
    
    ArrayTree copy(tree);
    //copy.dumpToStdout();
    std::cout << copy.to_str() << std::endl;

    ArrayTree subTree = copy.degraph(2);

    std::cout << copy.to_str() << std::endl;
    std::cout << subTree.to_str() << std::endl;

    copy.dumpToStdout();
    subTree.dumpToStdout();

    std::cout << copy.regraph(subTree, 2) << std::endl;

    std::cout << copy.to_str() << std::endl;


#else

    for(int i = 1; i < 300; ++i)
    {
        root.insert(i);
    }
    std::cout << root.check() << std::endl;
    std::cout << root.to_str() << std::endl;

    #if 0
    Node* n = root.nodeAt(3);
    n->degraph();

    std::cout << root.to_str() << std::endl;
    std::cout << n->getParent()->to_str() << std::endl;

    root.nodeAt(1)->regraph(n);

    std::cout << root.to_str() << std::endl; 
    #else
    Node* n = root.nodeAt(368);
    std::cout << n->getParent()->to_str() << std::endl;
    root.SPR_list(n);
    std::cout << root.to_str() << std::endl;
    #endif

#if 0
    ArrayTree tree(root);

    std::cout << tree.to_str() << std::endl;
    std::cout << tree.SPR_rec(3) << std::endl;
    std::cout << tree.to_str() << std::endl;

    std::cout << root.to_str() << std::endl;
    root.SPR_rec(root.nodeAt(3));
    std::cout << root.to_str() << std::endl;
#endif

#endif
#endif
}

int main(int argc, char* argv[])
{
    std::cout << "YOLO" << std::endl;

    std::chrono::duration<int> s_oneday(60*60*24);
    std::cout << s_oneday.count() << std::endl;

    debug();

    return 0;
}

