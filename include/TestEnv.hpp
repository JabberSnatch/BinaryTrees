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

/**
*   \file TestEnv.hpp
*   \brief Permet construire un test et le chronométrer
*   \author Samuel et Rodolphe
*

*/
#include <vector>
#include <string>
#include <chrono>
#include <ctime>

/**
*   \enum testType
*   \brief Nomme tous les types de test
*/
enum testType {ITVSREC,STATVSDYN,ITVSLIST};

/**
*   \class TestEnv
*   \brief classe pour construire un test
*   
*   La classe permet de construire un test en fonction du type de test et des paramètres donnés en vecteurs.
*   Elle contient aussi un chronomètre pour récupérer le temps du test   
*   
*/
class TestEnv 
{
public:
    /**
    *   \brief Constructeur
    *
    *   Constructeur de la classe TestEnv, mets dans les attributs ce qu'il faut pour lancer un test
    *
    */
    TestEnv(testType test,std::vector<float> floatPar=std::vector<float> (),bool *floatBoolPar=nullptr, bool* boolPar=nullptr);
    
    /**
    *   \brief Lance le test 
    *
    *   Méthode qui lance la fonction correpondant au test dans l'attribut _type
    *
    */
    void runTest();
    
    
private:
    /** Type du test */
    testType _type; 
    /** Vecteur des valeurs paramètres float du test */
    std::vector<float> _floatPar;
    /** Vecteur de booléen pour savoir quelle option est prise, dont la valeur est dans _floatPar */
    bool* _floatBoolPar;
    /** Vecteur de booléen pour savoir quel option booléenne prendre */ 
    bool* _boolPar; 
    
    /**
    *   \brief Lance le test itvsrec
    *
    *   Méthode qui lance le test pour Spr_ite statique en premier puis Spr_rec statique
    *   Chronomètre le temps des deux tests et les compare
    *   Va chercher les valeurs dans les vecteur en attributs
    */
    void _itVsrec();
    /**
    *   \brief Lance le test statiqueVsdynamique
    *
    *   Méthode qui lance le test pour Spr_rec statique en premier puis Spr_rec dynamique
    *   Chronomètre le temps des deux tests et les compare
    *   Va chercher les valeurs dans les vecteurs en attributs
    */
    void _statiqueVsdynamique();
    /**
    *   \brief Lance le test itvslist
    *
    *   Méthode qui lance le test pour Spr_ite statique en premier puis Spr_list statique
    *   Chronomètre le temps des deux test et les compare
    *   Va chercher les valeurs dans les vecteurs en attributs
    */
    void _itVslist();
    
    /**
    *   \classe Chrono
    *   \brief Classe pour chronométrer des test 
    *
    *   Cette classe permet de démarrer un chrono, le mettre en pause ou l'arréter
    *   On peut ensuite récupérer le temps
    */
    class Chrono
    {
    public:
        /**
        *   \brief Constructeur
        *   \param elapsed_time Temps avec lequel le chrono démarre, 0 par défaut
        *   \param precision Unités du chrono, milliseconds par défaut
        */
        Chrono( float elapsed_time=0,std::string precision="milliseconds");
        /**
        *   \brief Lance le chrono
        *
        *   Mets la valeur du temps actuel dans _start et isCalculing à true
        */
        void start();
        /**
        *   \brief Arréte le chrono 
        *   
        *   Prend la valeur de _start et la compare avec la valeur de temps actuel, ajoute le résultat dans _elapsed_time
        */
        void stop();
        /**
        *   \brief Remets le chrono a zéro
        *
        *   Mets la valeur de elapsed_time à 0
        */
        void reset();
        /**
        *   \brief Renvoie la valeur de elapsed_time
        *
        *   Permet aux méthodes qui utilisent le chrono de récupérer la valeur finale
        */
        float getDuration();
    private:
        /** Temps de départ du chrono*/
        std::chrono::time_point<std::chrono::system_clock> _start;
        /** Temps entre un start() et un stop() */
        float _elapsed_time;
        /** unité du temps du test */
        std::string _precision;
        /** booléen si le chrono a démarré ou pas*/
        bool _isCalculing;
    };
};

#endif // __TESTENV_INCLUDED__
