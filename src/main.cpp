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

int main(int argc, char* argv[])
{
    std::cout << "YOLO" << std::endl;

    std::chrono::duration<int> s_oneday(60*60*24);
    std::cout << s_oneday.count() << std::endl;

#ifdef RODOLPHE
    Node root(0);
    /*Node a(1);
    Node b(2);
    Node c(3);
    Node d(4);
    Node e(5);

    a.regraph(&c);
    a.regraph(&d);

    b.regraph(&e);

    root.regraph(&a);
    root.regraph(&b);*/
    
    for(int i = 1; i < 3000; ++i)
    {
        root.insert(i);
    }
    //std::cout << root.to_str() << std::endl;

    //std::cout << root.to_str() << std::endl;
    //std::cout << root.check() << std::endl;
    //std::cout << root.nbDescendants() << std::endl;
    
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<std::mt19937::result_type> randomNodes(1,root.nbDescendants());
	
    int nb = randomNodes(rng);
    int save_nb=nb;
    std::cout << "noeud a l'indice " << nb << std::endl;
    std::cout << (root.nodeAt(&nb))->to_str() << std::endl;
    //nb=save_nb;
    nb=1;
    root.SPR_ite(root.nodeAt(&nb));
    nb=1;
    root.SPR_rec(root.nodeAt(&nb));
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
    Node* rootNode = root.nodeAt(&nb);
    root.SPR_rec(rootNode);

    nb = 5;
    Node* copyNode = copy.nodeAt(&nb);
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
    root.SPR_rec(root.nodeAt(&nb));
    nb = 25;
    root.SPR_ite(root.nodeAt(&nb));

#endif

#endif

    return 0;
}

