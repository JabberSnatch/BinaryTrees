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



/**
    


*/

void
TestEnv::runTest()
{
    if (_type==STATVSDYN)
        _statiqueVsdynamique();
        
    else if (_type==RECVSLIST)
        _recVslist();
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





/**
        test for statique vs dynamique
        FloatList : 
    -2 Needed : 
        -f1 : float nbInsert : how many insert inside trees
            Default : 5.000
        -f2 : float randomNode : which node is choosen for spr
            Default : random value between 0 and nbInsert
    -1 Optionnal:
        -f3 : float nbRound : number of round made 
        
        
        BoolList:
    -4 boolean:
        -b1: boolean timeShown : boolean if the time of both test are shown
        -b2: boolean dataCountShown : boolean if dataCount is shown
        -b3: boolean nodeCountShown : boolean if nodeCount is shown
        -b4: boolean treeShown : boolean if tree is shown
*/
void
TestEnv::_statiqueVsdynamique()
{
    {
        int nbOption=0;
        cout << "plop" << endl;
        cout << _floatBoolPar[0] << endl;
        float nbInsert = (_floatBoolPar[0])?_floatPar[nbOption++]:5000;
        uniform_int_distribution<int> randomPick = uniform_int_distribution<int>(0, nbInsert-1);
        float randomNode = (_floatBoolPar[1])? _floatPar[nbOption++]:(randomPick(rng));
        float nbRound= (_floatBoolPar[2])? _floatPar[nbOption++]:1;
        
        bool timeShown=(_boolPar[0])? true:false;
        bool dataCountShown=(_boolPar[1])? true:false;
        bool nodeCountShown=(_boolPar[2])? true:false;
        bool treeShown=(_boolPar[3])? true:false;
        
        TestEnv::Chrono myChrono;
        float temps1 =0;
        float temps2 =0 ;
        float tempsTot=0;
        Node* rootNode;
        Node* saveParent;
        
        for(;nbRound>0;nbRound--)
        {
            Node root(0);
            for(int i = 1; i < nbInsert; ++i)
            {
                root.insert(i);
            }
            Node copy(root);
            ArrayTree rootArray(copy);
            
            myChrono.start();
                rootNode = root.nodeAt(randomNode);
                saveParent=rootNode->getParent();
                root.SPR_rec(rootNode);
                if(saveParent!=nullptr)
                    saveParent->regraph(rootNode);
            myChrono.stop();
            temps1+=myChrono.getDuration();
            if(timeShown !=0)
                cout << "durée du calcul: " << myChrono.getDuration() << endl;   
            if(dataCountShown!=0)
                cout << "somme de données: " << root.dataCount() << endl;
            if(nodeCountShown!=0)
                cout << "nombre de données: " << root.nodeCount() << endl; 
            
            myChrono.reset();
            myChrono.start();
                rootArray.SPR_rec(randomNode);
            myChrono.stop();
            temps2 +=myChrono.getDuration();
            if(timeShown !=0)
                cout << "durée du calcul: " << myChrono.getDuration() << endl;   
            if(dataCountShown!=0)
                cout << "somme de données: " << rootArray.dataCount() << endl;
            if(nodeCountShown!=0)
                cout << "nombre de données: " << rootArray.nodeCount() << endl;
            myChrono.reset();


            if(treeShown)
                cout << root.newick() << endl;            
            tempsTot= temps2/temps1 * 100;
            
            cout << "Temps stat / dyn : " << tempsTot << endl;
            if(nbRound-1>0)
                cout << "------------------" << endl;
        }
        
    }
    
}


/**
    test for recursif versus list
        FloatList : 
    -1 Needed : 
        float nbInsert : how many insert inside trees
    -2 Optionnal:
        float randomNode : which node is choosen for spr. Default value = random value between 0 and nbInsert
        float nbRound : number of round made 
        
        
        BoolList:
    -5 boolean:
        -b1: boolean timeShown : boolean if the time of both test are shown
        -b2: boolean dataCountShown : boolean if dataCount is shown
        -b3: boolean nodeCountShown : boolean if nodeCount is shown
        -b4: boolean treeShown : boolean if tree is shown
        -b5: boolean timeListCreationShown : boolean if the creation of the list is timed.
*/
void
TestEnv::_recVslist()
{
    {
        int nbOption=0;
        cout << _floatBoolPar[1] << "|" << _floatPar[0] << endl;
        float nbInsert = (_floatBoolPar[0])?_floatPar[nbOption++]:5000;
        uniform_int_distribution<int> randomPick = uniform_int_distribution<int>(0, nbInsert-1);
        float randomNode = (_floatBoolPar[1])? _floatPar[nbOption++]:( randomPick(rng));
        float nbRound= (_floatBoolPar[2])? _floatPar[nbOption++]:1;
        
        bool timeShown=(_boolPar[0])? true:false;
        bool dataCountShown=(_boolPar[1])? true:false;
        bool nodeCountShown=(_boolPar[2])? true:false;
        bool treeShown=(_boolPar[3])? true:false;
        bool timeListCreationShown=(_boolPar[4])? true:false;
        
        TestEnv::Chrono myChrono;
        TestEnv::Chrono myChrono2;
        float temps1 =0;
        float temps2 =0 ;
        float tempsTot=0;
        Node* rootNode;
        //Node* saveParent;
        Node* copyNode;
        //Node* saveCopyParent;
        
        while(nbRound>0)
        {
            Node root(0);
            for(int i = 1; i < nbInsert; ++i)
            {
                root.insert(i);
            }
            Node copy(root);
                rootNode = root.nodeAt(randomNode);
            myChrono.start();
                //saveParent=rootNode->getParent();
                root.SPR_rec(rootNode);
                //if(saveParent!=nullptr)
                //    rootNode->regraph(saveParent);
            myChrono.stop();
            temps1+=myChrono.getDuration();
            if(timeShown !=0)
                cout << "durée du calcul: " << myChrono.getDuration() << endl;   
            if(dataCountShown!=0)
                cout << "somme de données: " << root.dataCount() << endl;
            if(nodeCountShown!=0)
                cout << "nombre de données: " <<root.nodeCount() << endl; 
            
            myChrono.reset();
            if(timeListCreationShown)
            {
                myChrono2.start();
            }
                copyNode = copy.nodeAt(randomNode);
                copy.SPR_list_init(copyNode);
            if(timeListCreationShown)
            {
                myChrono2.stop();
                cout << "temps de création de la list : " << myChrono2.getDuration() << endl;
            }
            myChrono.start();
                //saveCopyParent=copyNode->getParent();
                copy.SPR_list(copyNode);
                /*if(saveCopyParent!=nullptr)
                    saveCopyParent->regraph(copyNode);*/
            myChrono.stop();
            temps2 +=myChrono.getDuration();
            if(timeShown !=0)
                cout << "durée du calcul: " << myChrono.getDuration() << endl;   
            if(dataCountShown!=0)
                cout << "somme de données: " << copy.dataCount() << endl;
            if(nodeCountShown!=0)
                cout << "nombre de données: " <<copy.nodeCount() << endl;
            myChrono.reset();


            if(treeShown)
                cout << root.newick() << endl;            
            tempsTot= temps2/temps1 * 100;
            
            cout << "Temps rec / list : " << tempsTot << endl;
            if(--nbRound>0)
                cout << "------------------" << endl;
        }
        
    }
}


TestEnv::Chrono::Chrono(float elapsed_time,string newPrecision, bool isCalculing):_elapsed_time(elapsed_time),_precision(newPrecision),_isCalculing(isCalculing)
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


