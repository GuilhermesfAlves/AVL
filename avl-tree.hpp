#ifndef __AVL_TREE_CPP__
#define __AVL_TREE_CPP__

#include <cstdlib>
#include <iostream>

using namespace std;

class nodo {
    public:
    nodo* dir;
    nodo* esq;
    short alt;
    int val;
 
    nodo* f_esq();

    nodo* f_dir();

    void destroi_arv();

    short altura_no();

    void imprime_arv();

    void arruma_alt();
};

nodo* rot_dir_s(nodo* arv);

nodo* rot_esq_s(nodo* arv);

nodo* rot_dir_j(nodo* arv);

nodo* rot_esq_j(nodo* arv);

nodo *insere(nodo* arv, int ins);

nodo *remov(nodo** arv, int rem);

/*função recursiva que imprime a lista de numeros até onde se encontra o número*/
void busca(nodo* arv, int busc); 

nodo *cria_no(int val);

short maior(short a, short b);

short altura_no(nodo *no);

short fator_balanceamento(nodo *no);

short confere_bal(nodo **arv);

short r_arruma_alt(nodo *arv);  

#endif /*__AVL_TREE_CPP__*/