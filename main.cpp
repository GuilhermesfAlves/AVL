#include "avl-tree.hpp"

int main(){
    nodo* root;
    char s;
    int val;

    root = NULL;
    while (1){        
        cin >> s;
        if (feof(stdin))
            break;

        cin >> val;

        if (s == 'i'){
            root = insere(root, val);
            confere_bal(&root);
            root -> imprime_arv();
        }
        else if (s == 'r'){
            root = remov(&root, val);
            confere_bal(&root);
            root -> imprime_arv();
        }
        else if (s == 'b'){
            busca(root, val);
        }
        else{
            cout << "tipo não encontrado";
        }
        cout << endl;
    }

    root -> destroi_arv();
    return 0;
}