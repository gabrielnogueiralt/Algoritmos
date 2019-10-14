#include <iostream>
#include <queue>

using namespace std;

struct NodeList {
    int id;
    NodeList *next;
};

class List {
private:
    NodeList *head, *tail;
public:
    List() {
        head = NULL;
        tail = NULL;
    }

    void createNode(int id) {
        NodeList *temp = new NodeList;
        temp->id = id;
        temp->next = NULL;
        if (head == NULL) {
            head = temp;
            tail = temp;
            temp = NULL;
        } else {
            tail->next = temp;
            tail = temp;
        }
    }

    int search(int id, int pos) {
        NodeList *current = head;
        while (current != NULL) {
            if (current->id == id)
                return pos;
            pos++;
            current = current->next;
        }
        return -1;
    }

    void deleteNode(int pos) {
        NodeList *current = new NodeList;
        NodeList *previous = new NodeList;
        current = head;
        for (int i = 0; i < pos; i++) {
            previous = current;
            current = current->next;
        }
        previous->next = current->next;
    }

    int size() {
        int count = 0;
        NodeList *current = head;
        while (current != NULL) {
            count++;
            current = current->next;
        }
        return count;
    }
};

class No {
public :
    int valor;
    No *direito, *esquerdo;
    List *agent;

    No();

    No(int);
};

No::No() {
    this->direito = this->esquerdo = NULL;
    this->agent = new List;
}

No::No(int valor) {
    this->valor = valor;
    this->direito = this->esquerdo = NULL;
    this->agent = new List;
}

class ArvoreBinaria {
protected :
    No *raiz;

    int buscar(No *, int, int);

    int remover(No *, int, int , int);

    int altura(No *);

    int level(No *, int, int);

public:
    ArvoreBinaria();

    int altura();

    int level(int);

    bool vazio();

    int buscar(int, int);

    int insere(int, int , int, int);

    int insereADM(int, int , int, int);

    int remover(int, int , int);

    No *noMaior(No *);

};

No *ArvoreBinaria::noMaior(No *raiz) {
    No *temp = NULL;

    temp = raiz;

    if (temp->direito == NULL) {
        raiz = raiz->esquerdo;
        return temp;
    } else
        return noMaior(raiz->direito);
}

int ArvoreBinaria::level(No *inicio, int valor, int nivel) {
    if (!inicio)
        return -1;
    else {
        if (valor == inicio->valor)
            return nivel;
        else {
            ++nivel;

            if (valor < inicio->valor)
                nivel = level(inicio->esquerdo, valor, nivel);
            else if (valor > inicio->valor)
                nivel = level(inicio->direito, valor, nivel);
        }

        return nivel;
    }
}


int ArvoreBinaria::level(int valor) {
    return level(this->raiz, valor, 0);
}

int ArvoreBinaria::altura(No *inicio) {
    if (!inicio)
        return -1;
    else {
        int alturaesquerda = 0, alturadireita = 0;
        alturaesquerda = altura(inicio->esquerdo);
        alturadireita = altura(inicio->direito);

        if (alturaesquerda < alturadireita)
            return alturadireita + 1;
        else
            return alturaesquerda + 1;
    }
}

int ArvoreBinaria::altura() {
    return altura(this->raiz) + 1;
}

int ArvoreBinaria::buscar(No* inicio, int valor, int id) {
    while (inicio != NULL) {
        if (valor == inicio->valor){
            if (inicio->agent->search(id, 0) != -1) {
                return this->level(this->raiz, valor, 0);
            } else {
                return -1;
            }
        }
        else if (valor < inicio->valor) {
            if (inicio->esquerdo == NULL) {
                return -1;
            } else {
                inicio = inicio->esquerdo;
            }

        } else{
            if (inicio->direito == NULL) {
                return -1;
            } else {
                inicio = inicio->direito;
            }

        }

    }
    return -1;
}

ArvoreBinaria::ArvoreBinaria() {
    this->raiz = NULL;
}

bool ArvoreBinaria::vazio() {
    return this->raiz == NULL;
}

