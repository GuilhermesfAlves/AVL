#ifndef __AVL_TREE_CPP__
#define __AVL_TREE_CPP__

#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

class nodo_t {
    public:
    
    nodo_t* dir;
    nodo_t* esq;
    int alt;
    int val;
    
    nodo_t(int k): val(k), alt(1), esq(NULL), dir(NULL){}
};

class AVLTree {
    nodo_t* root;

    int altura(nodo_t* nodo);

    int fator_balanceamento(nodo_t* nodo);

    void att_altura(nodo_t* nodo);

    nodo_t* rot_dir(nodo_t* y);

    nodo_t* rot_esq(nodo_t* x);

    nodo_t* insere(nodo_t* nodo, int val);

    void destroi(nodo_t* nodo);

    nodo_t* remove(nodo_t* nodo, int val)
};

#endif /*__AVL_TREE_CPP__*/