#include <iostream>

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

class Node {
private:
    int caste;
    List *agent;
    Node *left, *right;
public:
    Node(int caste) {
        this->caste = caste;
        this->agent = new List;
        this->left = NULL;
        this->right = NULL;
    }

    int getCaste() {
        return caste;
    }

    List *getAgent() {
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

    int insert(int caste, int id, int height, int base) {
        if (this->height() <= height) {
            if (root == NULL) {
                root = new Node(caste);
                root->getAgent()->createNode(id);
                cout << base << endl;
                return -3;
            } else
                return insertAux(root, caste, id, base, height);
        } else {
            return -2;
        }
    }

    int insertAux(Node *node, int caste, int id, int base, int height) {
        if (caste < node->getCaste()) {
            if (node->getLeft() == NULL) {
                if (this->height() < height) {
                    Node *newNode = new Node(caste);
                    newNode->getAgent()->createNode(id);
                    node->setLeft(newNode);
                    cout << base << endl;
                    return -3;
                } else {
                    return -2;
                }
            } else
                return insertAux(node->getLeft(), caste, id, base, height);
        } else if (caste > node->getCaste()) {
            if (node->getRight() == NULL) {
                if (this->height() < height) {
                    Node *newNode = new Node(caste);
                    newNode->getAgent()->createNode(id);
                    node->setRight(newNode);
                    cout << base << endl;
                    return -3;
                } else {
                    return -2;
                }

            } else {
                return insertAux(node->getRight(), caste, id, base, height);
            }
        } else {
            node->getAgent()->createNode(id);
            cout << base << endl;
            return -3;
        }

    }

    string insertADM(int caste, int id, int height, int base) {
        if (this->height() <= height) {
            if (root == NULL) {
                root = new Node(caste);
                root->getAgent()->createNode(id);
                return "alocated";
            } else
                return insertAuxADM(root, caste, id, base, height);
        } else {
            return "full";
        }
    }

    string insertAuxADM(Node *node, int caste, int id, int base, int height) {
        if (caste < node->getCaste()) {
            if (node->getLeft() == NULL) {
                if (this->height() < height) {
                    Node *newNode = new Node(caste);
                    newNode->getAgent()->createNode(id);
                    node->setLeft(newNode);
                    return "alocated";
                } else {
                    return "full";
                }

            } else
                return insertAuxADM(node->getLeft(), caste, id, base, height);
        } else if (caste > node->getCaste()) {
            if (node->getRight() == NULL) {
                if (this->height() < height) {
                    Node *newNode = new Node(caste);
                    newNode->getAgent()->createNode(id);
                    node->setRight(newNode);
                    return "alocated";
                } else {
                    return "full";
                }

            } else {
                return insertAuxADM(node->getRight(), caste, id, base, height);
            }
        } else {
            node->getAgent()->createNode(id);
            return "alocated";
        }

    }

    int search(int caste, int id, int base, int j) {
        if (root == NULL) {
            return -1;
        } else if (root->getCaste() == caste) {
            if (root->getAgent()->search(id, 0) != -1) {
                return 1;
            }

        }
        return searchAux(root, caste, id, base, j);
    }

    int searchAux(Node *node, int caste, int id, int base, int j) {
        if (caste < node->getCaste()) {
            if (node->getLeft() == NULL) {
                return -1;
            } else {
                j++;
                return searchAux(node->getLeft(), caste, id, base, j);
            }

        } else if (caste > node->getCaste()) {
            if (node->getRight() == NULL) {
                return -1;
            } else
                j++;
            return searchAux(node->getRight(), caste, id, base, j);
        } else {
            if (node->getAgent()->search(id, 0) != -1) {
                return j;
            }
            return -1;
        }
    }

    int ext(int caste, int id, int base) {
        if (this->search(caste, id, base, 1) != -1) {
            if (root->getCaste() == caste) {
                int pos = root->getAgent()->search(id, 0);
                root->getAgent()->deleteNode(pos);
                if (root->getAgent()->size() == 0) {
                    root = NULL;
                }
                return 1;
            } else {
                return extAux(root, caste, id, base);
            }
        }
        return -1;

    }

    int extAux(Node *node, int caste, int id, int base) {
        if (caste < node->getCaste()) {
            if (node->getLeft() == NULL) {
                return -1;
            } else
                return extAux(node->getLeft(), caste, id, base);
        } else if (caste > node->getCaste()) {
            if (node->getRight() == NULL) {
                return -1;
            } else {
                return extAux(node->getRight(), caste, id, base);
            }
        } else {
            int pos = node->getAgent()->search(id, 0);
            node->getAgent()->deleteNode(pos);
            if (node->getAgent()->size() == 0) {
                this->realocate(caste);
            }
            return 1;
        }
    }

    void realocate(int caste) {
        if(root->getLeft() == NULL){
            int v = root->getCaste()
        }
    }

    void realocateAux(int caste, Node* node){
        if (caste < node->getCaste()) {
            return realocateAux(caste, node->getLeft());
            }
        else if (caste > node->getCaste()) {
            return realocateAux(caste, node->getRight());
        } else {

        }
    }

public:
    int height() {
        return height(this->root);
    }

private:
    int height(Node *node) {
        if (node == NULL)
            return 0;
        else {
            int lDepth = height(node->getLeft());
            int rDepth = height(node->getRight());

            if (lDepth > rDepth)
                return (lDepth + 1);
            else return (rDepth + 1);
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

    int n = 0, h = 0, f = 0, c = 0, id = 0, b = 0, counter = 0, answerINF = 0, count = 0, i = 0, j = 0, answerSCH = 0;
    string adm = "", answerADM = "";
    cin >> n >> h >> f;
    Tree tree[n];
    while (adm != "END") {
        cin >> adm;
        if (adm != "END") {
            cin >> c >> id >> b;
        }
        if (adm == "ADM") {
            answerADM = tree[b].insertADM(c, id, h, b);
            if (answerADM != "alocated") {
                i = b + 1;
                while (answerADM != "allFull" || answerADM != "alocated") {
                    if (answerADM == "full") {
                        answerADM = tree[i].insertADM(c, id, h, i);
                        counter++;
                    } else if (counter >= n - 1) {
                        answerADM = "allFull";
                    }
                    i++;
                }
            }

        }
        if (adm == "INF") {
            answerINF = tree[b].insert(c, id, h, b);
            if (answerINF != -3) {
                i = b + 1;
                while (answerINF != -4 || answerINF != -3) {
                    if (answerINF == -2) {
                        answerINF = tree[i].insert(c, id, h, i);
                        counter++;
                    } else if (counter >= n - 1) {
                        answerINF = -4;
                    }
                    i++;
                }
            }
        }
        if (adm == "EXT") {
            tree[b].ext(c, id, b);
        }
        if (adm == "SCH") {
            answerSCH = tree[b].search(c, id, b, j);
            cout << answerSCH << endl;
        }
    }

    return 0;
}