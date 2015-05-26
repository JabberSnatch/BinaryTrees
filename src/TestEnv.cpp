    /*
 * =====================================================================================
 *
 *       Filename:  testenv.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  14/04/2015 09:52:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Samuel BOURASSEAU (SB), samuel.bourasseau@gmail.com
 *                  Rodolphe CHARLOT, charlot.rodolphe@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "TestEnv.hpp"
#include <iostream>
#include <chrono>
#include <random>
#include <ctime>
#include <vector>
#include "Node.hpp"
#include "ArrayTree.hpp"

using namespace std;

mt19937 rng = mt19937(random_device()());


TestEnv::TestEnv(testType test,std::vector<float> floatPar,bool* floatBoolPar, bool* boolPar): _type(test),_floatPar(floatPar),_floatBoolPar(floatBoolPar), _boolPar(boolPar)
{}



void
TestEnv::runTest()
{
    if(_type==DREC_VS_DIT)
        _DrecVsDit();
    else if (_type==DREC_VS_SREC)
        _DrecVsSrec();
        
    else if (_type==DREC_VS_DLIST)
        _DrecVsDlist();
    else if (_type==SREC_VS_SIT)
        _SrecVsSit();
}

/**
    How to build a new test :
    
        test for ... vs ...
        FloatList : 
        -Needed : 
            -f1: 
                Default :
        -Optionnal:
        
        BoolList:
        -b1: 
*/

void
TestEnv::_DrecVsDit()
{
    {
        int nbOption=0;
        float nbInsert = (_floatBoolPar[0])?_floatPar[nbOption++]:5000;
        uniform_int_distribution<int> randomPick = uniform_int_distribution<int>(0, nbInsert-1);
        float randomNode = (_floatBoolPar[1])? _floatPar[nbOption++]:( randomPick(rng));
        float nbRound= (_floatBoolPar[2])? _floatPar[nbOption++]:1;
        
        bool timeShown=(_boolPar[0])? true:false;
        bool dataCountShown=(_boolPar[1])? true:false;
        bool nodeCountShown=(_boolPar[2])? true:false;
        bool randomNodeShown=(_boolPar[3])? true:false;
        
        TestEnv::Chrono myChrono;
        TestEnv::Chrono myChrono2;
        float temps1 =0;
        float temps2 =0 ;
        float tempsTot=0;
        Node* rootNode;
        Node* copyNode;
        
        while(nbRound>0)
        {
            Node root(0);
            for(int i = 1; i < nbInsert; ++i)
            {
                root.insert(i);
            }
            Node copy(root);
            
            rootNode = root.nodeAt(randomNode);
            cout << "Premier Test : it" << endl;
            myChrono.start();
                root.SPR_ite(rootNode);
            myChrono.stop();
            temps1+=myChrono.getDuration();
            if(timeShown !=0)
                cout << "durée du calcul: " << myChrono.getDuration()<< " ms" << endl;   
            if(dataCountShown!=0)
                cout << "somme de données: " << root.dataCount() << endl;
            if(nodeCountShown!=0)
                cout << "nombre de données: " <<root.nodeCount() << endl; 
            
            myChrono.reset();
            cout << endl;
            
            copyNode = copy.nodeAt(randomNode);
            cout << "Deuxième test : rec" << endl;
            myChrono.start();
                copy.SPR_rec(copyNode);
            myChrono.stop();
            temps2 +=myChrono.getDuration();
            if(timeShown !=0)
                cout << "durée du calcul: " << myChrono.getDuration() << " ms" << endl;   
            if(dataCountShown!=0)
                cout << "somme de données: " << copy.dataCount() << endl;
            if(nodeCountShown!=0)
                cout << "nombre de données: " <<copy.nodeCount() << endl;
            myChrono.reset();


            if(randomNodeShown){
                if(rootNode->getParent()!=nullptr)
                {
                    rootNode=rootNode->getParent();
                }
                cout << "Node prise , de taille " << rootNode->nodeCount() << " :" << endl;
                cout << rootNode->to_str() << endl;
            }            
            tempsTot= temps2/temps1 * 100;
            
            cout << "Temps it / rec : " << tempsTot << endl;
            if(--nbRound>0)
                cout << "------------------" << endl;
        }
        
    }
}


