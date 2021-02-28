// José Luis dos Santos Araujo - 472435
// Joyce Kelly Chaves Barros da Silva - 472032

// José Luis e Joyce Kelly
#ifndef MATRIZ_H
#define MATRIZ_H

#include <string>
using namespace std;

struct Node;

class Matriz {
private:
    // Ponteiro para o no cabeca da lista
    Node* head;
    int rows, cols;
public:
    /**
     * Recebe as linhas e colunas da Matriz
     * @param rows Linhas da Matriz
     * @param cols Colunas da Matriz
     * */
    Matriz(int rows, int cols);

    /*Destrutor: libera memoria alocada
    Apos liberar a memoria alocada, esta funcao deve
    escrever na saida a mensagem "Matriza liberada"*/
    ~Matriz();

    /*
    Esse método lê, de um arquivo de entrada, os elementos diferentes de zero de uma
    matriz e monta a estrutura especificada anteriormente. Considere que a entrada
    consiste dos valores de m e n (número de linhas e de colunas da matriz) seguidos
    de triplas (i, j, valor) para os elementos diferentes de zero da matriz.
    */
    void lerMatriz(string file);

    /*
    Esse método imprime (uma linha da matriz por linha na saída) a matriz A, inclusive
    os elementos iguais a zero.
    */
    void imprime();
    /**
     * Pega o ponteiro na linha e coluna especificada
     * */
    Node* getPos(int row, int col);
    /**
     * Pega o ponteiro da coluna anterior a inserção
     * */
    Node* getColuna(int row, int col);
    /**
     * Pega o ponteiro da linha anterior a inserção
     * */
    Node* getLinha(int row, int col);
    /*
    Esse método insere o valor v na linha i, coluna j da matriz A.
    */
    void insere(int row, int col, double v);

    /*
    Esse método remove o valor v na linha i, coluna j da matriz A.
    */
    void remove(int row, int col);

    /*
    Essa função recebe como parâmetro as matrizes A e B, devolvendo uma matriz C
    que é a soma de A com B.
    */
    Matriz* soma(Matriz* A, Matriz* B);

    /*
    Esse método recebe como parâmetro as matrizes A e B, devolvendo uma matriz C
    que é o produto de A por B.
    */
    Matriz* multiplica(Matriz* A, Matriz* B);
};

#endif