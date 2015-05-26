/*
 * =====================================================================================
 *
 *       Filename:  ArrayTree.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  13/04/2015 13:35:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Samuel BOURASSEAU (SB), samuel.bourasseau@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef ARRAYTREE_H_INCLUDED
#define ARRAYTREE_H_INCLUDED

#include <string>
#include <random>

class Node;
/**
*   \classe ArrayTree
*   \brief Classe représentant un arbre binaire statique
*   
*   La classe contient quatre tableaux, parent/filsGauche/filsDroit/data. Quand on ajoute une node, elle vérifie qu'il y a suffisamment de place
*   pour ajouter une node, sinon elle créée un nouveau tableau plus grand et remets les anciens noeuds et le nouveau
*
*/
class ArrayTree
{
public:
/**
*   \brief Constructeur par défaut
*   
*   Mets tous les tableaux à 0
*/
    ArrayTree();

/**
*   \brief Construit un arbre en prenant une node dynamique pour exemple
*   \param Node Node utilisée pour l'exemple
*
*   Copie le contenu d'un node dynamique dans une node statique.
*/
    ArrayTree(Node&);
/**
*   \brief Constructeur par recopie
*   \param ArrayTree Node utilisée pour la recopie
*
*   Construit un noeud en utilisant selui en paramètre pour exemple
*/
    ArrayTree(const ArrayTree&);
/** \brief Ajout d'un opérateur =   \param ArrayTree ArrayTree avec laquelle est comparée l'arbre sur laquelle l'opérateur est appelé*/
    ArrayTree& operator =(const ArrayTree&);
/** Destructeur par défaut de l'arbre*/
    ~ArrayTree() = default;

/**
*   \brief Permet l'ajout de node 
*   \return Retourne le nouveau total de node 
*   
*   Augmente le nombre de node
*/
    int newNode(); // Gives back the index of a clear node

/**
*   \brief Permet d'insérer une Node dans un arbre
*   \param E data de la nouvelle de Node
*   
*   Insert une Node, va au hasard à droite ou à gauche le node a deux fils et réessaie d'insérer la node dans les fils
*/
    void insert(int E);

/**
*   \brief Enlève enlève le parent du noeud de l'arbre dans lequel il est
*   \param node Numéro de la node a enlevé
*   \return Retourne l'arbre enlevé avec la nodeA
*
*   La fonction mets le parent du parent du noeud à -1, le père devient donc une racine. Elle renvoie ensuite cette arbre
*/
    ArrayTree* degraph(int node);
/**
*   \brief Raccroche un noeud à l'arbre
*   \param child Arbre qui est raccroché à l'arbre
*   \return Retourne le noeud sur lequel l'arbre a été raccroché
*
*   Cette fonction rajoute un fils sur le noeud sur lequel il est appelé, et mets en petit-fils l'ancien fils et le noeud en paramètre
*/
    int regraph(ArrayTree& child, int node);

/**
*   \brief Vérifie l'arbre
*   \return Retourne si l'arbre est conformes
*   \param node Node par laquelle la fonction commence à vérifier
*
*/
    bool check(int node) const;

/**   \brief Permet de changer les data d'un noeud */
    void setData(int node, int data) {_data[node] = data;}

/** \brief Permet de récupérer les data d'un noeud \return Retourne les data d'un noeud */
    int getData(int node) const {return _data[node];}
/** \brief Permet de récupérer le parent \return Retourn un pointeur vers le parent */
    int getParent(int node) const {return _parents[node];}
/** \brief Permet de récupérer le fils gauche du noeud \return Retourne un pointeur vers le fils gauche du noeud */
    int getLeft(int node) const {return _lefts[node];}
/** \brief Permet de récupérer le fils droit du noeud \return Retourne un pointeur vers le fils droite du noeud*/
    int getRight(int node) const {return _rights[node];}

/** \brief Indique si le noeud a été initialisé \return Retourne vrai si le noeud est initalisé (_free)*/
    bool isFree(int node) const {return _free[node];}
/** \brief Indique si le noeud est orphelin \return Retourne vrai si le noeud n'a pas de parent*/
    bool isOrphan(int node) const {return _parents[node] == -1;}
/** \brief Indique si le noeud a un fils gauche \return Retourne vrai si le noeud n'a pas de fils gauche*/
    bool isLeftFree(int node) const {return _lefts[node] == -1;}
/** \brief Indique si le noeud a un fils droit \return Retourne vrai si le noeud n'a pas de fils droit*/
    bool isRightFree(int node) const {return _rights[node] == -1;}

/** \brief Donne la taille de l'arbre \return Retourne le nombre de noeud dans l'arbre du noeud sur lequel la fonction est appelé*/
    int size() const {return _nodeCount;}
/**
*   \brief Donne la somme des data 
*   \return Retourne le nombre de data en int
*   
*   Va chercher la somme des data à gauche puis à droit et les ajoute et renvoie
*/
    int dataCount();
/**
*   \brief  Donne le nombre de noeud en tout
*   \return Retourne le nombre de noeud 
*   
*   Dans les faits, utilise l'attribut _nodeCount
*/
    int nodeCount() {return _nodeCount;}

/**
*   \brief Permet l'affichage de l'arbre
*   \return Retourne un chaine de caractère représentant l'arbre
*
*   Affiche tous les éléments de l'arbre, avec leur pointeur pour les différencier (caster en long) grâce à _to_str()
*/
    std::string to_str();
/**
*   \brief Affiche tous les tableaux
*
*   Affiche tout le contenu des tableaux en attributs de la classe
*/
    void dumpToStdout();

/**
*   \brief Permet d'initialiser le SPR_rec
*   \param node Noeud utilisé pour le SPR
*
*   Lance le SPR sur l'arbre grâce à _SPR_rec()
*/
    void SPR_rec(int node);
/**
*   \brief Permet de lancer le SPR_ite
*   \param node Noeud utilisé pour le SPR
*
*   Lance le SPR sur tout l'arbre en itératif
*/
    void SPR_ite(int node);

private:
/**
*   \brief Charge un noeud de Node dans les tableaux
*   \return Retourne l'index de la nouvelle node
*/
    int _load(Node* n);
/**
*   \brief Charge un arbre dans l'arbre
*   \param source Arbre qui va être chargé
*   \param node ???????????
*   \return Retourne l'index ne la nouvelle node
*/ 
    int _load(ArrayTree& source, int node);

/**
*   \brief Retire une node proprement
*   \param node Node a retiré
*   
*   Supprime la node et ce qu'il y a en dessous. Met à jour les tableaux et nodeCount
*/
    void _remove(int node);

/**
*   \brief Défragmente l'arbre
*
*   Va enlever tous les espaces pour les mettre à la fin
*/
    void _defragment();
/**
*   \brief Echange deux noeud 
*   \param nodeA Première node a échanger
*   \param nodeB Deuxième node à échanger
*/
    void _swap(int nodeA, int nodeB);

