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

void debug()
{
#ifdef RODOLPHE
    std::vector<bool> floatBoolList={true,true,true};
    std::vector<float> floatList={5000,5,2,0};
    TestEnv myTest(itVsrec,floatList,floatBoolList);
    myTest.runTest();
    
#endif 

#ifdef SAMUEL
    Node root(0);

#if 1
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

    for(int i = 1; i < 300; ++i)
    {
        root.insert(i);
    }
    std::cout << root.check() << std::endl;

    int nb=25;
    root.SPR_rec(root.nodeAt(nb));
    root.SPR_ite(root.nodeAt(nb));

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

