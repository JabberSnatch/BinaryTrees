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
    for(int i = 1; i < 10; ++i)
    {
        root.insert(i);
    }
    
    Node copy(root);
    Node copy2;
    copy2 = copy;

    std::cout << "Root" << std::endl << root.to_str() << std::endl;
    std::cout << "Copy" << std::endl << copy.to_str() << std::endl;
    std::cout << "Copy2" << std::endl << copy2.to_str() << std::endl;

    int nb = 5;
    root.SPR_rec(root.nodeAt(&nb));
    nb = 5;
    copy.SPR_ite(copy.nodeAt(&nb));

    std::cout << "Root" << std::endl << root.to_str() << std::endl;
    std::cout << "Copy" << std::endl << copy.to_str() << std::endl;
    std::cout << "Copy2" << std::endl << copy2.to_str() << std::endl;

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