    void _increaseStorage(); //Enlarges storage by one block
    // TODO : implement a method to fit storage to the stored nodes
/**
*   \brief Permet l'affichage de l'arbre
*   \param acc Chaine en cours de construction
*   \param index ??????????????
*   \param depth hauteur à laquelle doit commencer la fonction
*   \return Retourne un chaine de caractère représentant l'arbre
*
*   Affiche tous les éléments de l'arbre, avec leur pointeur pour les différencier (caster en long)
*/
    std::string _to_str(std::string acc, int depth, int index);

/** \brief Donne le nombre de noeuds stockables \return Retourne le nombre de noeuds stockables*/
    int _storageSize() {return _blockCount * _blockSize;}

/** Nombre de blocks utilisés*/
    int _blockCount = 0;
/** Nombre de noeuds par blocs*/
    int _blockSize = 5;
/** Nombres de nodes dans l'arbre*/
    int _nodeCount = 0;
    
/** Tableau des parents*/
    int* _parents = nullptr;
/** Tableau des fils gauche*/
    int* _lefts = nullptr;
/** Tableau des fils droits */
    int* _rights = nullptr;
/** Tableau des données */
    int* _data = nullptr;
/** Tableau des nodes libres ou non*/
    bool* _free = nullptr;
    
/** Moteur de RNG du noeud*/
    static std::mt19937 rng;
/** Distribution pour l'aléatoire binaire du noeud*/
    static std::uniform_int_distribution<int> binaryPick;

/** 
*   \brief Lance SPR_rec sur tout l'arbre
*   \param subTree Noeud du sous-arbre utilisé pour le SPR
*   \param node Node sur laquelle SPR travaille
*   \param count Nombre de degraph/regraph effectués
*   \return Retourne le nombre de degraph/regraph effectués
*
*/
    int _SPR_rec(ArrayTree& subTree, int node, int count);
};

#endif // ARRAYTREE_H_INCLUDED

