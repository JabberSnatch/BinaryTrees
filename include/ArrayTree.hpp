
#ifndef ARRAYTREE_H_INCLUDED
#define ARRAYTREE_H_INCLUDED

/**
*   \file ArrayTree.hpp
*   \brief Permet de construire un arbre binaire statique
*   \author Samuel Bourasseau, Rodolphe Charlot
*/

#include <string>
#include <random>

class Node;
class NodeTree;

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
*   \deprecated Utiliser Node directement est déconseillé. Essayez d'utiliser un NodeTree à la place
*   \brief Construit un arbre en prenant une node dynamique pour exemple
*   \param Node Node utilisée pour l'exemple
*
*   Copie le contenu d'un arbre dynamique dans un arbre statique.
*/
    ArrayTree(Node&);

/**
 *  \brief Construit un ArrayTree en copiant la structure d'un NodeTree
 *  \param NodeTree Arbre source à copier
 *
 *  Copie l'arborescence désignée par le NodeTree passé en paramètre
 */
    ArrayTree(NodeTree&);
/**
*   \brief Constructeur par recopie
*   \param ArrayTree Arbre à copier
*
*   Construit un arbre en utilisant celui en paramètre pour exemple
*/
    ArrayTree(const ArrayTree&);
/** \brief Opérateur d'assignation  
 *  \param ArrayTree Arbre à assigner
 */
    ArrayTree& operator =(const ArrayTree&);
/** Destructeur par défaut de l'arbre*/
    ~ArrayTree() = default;

/**
*   \brief Alloue l'espace nécessaire pour un nouveau noeud vierge
*   \return Retourne l'index du noeud alloué
*   
*   Augmente le nombre de noeuds
*/
    int newNode();

/**
*   \brief Permet d'insérer un élément dans l'arbre
*   \param E élément à insérer
*   
*   Place l'élément dans le noeud appelant si il est libre.
*   Si le noeud n'est pas libre et a zéro ou un enfant, un enfant est créé et l'élément y est placé
*   Sinon, choisis au hasard un des enfants puis essaie d'y insérer la donnée.
*/
    void insert(int E);

/**
 *  \brief Débranche le père du noeud à l'index donné de l'arbre, en y laissant son frère
 *  \param node Indice du noeud à degrapher dans l'abre
 *  \return Renvoie node
 */
    int degraph(int node); 
/**
 *  \brief Branche le père du noeud au dessus de l'index donné, de telle manière que les noeuds child et node soient frères
 *  \param child Indice du noeud à regrapher. Devrait être le fils unique d'un noeud racine
 *  \param node Indice du noeud sur lequel regrapher. Après opération, devrait être le frère du noeud child
 *  \return Renvoie child
 */
    int regraph(int child, int node);

/**
*   \brief Vérifie l'arbre
*   \return Vrai si l'arbre est valide
*   \param node Noeud de départ de la vérification. Considéré comme la racine de l'arbre à vérifier
*/
    bool check(int node) const;

/**   \brief Permet de changer les data d'un noeud */
    void setData(int node, int data) {_data[node] = data;}

/** \brief Permet de récupérer l'indice de la racine de l'arbre */
    int getRoot() const {return _root;}
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
*   \brief Donne la somme des entiers stockés par les noeuds
*   \return Retourne la somme des noeuds en int
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
*   \brief Traduit l'arbre en chaîne de caractère
*   \return Retourne un chaine de caractère représentant l'arbre
*
*   Affiche tous les éléments de l'arbre sous forme de couple [donnée _ indice].
*/
    std::string to_str();
/**
*   \brief Affiche l'arbre
*   \return Renvoie une chaine de caractère
*
*   Affiche l'arbre selon la méthode de newick. 
*/
    std::string newick();
/**
*   \brief Affiche tous les tableaux sur la sortie standard
*
*   Affiche tout le contenu des tableaux en attributs de la classe
*/
    void dumpToStdout();

/**
*   \brief SPR implémenté sous forme récursive
*   \param node Noeud à degrapher/regrapher
*
*   Lance le SPR sur l'arbre grâce à _SPR_rec()
*/
    void SPR_rec(int node);
/**
*   \brief SPR implémenté sous forme itérative
*   \param node Noeud à degrapher/regrapher
*
*   Lance le SPR sur tout l'arbre en itératif
*/
    void SPR_ite(int node);

    std::vector<int> SPR_list_init(int noeud);
    void SPR_list(int noeud, std::vector<int>& nodes);

private:
    void _SPR_list_init(int noeud, std::vector<int>& nodes);
/**
*   \brief Charge un arbre dynamique dans l'ArrayTree appelant
*   \param n Noeud racine de l'arbre à charger
*   \return Retourne l'index de la racine de l'arbre chargé
*/
    int _load(Node* n);
/**
*   \brief Charge un noeud statique et ses descendants dans l'ArrayTree appelant
*   \param source Arbre à charger
*   \param node Indice dans source du premier noeud à charger
*   \return Retourne l'index de la racine de l'arbre chargé
*/ 
    int _load(ArrayTree& source, int node);

/**
*   \brief Supprime un noeud et ses descendants de l'arbre
*   \param node Noeud à libérer
*   
*   Les valeurs de tous les noeuds concernés sont replacées dans l'état par défaut.
*   Conduit souvent à une fragmentation des données dans le conteneur
*/
    void _remove(int node);

/**
*   \brief Défragmente l'arbre
*
*   Défragmente l'arbre à l'aide d'un tri à bulle
*/
    void _defragment();

/**
 *  \brief Permet de redéfinir l'emplacement du noeud racine de l'arbre
 *  \param node Indice où se trouve la nouvelle racine
 */
    void _setRoot(int node) {_root = node;}
/**
*   \brief Echange deux noeud dans le conteneur, et actualise les références
*   \param nodeA Premièr noeud a échanger
*   \param nodeB Deuxième noeud à échanger
*/
    void _swap(int nodeA, int nodeB);

/**
 *  \brief Agrandit le conteneur d'un bloc
 */
    void _increaseStorage();
    // TODO : implement a method to fit storage to the stored nodes
/**
*   \brief Fonction helper de to_str
*   \param acc Chaine en cours de construction
*   \param index noeud courant
*   \param depth profondeur du noeud courant
*   \return Retourne un chaine de caractère représentant l'arbre
*
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

/** Indice de la racine de l'arbre */
    int _root = 0;

    
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
    
/** Moteur de RNG des arbres statiques*/
    static std::mt19937 rng;
/** Distribution pour l'aléatoire binaire du noeud*/
    static std::uniform_int_distribution<int> binaryPick;

/** 
*   \brief Lance SPR_rec sur tout l'arbre
*   \param subTreeRoot Noeud du sous-arbre utilisé pour le SPR
*   \param currentNode Node sur laquelle SPR travaille
*   \param count Nombre de degraph/regraph effectués
*   \return Retourne le nombre de degraph/regraph effectués
*
*/
    int _SPR_rec(int subTreeRoot, int currentNode, int count);
};

#endif // ARRAYTREE_H_INCLUDED

