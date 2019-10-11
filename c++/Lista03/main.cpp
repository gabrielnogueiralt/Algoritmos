#include <iostream>

using namespace std;

template<class T>
class vector {
private:
    T *vet;
    int logic;
    int Rsize;

    bool full();

    void change();

public:
    vector();

    ~vector();

    bool empty();

    void push_back(T val);

    void pop_back();

    int size();

    T &operator[](int index);
};

template<class T>
bool vector<T>::full() {
    return (this->logic == this->Rsize);
}

template<class T>
void vector<T>::change() {
    int newSize = this->Rsize << 1;
    newSize++;

    T *aux = new T[newSize];

    for (int i = 0; i < this->logic; i++) aux[i] = this->vet[i];


    delete[] this->vet;

    this->vet = aux;
    this->Rsize = newSize;
}

template<class T>
vector<T>::vector() {
    this->vet = nullptr;
    this->logic = 0;
    this->Rsize = 0;
}

template<class T>
vector<T>::~vector() {
    delete[] this->vet;
    this->logic = 0;
    this->Rsize = 0;
}

template<class T>
bool vector<T>::empty() {
    return (this->logic == 0);
}

template<class T>
void vector<T>::push_back(T val) {
    if (this->full()) {
        this->change();
    }

    this->vet[this->logic] = val;
    this->logic++;
}

template<class T>
void vector<T>::pop_back() {
    this->logic--;
}

template<class T>
int vector<T>::size() {
    return (this->logic);
}

template<class T>
T &vector<T>::operator[](int index) {
    return this->vet[index];
}

class Node {
private:
    int caste;
    vector<int> agent;
    Node *left, *right;
public:
    Node(int caste) {
        this->caste = caste;
        this->agent = agent;
        this->left = NULL;
        this->right = NULL;
    }

    int getCaste() {
        return caste;
    }

    vector<int> getAgent() {
        return agent;
    }

    Node *getLeft() {
        return left;
    }

    Node *getRight() {
        return right;
    }

    void setLeft(Node *node) {
        left = node;
    }

    void setRight(Node *node) {
        right = node;
    }

};

class Tree {
private:
    Node *root;
public:
    Tree() {
        root = NULL;
    }

    void insert(int caste) {
        if (root == NULL)
            root = new Node(caste);
        else
            insertAux(root, caste);
    }

    void insertAux(Node *node, int caste) {
        if (caste < node->getCaste()) {
            if (node->getLeft() == NULL) {
                Node *newNode = new Node(caste);
                node->setLeft(newNode);
            } else {
                insertAux(node->getLeft(), caste);
            }
        } else if (caste > node->getCaste()) {
            if (node->getRight() == NULL) {
                Node *newNode = new Node(caste);
                node->setRight(newNode);
            } else {
                insertAux(node->getRight(), caste);
            }
        }

    }
public:
    int height(){
        return height(this->root);
    }
private:
    int height(Node *node) {
        if (node == NULL) {
            return 0;
        } else {
            int heightLeft = 0, heightRight = 0;
            heightLeft = height(node->getLeft());
            heightLeft++;
            heightRight = height(node->getRight());
            heightRight++;

            if (heightLeft > heightRight)
                return heightLeft;
            else
                return heightRight;

        }
    }

    Node *getRoot() {
        return root;
    }

//    void inOrder(Node* node){
//        if(node != NULL){
//            inOrder(node->getLeft());
//            cout << node->getCaste() << " ";
//            inOrder(node->getRight());
//        }
//    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, h, f, c, id, b;
    string adm;
    cin >> n >> h >> f;
    while(adm != "END"){
        cin >> adm;
        if(adm != "END") {
            cin >> c >> id >> b;
        }
    }

    return 0;
}