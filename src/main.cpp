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
#include <fstream>
#include <chrono>
#include <random>
#include <ctime>
#include <cassert>
#include <string.h>
#include <stdio.h>

#include "TestEnv.hpp"

#include "Node.hpp"
#include "NodeTree.hpp"
#include "ArrayTree.hpp"
int maxSizeBoolPar=50;
int maxSizeFloatPar=50;

void debug(int argc, char* argv[])
{

#ifdef RODOLPHE

#endif 

#ifdef SAMUEL
    NodeTree nTree;

// ARRAYTREE
#if 0
    nTree.insertNLeaves(15);

#if 1
    ArrayTree aTree(nTree);
    aTree.dumpToStdout();
    std::cout << aTree.to_str() << std::endl;
    assert(aTree.check(aTree.getRoot()));
    std::cout << "Check 1 Ok" << std::endl;
#endif

#if 0
    int subTree = aTree.degraph(1);
    std::cout << "aTree._root=" << aTree.getRoot() << std::endl;
    aTree.dumpToStdout();
    std::cout << aTree.to_str() << std::endl;
    assert(aTree.check(0));
    std::cout << "Check 2 Ok" << std::endl;
#endif

#if 0
    std::cout << aTree.regraph(1, aTree.getRoot()) << std::endl;
    std::cout << "aTree._root=" << aTree.getRoot() << std::endl;
    aTree.dumpToStdout();
    std::cout << aTree.to_str() << std::endl;
    assert(aTree.check(0));
    std::cout << "Check 3 Ok" << std::endl;
#endif

#if 1
    std::vector<int> nodes = aTree.SPR_list_init(3);
    aTree.SPR_list(3, nodes);
    std::cout << aTree.to_str() << std::endl;
    assert(aTree.check(aTree.getRoot()));
    std::cout << "Check 4 Ok" << std::endl;
#endif

// NODETREE
#else

    nTree.insertNLeaves(10);
    NodeTree copy(nTree);
    
    std::cout << nTree.to_str() << std::endl;
    std::cout << nTree.check() << std::endl;
    std::cout << copy.to_str() << std::endl;
    std::cout << copy.check() << std::endl;

    NodeTree* A = &nTree;
    NodeTree* B = &copy;

    Node* nodeA = (*A).nodeAt(1);
    Node* nodeB = (*B).nodeAt(1);

    std::cout << nodeA->to_str() << std::endl;
    std::cout << nodeB->to_str() << std::endl;

#if 0
    std::vector<Node*> nodesA = (*A).SPR_list_init(nodeA);
    (*A).SPR_list(nodeA, nodesA);

    std::vector<Node*> nodesB = (*B).SPR_list_init(nodeB);
    (*B).SPR_list(nodeB, nodesB);
#else
    (*A).SPR_ite(nodeA);
    (*B).SPR_rec(nodeB);
#endif
    std::cout << (*A).to_str() << std::endl;
    std::cout << (*A).getRoot()->to_str() << std::endl;
    std::cout << (*A).check() << std::endl;

    std::cout << (*B).to_str() << std::endl;
    std::cout << (*B).getRoot()->to_str() << std::endl;
    std::cout << (*B).check() << std::endl;

#endif
#endif
}

int parseCommandLine(int argc, char* argv[])
{
    std::vector<float> floatList={};
    bool floatBoolList[maxSizeFloatPar];
    for(int i=0;i<maxSizeFloatPar;i++)
        floatBoolList[i]=false;
        
    bool boolList[maxSizeBoolPar];
    for(int i=0;i<maxSizeBoolPar;i++)
        boolList[i]=false;
        
    testType test1;
    testType test2;
    bool fin=false;
    if(argc<2)
    {
        std::cout << "Donnez un test à faire, --help pour plus d'info" << std::endl;
        fin=true;
    
    }
    else if(strcmp(argv[1],"--help")==0)
    {
        std::ifstream fichier("help.txt");
        if(!fichier) 
        {
            std::cerr << "Le fichier help n'existe pas" << std::endl;
        }
        else
        {
            std::string line;
            while(std::getline(fichier,line))
            {
                std::cout << line << std::endl;
            }
        }
        fin=true;
    }
    //Premier test
    else if(strcmp(argv[1],"DREC")==0)
    {
        test1=DREC;
    }
    else if(strcmp(argv[1],"DIT")==0)
    {
        test1=DIT;
    }
    else if(strcmp(argv[1],"DLIST")==0)
    {
        test1=DLIST;
    }
    else if(strcmp(argv[1],"SREC")==0)
    {
        test1=SREC;
    }
    else if(strcmp(argv[1],"SIT")==0)
    {
        test1=SIT;
    }
    else if(strcmp(argv[1],"SLIST")==0)
    {
        test1=SLIST;
    }
    else
    {
        std::cerr << "Le test demandé n'existe pas, pour plus d'informations essayez --help" << std::endl;
        fin=true;
    }
    
    //Deuxième test
    if(!fin)
    {
        if(strcmp(argv[2],"DREC")==0)
        {
            test2=DREC;
        }
        else if(strcmp(argv[2],"DIT")==0)
        {
            test2=DIT;
        }
        else if(strcmp(argv[2],"DLIST")==0)
        {
            test2=DLIST;
        }
        else if(strcmp(argv[2],"SREC")==0)
        {
            test2=SREC;
        }
        else if(strcmp(argv[2],"SIT")==0)
        {
            test2=SIT;
        }
        else if(strcmp(argv[2],"SLIST")==0)
        {
            test2=SLIST;
        }
        else
        {
            std::cerr << "Le test demandé n'existe pas, pour plus d'informations essayez --help" << std::endl;
            fin=true;
        }
    }
    for(int i=3;i<argc;i++)
    {
        if(strlen(argv[i])!=3)
        {
            std::cerr << "L'argument numéro " << (i-2) << " n'est pas reconnu" << std::endl;
        }
        if(argv[i][0]=='-')
        {
            if(argv[i][1]=='f')
            {
                float puissance=1;
                float nombre=0;
                floatBoolList[(int)(argv[i][2])-49]=true;
                i++;
                for(int j=strlen(argv[i])-1;j>=0;j--)
                {
                    nombre=nombre+(argv[i][j]-48)*puissance;
                    puissance*=10;
                }
                floatList.push_back(nombre);
            }
            else if(argv[i][1]=='b')
            {
                boolList[(int)(argv[i][2])-49]=true;
            }
            else
            {
                std::cerr << "L'argument numéro " << (i-2) << " n'est pas reconnu, début non reconnu" << std::endl;
            }
        }
    }
            
            
    if(!fin)      
    {
        TestEnv myTest(test1,test2,floatList,floatBoolList,boolList);
        myTest.runTest();
    }  

    return 0;
}

int main(int argc, char* argv[])
{
    std::cout << "YOLO" << std::endl;

    std::chrono::duration<int> s_oneday(60*60*24);
    std::cout << s_oneday.count() << std::endl;
    
    debug(argc,argv);

    return parseCommandLine(argc, argv);
}