void
TestEnv::_DrecVsSrec()
{
    {
        int nbOption=0;
        float nbInsert = (_floatBoolPar[0])?_floatPar[nbOption++]:5000;
        uniform_int_distribution<int> randomPick = uniform_int_distribution<int>(0, nbInsert-1);
        float randomNode = (_floatBoolPar[1])? _floatPar[nbOption++]:(randomPick(rng));
        float nbRound= (_floatBoolPar[2])? _floatPar[nbOption++]:1;
        
        bool timeShown=(_boolPar[0])? true:false;
        bool dataCountShown=(_boolPar[1])? true:false;
        bool nodeCountShown=(_boolPar[2])? true:false;
        bool randomNodeShown=(_boolPar[3])? true:false;
        
        TestEnv::Chrono myChrono;
        float temps1 =0;
        float temps2 =0 ;
        float tempsTot=0;
        Node* rootNode;
        
        while(nbRound>0)
        {
            Node root(0);
            for(int i = 1; i < nbInsert; ++i)
            {
                root.insert(i);
            }
            Node copy(root);
            ArrayTree rootArray(copy);
            
            rootNode = root.nodeAt(randomNode);
            cout << "Premier Test : rec dynamique" << endl;
            myChrono.start();
                root.SPR_rec(rootNode);
            myChrono.stop();
            temps1+=myChrono.getDuration();
            if(timeShown !=0)
                cout << "durée du calcul: " << myChrono.getDuration()<< " ms" << endl;   
            if(dataCountShown!=0)
                cout << "somme de données: " << root.dataCount() << endl;
            if(nodeCountShown!=0)
                cout << "nombre de données: " << root.nodeCount() << endl; 
            
            myChrono.reset();
            cout << endl;
            
            cout << "Deuxième test : rec statique" << endl;
            myChrono.start();
                rootArray.SPR_ite(randomNode);
            myChrono.stop();
            temps2 +=myChrono.getDuration();
            if(timeShown !=0)
                cout << "durée du calcul: " << myChrono.getDuration()<< " ms" << endl;   
            if(dataCountShown!=0)
                cout << "somme de données: " << rootArray.dataCount() << endl;
            if(nodeCountShown!=0)
                cout << "nombre de données: " << rootArray.nodeCount() << endl;
            myChrono.reset();


            if(randomNodeShown){
                if(rootNode->getParent()!=nullptr)
                {
                    rootNode=rootNode->getParent();
                }
                cout << "Node prise , de taille " << rootNode->nodeCount() << " :" << endl;
                cout << rootNode->to_str() << endl;
            }          
            tempsTot= temps2/temps1 * 100;
            
            cout << "Temps stat / dyn : " << tempsTot << endl;
            if(--nbRound>0)
                cout << "------------------" << endl;
        }
        
    }
    
}


void
TestEnv::_DrecVsDlist()
{
    {
        int nbOption=0;
        float nbInsert = (_floatBoolPar[0])?_floatPar[nbOption++]:5000;
        uniform_int_distribution<int> randomPick = uniform_int_distribution<int>(0, nbInsert-1);
        float randomNode = (_floatBoolPar[1])? _floatPar[nbOption++]:( randomPick(rng));
        float nbRound= (_floatBoolPar[2])? _floatPar[nbOption++]:1;
        
        bool timeShown=(_boolPar[0])? true:false;
        bool dataCountShown=(_boolPar[1])? true:false;
        bool nodeCountShown=(_boolPar[2])? true:false;
        bool randomNodeShown=(_boolPar[3])? true:false;
        bool timeListCreationShown=(_boolPar[4])? true:false;
        
        TestEnv::Chrono myChrono;
        TestEnv::Chrono myChrono2;
        float temps1 =0;
        float temps2 =0;
        float tempsTot=0;
        Node* rootNode;
        Node* copyNode;
        
        while(nbRound>0)
        {
            Node root(0);
            for(int i = 1; i < nbInsert; ++i)
            {
                root.insert(i);
            }
            Node copy(root);
            rootNode = root.nodeAt(randomNode);
            cout << "Premier Test : rec dynamique" << endl;
            myChrono.start();
                root.SPR_ite(rootNode);
            myChrono.stop();
            temps1+=myChrono.getDuration();
            if(timeShown !=0)
                cout << "durée du calcul: " << myChrono.getDuration()<< " ms" << endl;   
            if(dataCountShown!=0)
                cout << "somme de données: " << root.dataCount() << endl;
            if(nodeCountShown!=0)
                cout << "nombre de données: " <<root.nodeCount() << endl; 
            
            myChrono.reset();
            cout << endl;
            cout << "Deuxième test : list dynamique" << endl;
            if(timeListCreationShown)
            {
                myChrono2.start();
            }
                copyNode = copy.nodeAt(randomNode);
                copy.SPR_list_init(copyNode);
            if(timeListCreationShown)
            {
                myChrono2.stop();
                cout << "temps de création de la liste : " << myChrono2.getDuration() << "ms" << endl;
                myChrono2.reset();
            }
            myChrono.start();
                copy.SPR_list(copyNode);
            myChrono.stop();
            temps2 +=myChrono.getDuration();
            if(timeShown !=0)
                cout << "durée du calcul: " << myChrono.getDuration() << " ms" << endl;   
            if(dataCountShown!=0)
                cout << "somme de données: " << copy.dataCount() << endl;
            if(nodeCountShown!=0)
                cout << "nombre de données: " <<copy.nodeCount() << endl;
            myChrono.reset();


            if(randomNodeShown){
                if(rootNode->getParent()!=nullptr)
                {
                    rootNode=rootNode->getParent();
                }
                cout << "\n" << "Node prise , de taille " << rootNode->nodeCount() << " :" << endl;
                cout << rootNode->to_str() << endl;
            }            
            tempsTot= temps2/temps1 * 100;
            
            cout << "Temps rec / list : " << tempsTot << endl;
            if(--nbRound>0)
                cout << "------------------" << endl;
        }
        
    }
}

