// José Luis dos Santos Araujo - 472435
// Joyce Kelly Chaves Barros da Silva - 472032

#include "Matriz.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Joyce Kelly e José Luis
struct Node {
    Node* direita;
    Node* abaixo;
    int linha;
    int coluna;
    double valor;

    Node(int linha, int coluna, double valor) {
        direita = nullptr;
        abaixo = nullptr;
        this->coluna = coluna;
        this->linha = linha;
        this->valor = valor;
    }

    Node() {
        direita = nullptr;
        abaixo = nullptr;
        this->linha = -1;
        this->coluna = -1;
        this->valor = 0;
    }
};

// Joyce Kelly e José Luis
Matriz::Matriz(int rows, int cols) {
    this->head = new Node(-1, -1, 0);
    this->rows = rows;
    this->cols = cols;
    // Criando índices para as linhas e colunas
    Node** vheadrows = new Node * [rows];
    Node** vheadcols = new Node * [cols];

    // Instanciando um Node em cada um dos indíces
    for (int i = 0; i < rows; i++) {
        vheadrows[i] = new Node();
    }
    for (int i = 0; i < cols; i++) {
        vheadcols[i] = new Node();
    }

    // ENCADEANDO LINHAS
    for (int i = 0; i < rows; i++) {
        vheadrows[i]->abaixo = vheadrows[i + 1];
        vheadrows[i]->direita = vheadrows[i];
    }

    vheadrows[rows - 1]->direita = vheadrows[rows - 1];
    vheadrows[rows - 1]->abaixo = this->head;

    // ENCADEANDO COLUNAS
    for (int i = 0; i < cols; i++) {
        vheadcols[i]->direita = vheadcols[i + 1];
        vheadcols[i]->abaixo = vheadcols[i];
    }

    vheadcols[cols - 1]->abaixo = vheadcols[cols - 1];
    vheadcols[cols - 1]->direita = this->head;

    // Encadeando linhas e colunas ao head
    head->abaixo = vheadrows[0];
    head->direita = vheadcols[0];
}

// José Luis
Matriz::~Matriz() {
    Node* aux = head;
    Node* temp;

    // Aqui deleta todas as linhas índices
    while (aux->direita != head) {
        temp = aux->direita;
        aux->direita = aux->direita->direita;
        delete temp;
    }

    // Aqui deleta todas as colunas índices
    while (aux->abaixo != head) {
        temp = aux->abaixo;
        aux->abaixo = aux->abaixo->abaixo;
        delete temp;
    }

    delete head;

    cout << "Matriz liberada!" << endl;
}

// José Luis
void Matriz::lerMatriz(string file) {
    ifstream input;
    input.open("matriz.txt");
    string row, col, value, skip;

    // Skipamos os dois primeiros valores do arquivo pois são apenas o tamanho da matriz
    input >> skip >> skip;

    while (!input.eof()) {
        // Pegamos os dados da Matriz do arquivo
        input >> row >> col >> value;

        // Retiramos as virgulas para podermos transformar de string para inteiro
        int index = row.find(',');
        row[index] = '\0';

        index = col.find(',');
        col[index] = '\0';

        // Transforma valores strings em inteiro para inserir
        int linha = stoi(row);
        int coluna = stoi(col);
        double valor = stod(value);
        this->insere(linha, coluna, valor);
    }

}

// Joyce Kelly
void Matriz::imprime() {
    Node* aux;

    // Aqui utilizamos um for para criar a matriz com os valores e os zeros
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            /**
             * Utilizamos a função getPos para verificar se na posição tem algum valor
             * se houver mostramos esse valor, se não mostramos 0
            */
            aux = getPos(i, j);
            if (aux != nullptr) {
                cout << aux->valor;
                // Apenas uma formatação para a Matriz não ficar desorganizada
                if (aux->valor < 0) {
                    cout << " ";
                }
                else if (aux->valor >= 10) {
                    cout << "  ";
                }
                else {
                    cout << "   ";
                }
            }
            else {
                cout << " " << 0 << "   ";
            }
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;
}

// José Luis
Node* Matriz::getPos(int row, int col) {
    Node* aux = this->head;

    // Caminha pelos índices de coluna
    for (int i = 0; i < col; i++) {
        aux = aux->direita;
    }

    /**
     * Se a coluna abaixo tiver um valor -1 na coluna, significa que não é um valor inserido
     * Se não é um valor inserido então é 0
    */
    if (aux->abaixo->coluna == -1) {
        aux = nullptr;
    }
    else {
        aux = aux->abaixo;
        // Enquanto não encontrar uma coluna índice, caminha para baixo até encontrar um elemento com a mesma linha solicitada
        while (aux->coluna != -1) {
            if (aux->linha == row) {
                break;
            }
            aux = aux->abaixo;
        }
    }

    return aux;
}

