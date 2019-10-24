#include <iostream>

using namespace std;

const int END = -1;

struct NodeList {
    int id;
    NodeList *next;

    NodeList () {
        this->next = nullptr;
    }

    NodeList (int id) {
        this->id = id;
        this->next = nullptr;
    }

    ~NodeList () {
        this->next = nullptr;
    }
};

class List {
    NodeList *head;
    void insert (NodeList * prev, int v) {
        NodeList * novo = new NodeList (v);
        novo->next = prev->next;
        prev->next = novo;
    }
    NodeList * find (NodeList * head, int v) {
        NodeList * cur = head;
        while (cur->next != nullptr && cur->next->id != v) {
            cur = cur->next;
        }
        return cur;
    }
public:
    List() {
        head = new NodeList ();
    }

    void createNode(int id) {
        insert (this->head, id);
    }

    int search(int id, int pos) {
        if ((find (head, id))->next != nullptr) {
            return 1;
        } else {
            return -1;
        }
    }

    void deleteNode(int v) {
        NodeList *prev = find (this->head, v);
        if (prev->next != nullptr) {
            NodeList * tchau = prev->next;
            prev->next = tchau->next;
            delete tchau;
        }
    }

    bool empty() {
        return (this->head->next == nullptr);
    }

    ~List() {
        delete head;
    }
};

struct Node {
    int caste;
    List *agent;
    Node *left, *right;

    Node(int caste, int id) {
        this->caste = caste;
        this->agent = new List();
        this->agent->createNode(id);
        this->left = nullptr;
        this->right = nullptr;
    }

    ~Node () {
        this->left = nullptr;
        this->right = nullptr;
    }

};

struct Tree {
    
    Node *root;
    
    Tree() {
        root = NULL;
    }

    pair <Node *, bool> insert (Node * root, int id, int caste, int h) {
        if (h == 0) {
            return make_pair(root, false);
        } else if (root == nullptr) {
            return make_pair (new Node (caste, id), true);
        } else if (caste < root->caste) {
            bool ret;
            tie (root->left, ret) = insert (root->left, id, caste, h - 1);
            return make_pair(root, ret);
        } else if (caste > root->caste) {
            bool ret;
            tie (root->right, ret) = insert (root->right, id, caste, h - 1);
            return make_pair (root, ret);
        } else {
            root->agent->createNode(id);
            return make_pair (root, true);
        }
    }

    int search (Node * root, int caste, int id, int h) {
        if (root == nullptr) {
            return -1;
        } else if (caste < root->caste){
            return search(root->left, caste, id, h+1);
        } else if(caste > root->caste){
            return search(root->right, caste, id, h+1);
        } else {
            if(root->agent->search(id) == 1){
                return h;
            } else {
                return -1;
            }  
        }
    }

    Node * ext (Node * root, int caste, int id) {
        if(root == nullptr){
            return root;
        } else if(caste < root->caste){
            root->left = ext(root->left, caste, id);
            return root;
        } else if(caste > root->caste){
            root->right = ext(root->right, caste, id);;
            return root;
        } else {
            root->agent->deleteNode(id);
            if (!root->agent->empty()) root;  
            if(root->left == nullptr && root->right == nullptr) {
                delete root;
                return nullptr;
            } else if(root->left == nullptr){
                Node * r = root->right;
                delete root;
                return r;
            } else if(root->right == nullptr){
                Node * l = root->left;
                delete root;
                return l;
            } else {
                Node * hijacked;
                tie (root->right, hijacked) = dispose (root->right);
                root->caste = hijacked->caste;
                delete root->agent;
                root->agent = hijacked->agent;
                delete hijacked;
            }
        }
    }

    pair <Node*, Node*> dispose (Node * root) {
        if (root->left == nullptr) {
            return make_pair (root->right, root);
        } else {
            Node * tchau;
            tie (root->left, tchau) = dispose (root->left);
            return make_pair (root, tchau);
        }
    } 

};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n = 0, h = 0, f = 0, c = 0, id = 0, b = 0, counter = 0, answerINF = 0, count = 0, i = 0, j = 0, answerSCH = 0;
    string adm = "", answerADM = "";
    cin >> n >> h >> f;
    Tree tree[n];
    while (input != "END") {
        cin >> input;
        if (input != "END") {
            cin >> c >> id >> b;
        }
        if (input == "ADM") {
            bool inseriu, cheio = false;
            tie (tree[b].root, inseriu) = tree[b].insert(tree[b].root, id, c, h);
            if (!inseriu) {
                i = b + 1;
                while (cheio || !inseriu) {
                    if (!inseriu) {
                        tie (tree[b].root, inseriu) = tree[i].insert(tree[b].root, id, c, h);
                        counter++;
                    } else if (counter >= n - 1) {
                        cheio = true;
                    }
                    i++;
                }
            }

        }
        if (input == "INF") {
            bool inseriu, cheio = false;
            tie (tree[b].root, inseriu) = tree[b].insert(tree[b].root, id, c, h);
            if (!inseriu) {
                i = b + 1;
                while (cheio || !inseriu) {
                    if (!inseriu) {
                        tie (tree[b].root, inseriu) = tree[i].insert(tree[b].root, id, c, h);
                        counter++;
                    } else if (counter >= n - 1) {
                        cheio = true;
                    }
                    if(inseriu){
                        cout << i << endl;
                    }
                    i++;
                }
            }
        }
        if (input == "EXT") {
            tree[b].ext(tree[b].root,c, id);
        }
        if (input == "SCH") {
            answerSCH = tree[b].search(tree[b].root, c, id, 1);
            cout << answerSCH << endl;
        }
    }

    return 0;
}