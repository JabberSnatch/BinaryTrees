/*
 * =====================================================================================
 *
 *       Filename:  NodeTree.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  18/05/2015 11:23:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Samuel BOURASSEAU (SB), samuel.bourasseau@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __NODETREE_H_INCLUDED__
#define __NODETREE_H_INCLUDED__

#include "Node.hpp"

class NodeTree
{
public:
/**
 *  \brief Constructeur par défaut
 */
    NodeTree();
/**
 *  \brief Constructeur à partir d'un Node
 *  \param node Noeud qui servira de racine à l'arbre
 */
    NodeTree(const Node& n);
/**
 *  \brief Destructeur par défaut
 */
    ~NodeTree() = default;
    void _setTree(Node* node);
/**
 *  \brief Permet d'insérer une donnée dans l'arbre
 *  \param E Element à insérer
 */
    void insert(int E);
/**
 *  \brief Permet d'insérer une donnée dans l'arbre, en le gardant aussi équilibré que possible
 *  \param E Element à insérer
 */
    void insertBalanced(int E);

/**
 *  \brief Permet d'ajouter n feuilles à l'arbre, agencées de manière aléatoire
 *  \param n Nombre de feuille à ajouter
 */
    void insertNLeaves(int n);
/**
 *  \brief Permet d'ajouter n feuilles à l'arbre deux à deux.
 *  \param n Nombre de feuille à insérer
 *  Si l'arbre contenait déjà le chemin d'une arborescence, celle ci est détruite
 *  Produit des arbres équilibrés uniquement pour des n puissances de 2
 */
    void insertNBalanced(int n);

/**
 *  \brief Vérifie si l'arbre est valide
 *  \return Renvoie vrai si l'abre est valide
 */
    bool check() const;
    
/**
 *  \brief Retourne le noeud désigné par l'indice donné
 *  \param num Indice du noeud à renvoyer
 *  \return Noeud désigné par l'indice donné
 */
    Node* nodeAt(int num);

/**
 *  \brief Définis le noeud donné comme étant la racine de l'arbre
 *  \param n Le nouvelle racine
 */
    void setRoot(Node* n);
/**
 *  \brief Accesseur de la racine
 *  \return Pointeur sur le noeud racine de l'arbre
 */
    Node* getRoot() {return _root;}

/**
 *  \brief Donne le nombre de noeuds contenus dans l'arbre
 *  \return Nombre de noeuds de l'arbre
 */
    int size() const {return _root->descendantCount()+1;}
/**
 *  \brief Donne le nombre de feuilles de l'arbre
 *  \return Nombre de feuilles de l'arbre
 */
    int leafCount();
/**
 *  \brief Donne la somme des données contenues dans l'arbre
 */
    int dataCount() {return _root->dataCount();}
/**
 *  \brief Donne le nombre de noeuds de l'arbre
 */
    int nodeCount() {return _root->nodeCount();}

/**
 *  \brief Traduit l'arbre en une chaîne de caractères
 *  \return Chaine de caractère représentant l'arbre
 */
    std::string to_str() {return _root->to_str();}

/**
 *  \brief Degraph le noeud donné et crée une liste de noeud contenant le reste de l'arbre
 *  \param noeud Noeud à dégrapher
 *  \return Liste des noeuds de l'arbre
 */
    std::vector<Node*> SPR_list_init(Node* noeud);
/**
 *  \brief Applique un SPR à la liste de noeuds donnée avec le noeud
 *  \param noeud Noeud à degrapher/regrapher
 *  \param nodes Liste des noeuds sur lesquels degrapher/regrapher
 */
    void SPR_list(Node* noeud, std::vector<Node*>& nodes);

    void SPR_rec(Node* noeud);
    void SPR_ite(Node* noeud);

private:
/** Racine de l'arbre */
    Node* _root;
};

#endif // __NODETREE_H_INCLUDED__
