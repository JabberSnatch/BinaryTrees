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

using namespace std;

mt19937 rng = mt19937(random_device()());
uniform_int_distribution<int> binaryPick = uniform_int_distribution<int>(0, 1);

TestEnv::TestEnv(testType test,vector<float> floatPar, vector<string> stringPar): _type(test),_floatPar(floatPar),_stringPar(stringPar)
{}

/**
    


*/

void
TestEnv::runTest()
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
{

    if(_type==itVsrec)
    /**
        test for iteratif versus recursif
        FloatList : 
        -Needed : 
            float nbInsert : how many insert inside trees
        -Optionnal:
            float randomNode : which node is choosen for spr. Default value = random value between 0 and nbInsert
            float nbRound : number of round made 
            boolean timeShown : boolean if the time of both test are shown
            
        StringList:
        -Needed : 
        -Optionnal:
    */
    {
        float nbInsert = _floatPar[0];
        float randomNode = binaryPick(rng) * nbInsert;
        float nbRound=1;
        bool timeShown=false;
        switch (_floatPar.size())
        {
            case 4:
                randomNode = _floatPar[1];
            
            case 3:
                nbRound=_floatPar[2];
            
            case 2:
                timeShown=_floatPar[3];
        }
        
        TestEnv::Chrono myChrono;
        float temps1 =0;
        float temps2 =0 ;
        float tempsTot=0;
        Node* rootNode;
        Node* copyNode;
        
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
                root.SPR_rec(rootNode);
            myChrono.stop();
            temps1+=myChrono.getDuration();
            if(timeShown !=0)
                cout << myChrono.getDuration() << endl;    
            
            myChrono.reset();
            myChrono.start();
                copyNode = copy.nodeAt(randomNode);
                copy.SPR_ite(copyNode);
            myChrono.stop();
            temps2 +=myChrono.getDuration();
            if(timeShown !=0)
                cout << myChrono.getDuration() << endl;   
            myChrono.reset();
            
            tempsTot= temps2/temps1 * 100;
            
            cout << "Temps it / rec : " << tempsTot << endl;
        }
        
    }
    
    else if (_type==statiqueVsdynamique)
    /**
        test for statique vs dynamique
        FloatList : 
        -Needed : 
        -Optionnal:
        
        StringList:
        -Needed : 
        -Optionnal:
    */
    {
    
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

