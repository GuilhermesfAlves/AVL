#include "avl-tree.hpp"

int main(){
    AVLTree arv;
    char s;
    int val;

    while (1){        
        cin >> s;
        if ((feof(stdin)) || (s == 'q'))
            break;

        cin >> val;

        if (s == 'i'){
            arv.insere(val);
            arv.imprime();
        }
        else if (s == 'r'){
            arv.remove(val);
            arv.imprime();
        }
        else if (s == 'b'){
            arv.busca(val);
        }
        else{
            cout << "tipo não encontrado";
        }
        cout << endl;
    }

    return 0;
}