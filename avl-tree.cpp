#include <avl-tree.hpp>

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

    if (!nodo) return nodo;

    if (val < nodo -> val) {
        nodo -> esq = remove(nodo -> esq, val);
    } else if (val > nodo -> val) {
        nodo -> dir = remove(nodo -> dir, val);
    } else {
        // nodo with only one child or no child
        if (!(nodo -> esq) || !(nodo -> dir)) {
            temp = nodo -> esq ? nodo -> esq : nodo -> dir;

            if (!temp) {
                temp = nodo;
                nodo = nullptr;
            } else {
                *nodo = *temp;
            }

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

    if (nodo == nullptr) return nodo;

    updateHeight(nodo);

    int balance = getBalanceFactor(nodo);

    if (balance > 1 && getBalanceFactor(nodo -> esq) >= 0) {
        return rotatedir(nodo);
    }
    if (balance > 1 && getBalanceFactor(nodo -> esq) < 0) {
        nodo -> esq = rotateesq(nodo -> esq);
        return rotatedir(nodo);
    }
    if (balance < -1 && getBalanceFactor(nodo -> dir) <= 0) {
        return rotateesq(nodo);
    }
    if (balance < -1 && getBalanceFactor(nodo -> dir) > 0) {
        nodo -> dir = rotatedir(nodo -> dir);
        return rotateesq(nodo);
    }

    return nodo;
}

// Função auxiliar para encontrar o nó com a chave mínima
nodo* minValuenodo(nodo* nodo) {
    nodo* current = nodo;
    while (current->esq != nullptr) {
        current = current->esq;
    }
    return current;
}