int ArvoreBinaria::insere(int valor, int id, int altura, int base) {
    if(this->altura() <= altura){
        No *tmp = this->raiz;
        No *ant = NULL;

        while (tmp != NULL) {
            ant = tmp;

            if (tmp->valor < valor) {
                tmp = tmp->direito;
            } else if (tmp->valor > valor){
                tmp = tmp->esquerdo;
            } else {
                tmp->agent->createNode(id);
                cout << base << endl;
                return -3;
            }
        }

        if (this->vazio()) {
            if(this->altura() < altura) {
                this->raiz = new No(valor);
                this->raiz->agent->createNode(id);
                cout << base << endl;
                return -3;
            } else {
                return -2;
            }
        } else if (ant->valor < valor) {
            if(this->altura() < altura) {
                ant->direito = new No(valor);
                ant->direito->agent->createNode(id);
                cout << base << endl;
                return -3;
            } else {
                return -2;
            }
        } else {
            if(this->altura() < altura) {
                ant->esquerdo = new No(valor);
                ant->esquerdo->agent->createNode(id);
                cout << base << endl;
                return -3;
            } else {
                return -2;
            }
        }
    }
    return -2;
}

int ArvoreBinaria::insereADM(int valor, int id, int altura, int base) {
    if(this->altura() <= altura){
        No *tmp = this->raiz;
        No *ant = NULL;

        while (tmp != NULL) {
            ant = tmp;

            if (tmp->valor < valor) {
                tmp = tmp->direito;
            } else if (tmp->valor > valor){
                tmp = tmp->esquerdo;
            } else {
                tmp->agent->createNode(id);
                return -3;
            }
        }

        if (this->vazio()) {
            if(this->altura() < altura) {
                this->raiz = new No(valor);
                this->raiz->agent->createNode(id);
                return -3;
            } else {
                return -2;
            }
        } else if (ant->valor < valor) {
            if(this->altura() < altura) {
                ant->direito = new No(valor);
                ant->direito->agent->createNode(id);
                return -3;
            } else {
                return -2;
            }
        } else {
            if(this->altura() < altura) {
                ant->esquerdo = new No(valor);
                ant->esquerdo->agent->createNode(id);
                return -3;
            } else {
                return -2;
            }
        }
    }
    return -2;
}

int ArvoreBinaria::remover(No *raiz, int valor, int id, int base) {
    No *temp = NULL;

    if (raiz == NULL)
        return 1;
    if (valor == raiz->valor) {
        temp = raiz;
        if (raiz->esquerdo == NULL)
            raiz = raiz->direito;
        else if (raiz->direito == NULL)
            raiz = raiz->esquerdo;
        else {
            temp = noMaior(raiz->esquerdo);
            raiz->valor = temp->valor;
        }
        delete temp;
        return 0;
    } else if (valor < raiz->valor)
        return remover(raiz->esquerdo, valor, id, base);
    else
        return remover(raiz->direito, valor, id, base);
}

int ArvoreBinaria::remover(int valor, int id, int base) {
    return remover(this->raiz, valor, id, base);
}

int ArvoreBinaria::buscar(int valor, int id) {
    return buscar(this->raiz, valor, id);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n = 0, h = 0, f = 0, c = 0, id = 0, b = 0, counter = 0,answerADM = 0, answerINF = 0, count = 0, i = 0, j = 0, answerSCH = 0;
    string input = "";
    cin >> n >> h >> f;
    ArvoreBinaria tree[n];
    while (input != "END") {
        cin >> input;
        if (input != "END") {
            cin >> c >> id >> b;
        }
        if (input == "ADM") {
            answerADM = tree[b].insereADM(c, id, h, b);
            if (answerADM != -3) {
                i = (b + 1) % n;
                while (answerADM != 1 && answerADM != -3) {
                    if (answerADM == -2) {
                        answerADM = tree[i].insereADM(c, id, h, i);
                        counter++;
                    }
                    if (counter >= n - 1) {
                        answerADM = 1;
                    }
                    i = (i + 1) % n;
                }
                counter = 0;
            }

        }
        if (input == "INF") {
            answerINF = tree[b].insere(c, id, h, b);
            if (answerINF != -3) {
                i = (b + 1) % n;
                while (answerINF != -4 || answerINF != -3) {
                    if (answerINF == -2) {
                        answerINF = tree[i].insere(c, id, h, i);
                        counter++;
                    } else if (counter >= n - 1) {
                        answerINF = -4;
                    }
                    i++;
                }
            }
        }
        if (input == "EXT") {
            tree[b].remover(c, id, b);
        }
        if (input == "SCH") {
            answerSCH = tree[b].buscar(c, id);
            cout << answerSCH << endl;
        }
    }

    return 0;
}