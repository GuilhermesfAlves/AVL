#include "avl-tree.hpp"

int AVLTree::altura(nodo_t* nodo){
    return (nodo)? nodo -> alt : 0;
}

int AVLTree::fator_balanceamento(nodo_t* nodo){
    return (nodo)? altura(nodo -> esq) - altura(nodo -> dir) : 0;
}

void AVLTree::att_altura(nodo_t* nodo){
    nodo -> alt = 1 + max(altura(nodo -> esq), altura(nodo -> dir));
}

void AVLTree::destroi(nodo_t* nodo){

    if (!nodo)
        return;

    AVLTree::destroi(nodo -> esq);
    AVLTree::destroi(nodo -> dir);
    delete nodo;
}

nodo_t* AVLTree::insere(nodo_t* nodo, int val){
    int bal;

    if (!nodo) 
        return new nodo_t(val);

    if (val < nodo -> val)
        nodo -> esq = insere(nodo -> esq, val);
    else if (val > nodo -> val) 
        nodo -> dir = insere(nodo -> dir, val);
    else 
        return nodo;
    

    AVLTree::att_altura(nodo);

    bal = AVLTree::fator_balanceamento(nodo);

    if (bal > 1 && val < nodo -> esq -> val) 
        return AVLTree::rot_dir(nodo);
    
    if (bal < -1 && val > nodo -> dir -> val) 
        return AVLTree::rot_esq(nodo);
    
    if (bal > 1 && val > nodo -> esq -> val) {
        nodo -> esq = AVLTree::rot_esq(nodo -> esq);
        return AVLTree::rot_dir(nodo);
    }

    if (bal < -1 && val < nodo -> dir -> val) {
        nodo -> dir = AVLTree::rot_dir(nodo -> dir);
        return AVLTree::rot_esq(nodo);
    }

    return nodo;
}

nodo_t* AVLTree::rot_dir(nodo_t* y) {
    nodo_t* x;
    nodo_t* T2;

    x = y -> esq;
    T2 = x -> dir;
    x -> dir = y;
    y -> esq = T2;

    AVLTree::att_altura(y);
    AVLTree::att_altura(x);

    return x;
}

nodo_t* AVLTree::rot_esq(nodo_t* x) {
    nodo_t* y;
    nodo_t* T2;

    y = x -> dir;
    T2 = y -> esq;
    y -> esq = x;
    x -> dir = T2;

    AVLTree::att_altura(x);
    AVLTree::att_altura(y);

    return y;
}

nodo_t* AVLTree::remove(nodo_t* nodo, int val) {
    nodo_t* temp;
    int balance;

    if (!nodo) 
        return nodo;

    if (val < nodo -> val)
        nodo -> esq = remove(nodo -> esq, val);
    else if (val > nodo -> val) 
        nodo -> dir = remove(nodo -> dir, val);
    else {
        // nodo with only one child or no child
        if (!(nodo -> esq) || !(nodo -> dir)) {
            temp = (nodo -> esq) ? nodo -> esq : nodo -> dir;

            if (!temp) {
                temp = nodo;
                nodo = NULL;
            } else 
                *nodo = *temp;

            delete temp;
        } else {
            // nodo with two children, get the in-order successor (smallest in the dir subtree)
            temp = minValuenodo(nodo -> dir);

            // Copy the in-order successor's data to this nodo
            nodo -> val = temp -> val;

            // Delete the in-order successor
            nodo -> dir = remove(nodo -> dir, temp -> val);
        }
    }

    if (!nodo) 
        return nodo;

    AVLTree::att_altura(nodo);

    balance = AVLTree::fator_balanceamento(nodo);

    if ((balance > 1) && AVLTree::fator_balanceamento(nodo -> esq) >= 0) {
        return AVLTree::rot_dir(nodo);
    }
    if ((balance > 1) && AVLTree::fator_balanceamento(nodo -> esq) < 0) {
        nodo -> esq = AVLTree::rot_esq(nodo -> esq);
        return AVLTree::rot_dir(nodo);
    }
    if ((balance < -1) && AVLTree::fator_balanceamento(nodo -> dir) <= 0) {
        return AVLTree::rot_esq(nodo);
    }
    if ((balance < -1) && AVLTree::fator_balanceamento(nodo -> dir) > 0) {
        nodo -> dir = AVLTree::rot_dir(nodo -> dir);
        return AVLTree::rot_esq(nodo);
    }

    return nodo;
}

// Função auxiliar para encontrar o nó com a chave mínima
nodo_t* AVLTree::minValuenodo(nodo_t* nodo) {
    nodo_t* atual;

    atual = nodo;
    while (atual -> esq) 
        atual = atual -> esq;
    
    return atual;
}

void AVLTree::imprime_arv(nodo_t* nodo){

    cout << "(";
    if (!nodo){
        cout << ")";
        return;
    }

    cout << nodo -> val << ",";
    imprime_arv(nodo -> esq);
    cout << ",";
    imprime_arv(nodo -> dir);
    cout << ")";
}

void AVLTree::busca(nodo_t* nodo, int val){

    if (!nodo)
        return;

    cout << nodo -> val;

    if (val == nodo -> val)
        return;
    cout << ",";

    if (val < nodo -> val){
        busca(nodo -> esq, val);
        return;
    }
    busca(nodo -> dir, val);
    return;
}
