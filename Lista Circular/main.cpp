// José Luis dos Santos Araujo - 472435
// Joyce Kelly Chaves Barros da Silva - 472032
#include<iostream>
#include<sstream>
#include "List.h"

using namespace std;

int main() {

    List** l = new List * [10];
    int lists = 0;
    int op = 0;
    // Joyce Kelly 
    string msg = "0 - Criar Lista\n1 - Adicionar no final:\n2 - Remover no final:\n3 - Inserir Depois\n4 - Remover\n5 - Remover todos\n6 - Mostrar\n7 - Mostrar ao Contrário\n8 - É Vazio?\n9 - Tamanho\n10 - Limpar\n11 - Concatenar\n12 - Copiar\n13 - Copiar de um array\n14 - É igual? \n\n-1 - SAIR";
    do {
        cout << "Selecione uma opção:" << endl << msg << endl;
        cin >> op;
        if (op == 0) {
            l[lists] = new List();
            cout << "Lista " << lists << " criada!" << endl;
            lists++;
        }
        else if (op == 1) {
            int key = 0;
            int lista;
            cout << "Insira a lista:" << endl;
            cin >> lista;
            cout << "Insira um valor:" << endl;
            cin >> key;
            l[lista]->push_back(key);
        }

        else if (op == 2) {
            int lista;
            cout << "Insira a lista:" << endl;
            cin >> lista;
            cout << l[lista]->pop_back();
        }

        else if (op == 3) {
            int key = 0;
            int k = 0;
            int lista;
            cout << "Insira a lista:" << endl;
            cin >> lista;
            cout << "Insira o valor e o local:" << endl;
            cin >> key;
            cin >> k;
            l[lista]->insertAfter(key, k);
        }

        else if (op == 4) {
            int key = 0;
            int lista;
            cout << "Insira a lista:" << endl;
            cin >> lista;
            cout << "Insira o valor:" << endl;
            cin >> key;
            l[lista]->remove(key);
        }

        else if (op == 5) {
            int key = 0;
            int lista;
            cout << "Insira a lista:" << endl;
            cin >> lista;
            cout << "Insira o valor:" << endl;
            cin >> key;
            l[lista]->removeAll(key);
        }

        else if (op == 6) {
            int lista;
            cout << "Insira a lista:" << endl;
            cin >> lista;
            l[lista]->print();
        }

        else if (op == 7) {
            int lista;
            cout << "Insira a lista:" << endl;
            cin >> lista;
            l[lista]->printReverse();
        }

        else if (op == 8) {
            int lista;
            cout << "Insira a lista:" << endl;
            cin >> lista;
            if (l[lista]->empty()) {
                cout << "É vazia!";
            }
            else {
                cout << "Não é vazia!";
            }
        }

        else if (op == 9) {
            int lista;
            cout << "Insira a lista:" << endl;
            cin >> lista;
            cout << "O tamanho é " << l[lista]->size() << endl;
        }

        else if (op == 10) {
            int lista;
            cout << "Insira a lista:" << endl;
            cin >> lista;
            l[lista]->clear();
        }

        else if (op == 11) {
            int lista1;
            cout << "Insira a primeira lista:" << endl;
            cin >> lista1;
            int lista2;
            cout << "Insira a segunda lista:" << endl;
            cin >> lista2;
            l[lista1]->concat(l[lista2]);
        }

        else if (op == 12) {
            int lista, lst;
            cout << "Insira a lista que deseja copiar:" << endl;
            cin >> lista;
            l[lists] = l[lista]->copy();
            cout << "Lista copiada no índice " << lists << endl;
            lists++;
        }

        else if (op == 13) {
            int n = 0;
            int lista;
            cout << "Insira a lista:";
            cin >> lista;
            cout << "Insira o tamanho do array:" << endl;
            cin >> n;
            cout << "Insira os valores do array:" << endl;
            int arr[n];
            for (int i = 0;i < n;i++) {
                cin >> arr[i];
            }
            l[lista]->copyArray(n, arr);
        }

        else if (op == 14) {
            int lista1;
            cout << "Insira a primeira lista:" << endl;
            cin >> lista1;
            int lista2;
            cout << "Insira a segunda lista:" << endl;
            cin >> lista2;
            if (l[lista1]->equal(l[lista2])) {
                cout << "É igual" << endl;
            }
            else {
                cout << "Não é igual!" << endl;
            }
        }
        else if (op != -1) {
            cout << "Escolha uma opção apresentada no menu!" << endl;
        }
        cout << endl;
    } while (op != -1);
    return 0;
}