void
TestEnv::_SrecVsSit()
{
    int nbOption=0;
    float nbInsert = (_floatBoolPar[0])?_floatPar[nbOption++]:5000;
    uniform_int_distribution<int> randomPick = uniform_int_distribution<int>(0, nbInsert-1);
    float randomNode = (_floatBoolPar[1])? _floatPar[nbOption++]:(randomPick(rng));
    float nbRound= (_floatBoolPar[2])? _floatPar[nbOption++]:1;
    
    bool timeShown=(_boolPar[0])? true:false;
    bool dataCountShown=(_boolPar[1])? true:false;
    bool nodeCountShown=(_boolPar[2])? true:false;
    bool randomNodeShown=(_boolPar[3])? true:false;
    
    TestEnv::Chrono myChrono;
    float temps1 =0;
    float temps2 =0 ;
    float tempsTot=0;
    Node* rootNode;
    
    while(nbRound>0)
    {
        Node root(0);
        for(int i = 1; i < nbInsert; ++i)
        {
            root.insert(i);
        }
        ArrayTree rootArray(root);
        ArrayTree rootArray2(root);
        
        cout << "Premier Test : rec statique" << endl;
        myChrono.start();
            rootArray.SPR_rec(randomNode);
        myChrono.stop();
        temps1+=myChrono.getDuration();
        if(timeShown !=0)
            cout << "durée du calcul: " << myChrono.getDuration()<< " ms" << endl;   
        if(dataCountShown!=0)
            cout << "somme de données: " << root.dataCount() << endl;
        if(nodeCountShown!=0)
            cout << "nombre de données: " << root.nodeCount() << endl; 
        
        myChrono.reset();
        cout << endl;
        
        cout << "Deuxième test : ite statique" << endl;
        myChrono.start();
            rootArray2.SPR_ite(randomNode);
        myChrono.stop();
        temps2 +=myChrono.getDuration();
        if(timeShown !=0)
            cout << "durée du calcul: " << myChrono.getDuration()<< " ms" << endl;   
        if(dataCountShown!=0)
            cout << "somme de données: " << rootArray.dataCount() << endl;
        if(nodeCountShown!=0)
            cout << "nombre de données: " << rootArray.nodeCount() << endl;
        myChrono.reset();


        if(randomNodeShown){
            if(rootNode->getParent()!=nullptr)
            {
                rootNode=rootNode->getParent();
            }
            cout << "Node prise , de taille " << rootNode->nodeCount() << " :" << endl;
            cout << rootNode->to_str() << endl;
        }          
        tempsTot= temps2/temps1 * 100;
        
        cout << "Temps stat / dyn : " << tempsTot << endl;
        if(--nbRound>0)
            cout << "------------------" << endl;
    }
        
}


TestEnv::Chrono::Chrono(float elapsed_time,string newPrecision):_elapsed_time(elapsed_time),_precision(newPrecision),_isCalculing(false)
{}


void
TestEnv::Chrono::start()
{
    _isCalculing=true;
    _start = std::chrono::system_clock::now();

}

void
TestEnv::Chrono::stop()
{
    if(_isCalculing==true)
    {
        chrono::time_point<chrono::system_clock> end=chrono::system_clock::now();
        _isCalculing=false;
        if(_precision=="nanoseconds")
        {
            _elapsed_time+=chrono::duration_cast<chrono::nanoseconds>(end-_start).count();
        }
        else if(_precision=="microseconds")
        {
            _elapsed_time+=chrono::duration_cast<chrono::microseconds>(end-_start).count();
        }
        else if(_precision=="seconds")
        {
            _elapsed_time+=chrono::duration_cast<chrono::seconds>(end-_start).count();
        }
        else
        {
            _elapsed_time+=chrono::duration_cast<chrono::milliseconds>(end-_start).count();
        }
                                 
    }
    else
        cerr << "Le chrono n'a pas démarré, vous ne pouvez pas le stopper" << endl;
}
void
TestEnv::Chrono::reset()
{
    _elapsed_time=0;
}
float
TestEnv::Chrono::getDuration()
{
    return _elapsed_time;
}


