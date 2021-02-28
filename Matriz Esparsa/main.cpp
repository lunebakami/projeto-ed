// José Luis dos Santos Araujo - 472435
// Joyce Kelly Chaves Barros da Silva - 472032

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Matriz.h"

using namespace std;

int main() {

    // José Luis
    ifstream input;
    input.open("matriz.txt");

    string row, col;
    input >> row;
    input >> col;
    int index = row.find(',');
    row[index] = '\0';

    int rows = stoi(row);
    int cols = stoi(col);

    Matriz* m = new Matriz(rows, cols);
    m->lerMatriz("matriz.txt");
    m->imprime();

    // Inserir valor 30 na linha 1 coluna 3
    m->insere(1, 3, 30);
    m->imprime();

    // Remover valor 30 na linha 1 coluna 3
    m->remove(1, 3);
    m->imprime();

    Matriz* m2 = new Matriz(rows, cols);
    m2->lerMatriz("matriz.txt");

    // Inserir valor 30 na linha 1 coluna 3 na Matriz 2
    m2->insere(1, 3, 30);

    // Soma Matriz m com a Matriz m2
    Matriz* m3 = m->soma(m, m2);
    m3->imprime();

    // Multiplica Matriz m com a Matriz m2
    Matriz* m4 = m->multiplica(m, m2);
    m4->imprime();
    return 0;
}