// José Luis
Node* Matriz::getColuna(int row, int col) {
    Node* aux = this->head;

    // Caminha pelos índices de coluna
    for (int i = 0; i < col; i++) {
        aux = aux->direita;
    }

    if (aux->abaixo->coluna != -1) {
        // Enquanto o debaixo não for uma coluna índice, procura um abaixo que tenha uma linha maior que a solicitada
        while (aux->abaixo->coluna != -1) {
            if (aux->abaixo->linha > row) {
                break;
            }
            aux = aux->abaixo;
        }
    }

    return aux;
}

// Joyce Kelly
Node* Matriz::getLinha(int row, int col) {
    Node* aux = this->head;

    // Caminha pelos índices de linha
    for (int i = 0; i < row; i++) {
        aux = aux->abaixo;
    }


    // Enquanto o da direita não for uma linha índice, procura um a direita que tenha uma coluna maior que a solicitada
    if (aux->direita->linha != -1) {
        while (aux->direita->linha != -1) {
            if (aux->direita->coluna > col) {
                break;
            }
            aux = aux->direita;
        }
    }
    return aux;
}

// José Luis
void Matriz::insere(int row, int col, double v) {
    // verifica se os valores passados são válidos
    if (row > rows || col > cols) {
        throw "Linha ou Coluna inválido!";
    }

    // Cria o novo nó
    Node* new_node = new Node(row, col, v);
    Node* aux;

    /**
     * Pega o elemento na mesma coluna e na linha anterior
     * e reorganiza os encadeamentos
    */
    aux = getColuna(row, col);
    new_node->abaixo = aux->abaixo;
    aux->abaixo = new_node;

    /**
     * Pega o elemento na mesma linha e na coluna anterior
     * e reorganiza os encadeamentos
    */
    aux = getLinha(row, col);
    new_node->direita = aux->direita;
    aux->direita = new_node;
}

// Joyce Kelly
void Matriz::remove(int row, int col) {
    Node* aux; // Utilizado para reorganizar os encadeamentos
    Node* temp; // Utilizado para guardar o elemento que será apagado

    /**
     * Pega o elemento na mesma coluna e na linha anterior
     * e reorganiza os encadeamentos
    */
    aux = getColuna(row - 1, col);
    temp = aux->abaixo;
    aux->abaixo = temp->abaixo;

    /**
     * Pega o elemento na mesma linha e na coluna anterior
     * e reorganiza os encadeamentos
    */
    aux = getLinha(row, col - 1);
    temp = aux->direita;
    aux->direita = temp->direita;

    // Deleta o elemento na posição escolhida
    delete temp;
}

// José Luis
Matriz* Matriz::soma(Matriz* A, Matriz* B) {
    // Verificando se as Matrizes são iguais
    if (A->rows != B->rows || A->cols != B->cols) {
        cout << "Matrizes de tamanhos diferentes!" << endl;
        return nullptr;
    }

    // Cria nova Matriz
    Matriz* m = new Matriz(A->rows, A->cols);
    Node* aux;
    int a, b;
    // Realiza a soma dos elementos das Matrizes
    for (int i = 1; i <= A->rows; i++) {
        for (int j = 1; j <= A->cols; j++) {
            aux = A->getPos(i, j);
            // Utilizando operador ternário para atribuir valor na variável a
            a = (aux != nullptr) ? aux->valor : 0;

            aux = B->getPos(i, j);
            // Utilizando operador ternário para atribuir valor na variável b
            b = (aux != nullptr) ? aux->valor : 0;

            m->insere(i, j, a + b);
        }
    }

    return m;
}

Matriz* Matriz::multiplica(Matriz* A, Matriz* B) {
    // Verificando se as Matrizes são iguais
    if (this->rows != B->cols || this->cols != B->rows) {
        cout << "Matrizes de tamanhos diferentes!" << endl;
        return nullptr;
    }

    // Cria nova Matriz
    Matriz* m = new Matriz(this->rows, this->cols);
    Node* aux;
    Node* aux2;
    int a, b;
    // Realiza a multiplicação dos elementos das Matrizes
    for (int i = 1; i <= this->rows; i++) {
        for (int j = 1; j <= this->cols; j++) {
            aux = this->getPos(i, j);
            // Utilizando operador ternário para atribuir valor na variável a
            a = (aux != nullptr) ? aux->valor : 0;

            // Pegando o valor da próxima coluna
            aux2 = this->getPos(i, j + 1);
            // Multiplica os valores
            a *= (aux2 != nullptr) ? aux2->valor : 0;

            aux = B->getPos(j, i);
            // Utilizando operador ternário para atribuir valor na variável b
            b = (aux != nullptr) ? aux->valor : 0;

            // Pegando o valor da próxima linha
            aux2 = this->getPos(i + 1, j);
            // Multiplica os valores
            b *= (aux2 != nullptr) ? aux2->valor : 0;

            m->insere(i, j, a + b);
        }
    }

    return m;
}
