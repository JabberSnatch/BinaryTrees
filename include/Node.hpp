
#ifndef __NODE_H_INCLUDED__
#define __NODE_H_INCLUDED__

/**
*   \file Node.hpp
*   \brief Permet de construire un arbre binaire dynamique
*   \author Samuel et Rodolphe
*/

#include <string>
#include <random>
#include <iostream>
#include <sstream>



/**
*   \class Node 
*   \brief Classe représentant un arbre binaire dynamique
*
*   La classe construit une racine pour un arbre binaire, à laquelle on rajoute des noeuds par insert ou insertBalanced
*   On peut après lui appliquer les actions sur les arbres binaires, dont le SPR en itératif, récursif, list.
*
*/
class Node
{
public:
/**
*   \class NodeIter 
*   \brief Classe pour faire un itérateur sur Node
*
*   La classe permet de créer un itérateur sur les éléments dans Node
*
*/
    class NodeIter;

/**
*   \brief Constructeur par défaut
*
*   Mets toutes les valeurs a nullptr (pas de parent, pas de fils et pas de data)
*/
    Node() = default;
    
/**
*   \brief Constructeur avec rajout de donnée et d'un parent
*
*   \param data Donnée contenu dans le noeud
*   \param parent Node parent pour la nouvelle node
*/
    Node(int data, Node* parent = nullptr);
/** \brief Constructeur par recopie \param Node Node utilisé pour copier les données*/
    Node(const Node&);
/** \brief Ajout d'un opérateur =   \param Node Node avec laquelle est comparée la node sur laquelle l'opérateur est appelé*/
    Node& operator =(const Node&);
    
/**
*   \brief Permet de cloner une node
*   \return Retourne un pointeur vers un nouveau Node contenant les données du noeud actuel
*/
    Node* clone();
/** \brief Destructeur de Node*/
    ~Node();

/**
*   \brief Permet d'insérer une Node dans un arbre
*   \param E data de la nouvelle de Node
*   
*   Insert une Node, va au hasard à droite ou à gauche le node a deux fils et réessaie d'insérer la node dans les fils
*
*/
    void insert(int E);
/**
*   \brief Permet d'insérer de façon équilibrée une Node dans un arbre
*   \param E data de la nouvelle Node
*
*   Insert une Node, va chercher le premier noeud pour laisser l'arbre équilibré et l'insert
*/
    void insertBalanced(int E);
/**
*   \brief Permet d'ajouter un fils à un noeud
*   \param noeud Node a rajouté
*   \return Retourne si l'ajout de la node a réussi
*
*/
    bool addChild(Node * noeud);

/**
*   \brief Enlève enlève le parent du noeud de l'arbre dans lequel il est
*   
*   La fonction mets le parent du parent du noeud à nullptr, le père devient donc une racine.
*/
    void degraph();
/**
*   \brief Raccroche un noeud à l'arbre
*   \param child Noeud qui est raccrochée à l'arbre
*   \return Retourne si l'opération réussie
*
*   Cette fonction rajoute un fils sur le noeud sur lequel il est appelé, et mets en petit-fils l'ancien fils et le noeud en paramètre
*/
    bool regraph(Node* child);

/**
*   \brief Vérifie l'arbre, doit être appelé sur la racine
*   \return Retourne si l'arbre est bien conforme
*
*   Lance la vérification sur les noeuds
*/
    bool check() const;
/**
*   \brief Vérifie si les noeud sont bien conforme 
*   \return Retourne si les noeuds sont bien conformes
*
*   Vérifie si l'arbre est conforme (si le noeud A a bien le noeud B en fils et si le noeud B a bien le noeud A en parent)
*/
    bool nodeCheck() const;

/**
*   \brief Permet de récupérer la racine de l'arbre
*   \return Retourne un pointeur vers la racine
*
*   La fonction cherche le parent le plus haut, et retourne un pointeur vers ce noeud. Peut-être appelé dans tout l'arbre
*/
    Node* findRoot();
/** \brief Donne le nombre de descendants   \return Retourne le nombre de fils du noeud*/
    int descendantCount() const;
/**
*   \brief Donne le noeud à un index donné
*   \param num Numéro du noeud demandé
*   \return Retourne un pointeur vers le noeud demandé, nullptr sinon
*   
*   L'index commence à 0 et va jusqu'au nombre de noeud - 1
*   Appelle _nodeAt() pour tout chercher
*/
    Node* nodeAt(int num);

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
*   Dans les faits, utilise descendantCount() et rajoute 1
*/
    int nodeCount();
/**
*   \brief Affiche l'arbre
*   \return Renvoie une chaine de caractère
*
*   Affiche l'arbre selon la méthode de newick. 
*/
    std::string newick();

/**   \brief Permet de changer les data d'un noeud */
    void setData(int data) {_data = data;}
/** \brief Permet de récupérer les data d'un noeud \return Retourne les data d'un noeud */
    int getData() const {return _data;}
/** \brief Permet de récupérer le parent \return Retourn un pointeur vers le parent */
    Node* getParent() {return _parent;}
/** \brief Permet de récupérer le fils gauche du noeud \return Retourne un pointeur vers le fils gauche du noeud */
    Node* getLeft() {return _left;}
/** \brief Permet de récupérer le fils droit du noeud \return Retourne un pointeur vers le fils droite du noeud*/
    Node* getRight() {return _right;}

/** \brief Indique si le noeud a été initialisé \return Retourne vrai si le noeud est initalisé (_free)*/
    bool isFree() const {return _free;}
/** \brief Indique si le noeud est orphelin \return Retourne vrai si le noeud n'a pas de parent*/
    bool isOrphan() const {return _parent == nullptr;}
/** \brief Indique si le noeud a un fils gauche \return Retourne vrai si le noeud n'a pas de fils gauche*/
    bool isLeftFree() const {return _left == nullptr;}
/** \brief Indique si le noeud a un fils droit \return Retourne vrai si le noeud n'a pas de fils droit*/
    bool isRightFree() const {return _right == nullptr;}

/** \brief Donne la taille de l'arbre \return Retourne le nombre de noeud dans l'arbre du noeud sur lequel la fonction est appelé*/
    int size() {return findRoot()->descendantCount()+1;}
/** \brief Donne le nombre de feuille de l'arbre \return Retourne le nombre feuille dans l'arbre sur lequel la fonction est appelé*/
    int leafCount();

/** \brief Donne un itérateur sur l'arbre \return Retourne un pointeur vers un itérateur sur l'arbre*/
    Node::NodeIter* begin() {return new Node::NodeIter(this);}
/**
*   \brief Permet l'affichage de l'arbre
*   \return Retourne un chaine de caractère représentant l'arbre
*
*   Affiche tous les éléments de l'arbre, avec leur pointeur pour les différencier (caster en long) grâce à _to_str()
*/
    std::string to_str();
/**
*   \brief Permet d'initialiser SPR_list()
*   \param noeud Noeud utilisé pour le SPR
*   
*   Créer la liste contenant les éléments de l'arbre (sous forme de vecteur)
*/
    void SPR_list_init(Node* noeud);
/**
*   \brief Permet de lancer le SPR_list
*   \param noeud Noeud utilisé pour le SPR
*
*   Doit avec été initialisé par SPR_init(). Lance le SPR sur tout l'arbre grâce au vector nodes'
*/
    void SPR_list(Node* noeud);
/**
*   \brief Permet de lancer le SPR_ite
*   \param noeud Noeud utilisé pour le SPR
*
*   Lance le SPR sur tout l'arbre en itératif
*/
    void SPR_ite(Node* noeud);
/**
*   \brief Permet d'initialiser le SPR_rec
*   \param noeud Noeud utilisé pour le SPR
*
*   Lance le SPR sur l'arbre grâce à _SPR_rec()
*/
    void SPR_rec(Node* noeud);

private:
/**
*   \brief Change le parent par le nouveau en paramètre
*   \param parent Nouveau parent du noeud
*/
    void _setParent(Node* parent) {_parent = parent;}

/** Parent du noeud*/
    Node* _parent;
/** Fils gauche du noeud*/
    Node* _left;
/** Fils droit du noeud */
    Node* _right;
/** Vecteur de noeud, initialisé par SPR_list_init*/
    std::vector<Node*> nodes;

/** Données du noeud */
    int _data;
/** Booléen si le noeud a été initialisé*/
    bool _free;

/** Moteur de RNG du noeud*/
    static std::mt19937 rng;
/** Distribution pour l'aléatoire binaire du noeud*/
    static std::uniform_int_distribution<int> binaryPick;

/** 
*   \brief Lance SPR_rec sur tout l'arbre
*   \param noeud Noeud utilisé pour le SPR
*   \param count Nombre de degraph/regraph effectués
*   \return Retourne le nombre de degraph/regraph effectués
*
*/
    int _SPR_rec(Node* noeud, int count);
/**
*   \brief Permet l'affichage de l'arbre
*   \param acc Chaine en cours de construction
*   \param depth hauteur à laquelle est la fonction
*   \return Retourne un chaine de caractère représentant l'arbre
*
*   Affiche tous les éléments de l'arbre, avec leur pointeur pour les différencier (caster en long)
*/
    std::string _to_str(std::string acc, int depth);
/**
*   \brief Donne le noeud à un index donné
*   \param num Numéro du noeud demandé sur l'arbre actuel
*   \return Retourne le nombre de noeud restant à chercher
* 
*   Va chercher le noeud en regardant le noeud actuel, puis va chercher dans le noeud gauche puis le noeud droit
*/
    int _nodeAt(int num);

public:
/**
*   \classe NodeIter
*   \brief Classe pour créer un itérateur sur Node
*/
    class NodeIter
    {
        friend class Node;

    public:
/** \brief Itinitialise l'itérateur*/
        void begin() {_index = 0;}
/** \brief Va au noeud suivant dans l'ordre de l'index de nodeAt() \return Retourne un pointeur vers le prochain noeud */
        Node* getNext() {return _root->nodeAt(_index++);}
/** \brief Indique si le noeud a un noeud suivant \return Retourne faux si le noeud est le dernier*/
        bool hasNext() {return _index < _size;}
/** \brief Mets l'itérateur au dernier élément*/
        void end() {_index = _size-1;}

    private:
/**
*   \brief Constructeur de NodeIter
*   \param root Racine sur laquelle l'itérateur va itérer
*/
        NodeIter(Node* root)
            :_root(root), _index(0), _size(root->size())
        {}
/** Racine de l'arbre sur lequel l'itérateur itère*/
        Node* _root;
/** Indice de l'élément sur lequel l'itérateur est*/
        int _index;
/** Taille de l'arbre*/
        int _size;

    };

};


#endif // __NODE_H_INCLUDED__
