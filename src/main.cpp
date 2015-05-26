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
#include <string.h>
#include <stdio.h>

#include <cassert>
#include "Node.hpp"
#include "TestEnv.hpp"

#include "ArrayTree.hpp"
int maxSizeBoolPar=50;
int maxSizeFloatPar=50;

void debug(int argc, char* argv[])
{

#ifdef RODOLPHE
    std::vector<float> floatList={};
    bool floatBoolList[maxSizeFloatPar];
    for(int i=0;i<maxSizeFloatPar;i++)
        floatBoolList[i]=false;
        
    bool boolList[maxSizeBoolPar];
    for(int i=0;i<maxSizeBoolPar;i++)
        boolList[i]=false;
        
    testType test;
    if(argc<2)
    {
        std::cout << "Donnez un test à faire, --help pour plus d'info" << std::endl;
    
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
    }
    else if(strcmp(argv[1],"DREC_VS_DIT")==0)
    {
        test=DREC_VS_DIT;
    }
    else if(strcmp(argv[1],"DREC_VS_SREC")==0)
    {
        test=DREC_VS_SREC;
    }
    else if(strcmp(argv[1],"DREC_VS_DLIST")==0)
    {
        test=DREC_VS_DLIST;
    }
    else if(strcmp(argv[1],"SREC_VS_SIT")==0)
    {
        test=SREC_VS_SIT;
    }
    else
    {
        std::cerr << "Le test demandé n'existe pas, pour plus d'informations essayez --help" << std::endl;
    }
    for(int i=2;i<argc;i++)
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
            
            
            
    TestEnv myTest(test,floatList,floatBoolList,boolList);
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

    for(int i = 0; i < 10000; ++i)
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

    debug(argc,argv);

    return 0;
}

