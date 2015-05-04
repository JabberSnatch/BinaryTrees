/*
 * =====================================================================================
 *
 *       Filename:  node.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  14/04/2015 09:49:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Samuel BOURASSEAU (SB), samuel.bourasseau@gmail.com
 *                  Rodolphe CHARLOT, charlot.rodolphe@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __TESTENV_INCLUDED__
#define __TESTENV_INCLUDED__
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
enum testType {itVsrec,statiqueVsdynamique};
class TestEnv 
{
public:
    
    TestEnv(testType test,std::vector<float> floatPar=std::vector<float> (),std::vector<bool> floatBoolPar=std::vector<bool> (), std::vector<std::string> stringPar=std::vector<std::string>(),std::vector<bool> stringBoolPar=std::vector<bool> ());
    
    void runTest();
    
    
private:
    testType _type;
    std::vector<float> _floatPar;
    std::vector<bool> _floatBoolPar;
    std::vector<std::string> _stringPar;
    std::vector<bool> _stringBoolPar;
    
    class Chrono
    {
    public:
        Chrono( float elapsed_time=0,std::string precision="milliseconds", bool isCalculing=false);
        void start();
        void stop();
        void reset();
        float getDuration();
    private:
        std::chrono::time_point<std::chrono::system_clock> _start;
        float _elapsed_time;
        std::string _precision;
        bool _isCalculing;
    };
};

#endif // __TESTENV_INCLUDED__
