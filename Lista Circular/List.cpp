// José Luis dos Santos Araujo - 472435
// Joyce Kelly Chaves Barros da Silva - 472032
#include <iostream>
#include <sstream>
#include "List.h"

using namespace std;

struct Node {
    int value;
    Node* next;
    Node* prev;
};
// José Luis
List::List() {
    // Definindo head e tail
    head = new Node;
    tail = new Node;

    head->value = -77777777;
    head->next = tail;
    head->prev = tail;

    tail->value = -77777777;
    tail->next = head;
    tail->prev = head;
}

// Joyce Kelly
List::~List() {
    // Limpando a lista e liberando head e tail
    clear();
    delete head;
    delete tail;
    cout << "lista liberada" << endl;
}

// José Luis
Node* List::search(int key) {
    // Verificamos se a lista está vazia
    if (empty()) {
        return nullptr;
    }

    Node* aux = head;

    // Procuramos qual elemento tem o mesmo valor que a key passada
    while (aux->next != tail) {
        if (aux->next->value == key) {
            return aux;
        }
        aux = aux->next;
    }

    return nullptr;
}

// José Luis
void List::push_back(int key) {
    // Criamos o novo nó e definimos seus valores
    Node* new_node = new Node();
    new_node->value = key;

    // Liga novo nó ao tail
    new_node->next = tail;
    new_node->prev = tail->prev;

    // Liga o novo nó ao anterior ao tail
    tail->prev->next = new_node;
    tail->prev = new_node;
}

// Joyce Kelly
int List::pop_back() {
    // Verifica se a lista está vazia
    if (empty()) {
        cout << "Lista vazia ";
        return 0;
    }
    // Pegamos o primeiro elemento antes do tail
    Node* aux = tail->prev;

    // Reorganizamos os relacionamentos
    tail->prev = aux->prev;
    aux->prev->next = tail;

    // Pegamos o valor para retornar
    int i = aux->value;

    // Deleta o elemento
    delete aux;

    return i;
}

// José Luis
void List::insertAfter(int key, int k) {
    Node* aux = head;
    int count = 0;

    // definimos um novo nó
    Node* new_node = new Node();
    new_node->value = key;

    // Percorremos até o local escolhido
    while (count < k) {
        aux = aux->next;
        count++;
    }

    // Reorganizamos os relacionamentos e inserimos o novo nó no local
    new_node->prev = aux;
    new_node->next = aux->next;

    aux->next->prev = new_node;
    aux->next = new_node;
}

// Joyce Kelly
void List::remove(int key) {
    // Verifica se a lista está vazia
    if (empty()) {
        cout << "Lista vazia";
    }

    // Recebemos o elemento com o valor especificado
    Node* aux = search(key);
    Node* temp;
    // Se não for nulo reorganizamos os relacionamentos
    if (aux != nullptr) {
        temp = aux->next;
        aux->next = aux->next->next;
        aux->next->prev = aux;
        delete temp;
    }
}

// José Luis
void List::removeAll(int key) {
    // Verifica se a lista é vazia
    if (empty()) {
        cout << "Lista vazia";
    }

    Node* aux = head->next;
    Node* temp;

    // Percorre a lista e remove todas as ocorrencias do valor
    while (aux != tail) {
        temp = aux;
        aux = aux->next;
        if (temp->value == key) {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;

            delete temp;
        }
    }
}

// Joyce Kelly
void List::print() {
    // Verifica se a lista está vazia
    if (empty()) {
        cout << "Lista vazia" << endl;
        return;
    }

    // Cria uma stringstream para mostrar os valores no final
    stringstream ss;

    ss << "[";

    Node* aux = head->next;

    // Percorre a lista enquanto o auxiliar não for o tail 
    while (aux != tail) {
        // Armazena o valor na stringstream
        ss << aux->value;
        // se o próximo não for o tail, adiciona uma virgula
        if (aux->next != tail) {
            ss << ",";
        }
        // passa para o próximo elemento
        aux = aux->next;
    }

    ss << "]";

    cout << ss.str() << endl;;
}

// José Luis
void List::printReverse() {
    if (empty()) {
        cout << "Lista vazia" << endl;
        return;
    }

    // Cria uma stringstream para mostrar os valores no final
    stringstream ss;

    ss << "[";

    Node* aux = tail->prev;

    // Percorre a lista enquanto o auxiliar não for o tail 
    while (aux != head) {
        ss << aux->value;
        // se o próximo não for o head, adiciona uma virgula
        if (aux->prev != head) {
            ss << ",";
        }
        // passa para o elemento anterior
        aux = aux->prev;
    }

    ss << "]";

    cout << ss.str() << endl;;
}

// José Luis
bool List::empty() {
    // Se o head aponta pro next, significa que não há nenhum nó na Lista
    if (head->next == tail) {
        return true;
    }

    return false;
}

// Joyce Kelly
int List::size() {
    Node* aux = head;
    int count = 0;

    // Percorre a Lista utilizando uma variável contadora
    while (aux->next != tail) {
        count++;
        aux = aux->next;
    }

    return count;
}

// José Luis
void List::clear() {
    Node* aux = head;
    Node* temp;
    // Percorremos enquanto o próximo do aux(head) não é o tail
    while (aux->next != tail) {
        // Reorganiza os relacionamentos para apagar o próximo do aux(head)
        temp = aux->next;
        aux->next = aux->next->next;
        delete temp;
    }

    // Reorganiza o head e o tail
    head->next = tail;
    tail->prev = head;
}

// Joyce Kelly
void List::concat(List* lst) {
    /**
     * Se a lista passada não for vazia
     * reorganiza os heads e tails de ambas as listas
     * para concatenar o inicio de uma ao final da outra
    */
    if (!lst->empty()) {
        this->tail->prev->next = lst->head->next;
        lst->head->next->prev = this->tail->prev;

        this->tail->prev = lst->tail->prev;
        lst->tail->prev->next = this->tail;
        lst->head->next = lst->tail;
    }
}

// Joyce Kelly
List* List::copy() {
    // Cria nova lista
    List* lst = new List();

    // Verifica se a lista está vazia
    if (this->empty()) {
        return lst;
    }

    Node* aux = this->head->next;

    // Percorre a lista adicionando cada valor ao final da nova lista
    while (aux != tail) {
        lst->push_back(aux->value);

        aux = aux->next;
    }

    return lst;
}

// José Luis
void List::copyArray(int n, int arr[]) {
    // Percorre o array inserindo os valores no final da lista
    for (int i = 0; i < n; i++) {
        this->push_back(arr[i]);
    }
}

// José Luis
bool List::equal(List* lst) {
    // Verifica se ambas tem o mesmo tamanho
    if (lst->size() != this->size()) {
        return false;
    }

    Node* aux1 = this->head->next;
    Node* aux2 = lst->head->next;

    // Percorre uma das listas e se encontrar uma divergencia retorna falso
    while (aux1 != tail) {
        if (aux1->value != aux2->value) {
            return false;
        }
        aux1 = aux1->next;
        aux2 = aux2->next;
    }

    return true;
}