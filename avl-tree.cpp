#include <avl-tree.hpp>

void nodo::destroi_arv(){

    if (!this)
        return;
    if (this -> esq)
        this -> esq -> destroi_arv();
    if (this -> dir)
        this -> dir -> destroi_arv();
    free(this);
}

nodo *insere(nodo* arv, int ins){
    if (!arv)
        return cria_no(ins);

    if (arv -> val > ins)
        arv -> esq = insere(arv -> esq, ins);
    else 
        arv -> dir = insere(arv -> dir, ins);
    
    arv -> arruma_alt();
    return arv;
}

void nodo::arruma_alt(){
    this -> alt = maior((this -> esq -> altura_no()), (this -> dir -> altura_no())) + 1;
}

short maior(short a, short b){
    return (a > b)? a: b;
}

short nodo::altura_no(){
    return (this)? this -> alt: -1;
}

short r_arruma_alt(nodo *arv){
    return (arv)? (maior((arv -> esq -> altura_no()), (arv -> dir -> altura_no())) + 1) : -1;
}

void nodo::imprime_arv(){

    cout << "(";
    if (!this){
        cout << ")";
        return;
    }

    cout << this -> val << ",";
    this -> esq -> imprime_arv();
    cout << ",";
    this -> dir -> imprime_arv();
    cout << ")";
}

nodo *cria_no(int val){
    nodo *novo;

    if (!(novo = static_cast<nodo*> (malloc(sizeof(nodo))))){
        fprintf(stderr,"ERRO MALLOC");
        exit(1);
    }
    novo -> dir = NULL;
    novo -> esq = NULL;
    novo -> alt = 0;
    novo -> val = val;

    return novo;
}

void busca(nodo* arv, int busc){

    if (!arv)
        return;

    cout << arv -> val;

    if (busc == arv -> val)
        return;
    cout << ",";

    if (busc < arv -> val)
        busca(arv -> esq, busc);

    busca(arv -> dir, busc);
    return;
}

short confere_bal(nodo *arv){
    short bal;
 
    if (!arv) 
        return -1;

    bal = confere_bal(arv -> esq) - confere_bal(arv -> dir);

    if (bal == 2){
        if ((altura_no(arv -> esq -> dir)) > (altura_no(arv -> esq -> esq)))
            arv = rot_esq_j(arv);
        arv = rot_dir_s(arv);
        return r_arruma_alt(arv);
    }
    if (bal == -2){
        if ((altura_no(arv -> dir -> esq)) > (altura_no(arv -> dir -> dir)))
            arv = rot_dir_j(arv);
        arv = rot_esq_s(arv);
        return r_arruma_alt(arv);
    }
     
    return arv -> alt;
}

nodo *rot_dir_s(nodo* arv){
    nodo *aux;
    nodo *root;

    root = arv -> esq;
    aux = root -> dir;
    root -> dir = arv;
    arv -> esq = aux;
    
    return root;
}

nodo *rot_esq_s(nodo* arv){ 
    nodo *aux;
    nodo *root;

    root = arv -> dir;
    aux = root -> esq;
    root -> esq = arv;
    arv -> dir = aux;

    return root;
}

nodo *rot_dir_j(nodo* arv){
    nodo *aux;

    aux = arv -> dir -> esq -> dir;
    arv -> dir -> esq -> dir = arv -> dir;
    arv -> dir = arv -> dir -> esq;
    arv -> dir -> dir -> esq = aux;

    return arv;
}

nodo *rot_esq_j(nodo *arv){
    nodo *aux;

    aux = arv -> esq -> dir -> esq;
    arv -> esq -> dir -> esq = arv -> esq;
    arv -> esq = arv -> esq -> dir;
    arv -> esq -> esq -> dir = aux;

    return arv;
}

nodo* nodo::f_esq(){
    nodo *aux;

    if (!this -> esq){
        aux = *this;
        *this = this -> dir;
        return aux;
    }
    
    return nodo::f_esq();
}

nodo* nodo::f_dir(){
    nodo *aux;

    if (!this -> dir){
        aux = this;
        this = this -> esq;
        return aux;
    }

    return nodo::f_dir();
}

nodo *remov(nodo** arv, int rem){
    nodo *aux;

    if (!(*arv)){
        fprintf(stderr, "não encontrado");
        exit(1);
    }
    
    if ((*arv) -> val == rem){
        if (((*arv) -> dir) && ((*arv) -> esq)){
            if (((*arv) -> dir -> alt) > ((*arv) -> esq -> alt))
                aux = f_esq(&(*arv) -> dir);
            else 
                aux = f_dir(&(*arv) -> esq);
            aux -> dir = (*arv) -> dir;
            aux -> esq = (*arv) -> esq;
            free(*arv);
            return aux;
        }
        
        if ((*arv) -> dir){
            aux = (*arv) -> dir;
            free(*arv);
            return aux;
        }

        if ((*arv) -> esq){
            aux = (*arv) -> esq;
            free(*arv);
            return aux;
        }

        free(*arv);
        return NULL;
    }

    if ((*arv) -> val > rem){
        (*arv) -> esq = remov(&(*arv) -> esq, rem);
        return *arv;
    }

    (*arv) -> dir = remov(&(*arv) -> dir, rem);
    return *arv;
}