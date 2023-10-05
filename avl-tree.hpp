#ifndef __AVL_TREE_CPP__
#define __AVL_TREE_CPP__

#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

class nodo_t {
    public:
    nodo_t(int k): val(k), alt(1), esq(NULL), dir(NULL){}
    
    nodo_t* dir;
    nodo_t* esq;
    int alt;
    int val;
    
};

class AVLTree {
    public:
    nodo_t* root;
    private:
    int altura(nodo_t* nodo);

    int fator_balanceamento(nodo_t* nodo);

    void att_altura(nodo_t* nodo);

    nodo_t* rot_dir(nodo_t* y);

    nodo_t* rot_esq(nodo_t* x);

    nodo_t* insere(nodo_t* nodo, int val);

    void destroi(nodo_t* nodo);

    nodo_t* remove(nodo_t* nodo, int val);

    nodo_t* minValuenodo(nodo_t* nodo);

    void imprime_arv(nodo_t* nodo);

    void busca(nodo_t* nodo, int val);

    public:
    void imprime(){
        imprime_arv(root);
    }

    void insere(int val){
        root = insere(root,val);
    }

    void remove(int val){
        root = remove(root,val);
    }
    
    void busca(int val){
        busca(root,val);
    }

    AVLTree(): root(NULL){}

    ~AVLTree(){
        destroi(root);
    }
};

#endif /*__AVL_TREE_CPP__*/