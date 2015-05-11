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


TestEnv::TestEnv(testType test,std::vector<float> floatPar,std::vector<bool> floatBoolPar, std::vector<std::string> stringPar,std::vector<bool> stringBoolPar): _type(test),_floatPar(floatPar),_floatBoolPar(floatBoolPar), _stringPar(stringPar),_stringBoolPar(stringBoolPar)
{}



/**
    


*/

void
TestEnv::runTest()
{
    if(_type==ITVSREC)
        _itVsrec();
   
    else if (_type==STATVSDYN)
        _statiqueVsdynamique();
        
    else if (_type==RECVSLIST)
        _recVslist();
}

/**
    How to build a new test :
    
        test for ... vs ...
        FloatList : 
        -Needed : 
        -Optionnal:
        
        StringList:
        -Needed : 
        -Optionnal:
*/




/**
    test for iteratif versus recursif
    FloatList : 
    -1 Needed : 
        float nbInsert : how many insert inside trees
    -6 Optionnal:
        float randomNode : which node is choosen for spr. Default value = random value between 0 and nbInsert
        float nbRound : number of round made 
        boolean timeShown : boolean if the time of both test are shown
        boolean dataCountShown : boolean if dataCount is shown
        boolean nodeCountShown : boolean if nodeCount is shown
        boolean treeShown : boolean if tree is shown
        
    StringList:
    -0 Needed : 
    -0 Optionnal:
*/
void
TestEnv::_itVsrec()
{
    {
        float nbInsert = _floatPar[0];
        int nbOption=1;
        uniform_int_distribution<int> randomPick = uniform_int_distribution<int>(0, nbInsert-1);
        float randomNode = (_floatBoolPar[0])? _floatPar[nbOption++]:( randomPick(rng));
        float nbRound= (_floatBoolPar[1])? _floatPar[nbOption++]:1;
        bool timeShown=(_floatBoolPar[2])? _floatPar[nbOption++]:false;
        bool dataCountShown=(_floatBoolPar[3])? _floatPar[nbOption++]:false;
        bool nodeCountShown=(_floatBoolPar[4])? _floatPar[nbOption++]:false;
        bool treeShown=(_floatBoolPar[5])? _floatPar[nbOption++]:false;
        
        TestEnv::Chrono myChrono;
        float temps1 =0;
        float temps2 =0 ;
        float tempsTot=0;
        Node* rootNode;
        //Node* saveParent;
        Node* copyNode;
        //Node* saveCopyParent;
        
        for(;nbRound>0;nbRound--)
        {
            Node root(0);
            for(int i = 1; i < nbInsert; ++i)
            {
                root.insert(i);
            }
            Node copy(root);
            myChrono.start();
                rootNode = root.nodeAt(randomNode);
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
            myChrono.start();
                copyNode = copy.nodeAt(randomNode);
                //saveCopyParent=copyNode->getParent();
                copy.SPR_ite(copyNode);
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
            
            cout << "Temps it / rec : " << tempsTot << endl;
        }
        
    }
}

/**
        test for statique vs dynamique
        FloatList : 
        -Needed : 
        -Optionnal:
        
        StringList:
        -Needed : 
        -Optionnal:
    */
void
TestEnv::_statiqueVsdynamique()
{
    {
        float nbInsert = _floatPar[0];
        int nbOption=1;
        uniform_int_distribution<int> randomPick = uniform_int_distribution<int>(0, nbInsert-1);
        float randomNode = (_floatBoolPar[0])? _floatPar[nbOption++]:( randomPick(rng));
        float nbRound= (_floatBoolPar[1])? _floatPar[nbOption++]:1;
        bool timeShown=(_floatBoolPar[2])? _floatPar[nbOption++]:false;
        bool dataCountShown=(_floatBoolPar[3])? _floatPar[nbOption++]:false;
        bool nodeCountShown=(_floatBoolPar[4])? _floatPar[nbOption++]:false;
        bool treeShown=(_floatBoolPar[5])? _floatPar[nbOption++]:false;
        
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
                cout << "somme de données: " << copy.dataCount() << endl;
            if(nodeCountShown!=0)
                cout << "nombre de données: " << copy.nodeCount() << endl;
            myChrono.reset();


            if(treeShown)
                cout << root.newick() << endl;            
            tempsTot= temps2/temps1 * 100;
            
            cout << "Temps stat / dyn : " << tempsTot << endl;
        }
        
    }
    
}


/**
        test for statique vs dynamique
        FloatList : 
        -Needed : 
        -Optionnal:
        
        StringList:
        -Needed : 
        -Optionnal:
    */
void
TestEnv::_recVslist()
{

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


