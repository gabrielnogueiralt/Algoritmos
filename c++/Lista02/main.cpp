#include <bits/stdc++.h>

using namespace std;

struct No {
    int chave;
    string valor;

    No(int chave, string valor) {
        this->chave = chave;
        this->valor = valor;
    }
};

class Estacionamento1 {
    No **vetor;
    int fMin, fMax, mMin, m, vagasOcupadas, nivelOcupacao;

public:
    Estacionamento1(int fMin, int fMax, int mMin) {
        this->fMin = fMin;
        this->fMax = fMax;
        this->mMin = mMin;
        this->m = mMin;
        this->vagasOcupadas = 0;
        this->nivelOcupacao = 0;
        vetor = new No * [m];

        for (int i = 0; i < m; i++) {
            vetor[i] = NULL;
        }
    }

    pair<int, int> inserir(int chave, string valor) {

        if (100 * nivelOcupacao > m * fMax) {
            int novoM = m * 2;
            funcRehashing(novoM);
            m *= 2;
            return auxInserir(chave, valor);
        }
        else {
            return auxInserir(chave, valor);
        }
    }

    pair<int,int> auxInserir(int chave, string valor) {
        pair<int,int> p;

        p.first = hash(chave, m);
        p.second = 0;

        while (vetor[p.first] != NULL) {
            p.second++;
            p.first = hash(chave + p.second, m);
        }

        vetor[p.first] = new No(chave, valor);

        nivelOcupacao++; vagasOcupadas++;
        return p;
    }

    int hash(int chave, int k) {
        return (chave % k);
    }

    pair<int, int> procurar(int chave) {
        bool encontrou = false;
        pair<int,int> p;

        p.first = hash(chave, m);
        p.second = 0;

        while (!encontrou && vetor[p.first] != NULL) {
            if (vetor[p.first]->chave == chave) {
                if (vetor[p.first]->chave > 0) {
                    return p;
                } else {
                    encontrou = true;
                }
            } else {
                p.second++;
                p.first = hash(chave + p.second, m);
            }
        }

        p.first = -1; p.second = -1;

        return p;
    }

    pair<int, int> remover(int chave) {
        pair<int,int> p;

        p = procurar(chave);

        if (p.first >= 0) {
            vetor[p.first]->chave = -1;
            vagasOcupadas--;
            if (m / 2 >= mMin && 100 * vagasOcupadas < m * fMin) {
                int novoM;
                novoM = m / 2;
                funcRehashing(novoM);
                m = m / 2;
            }
        }

        return p;
    }

    void funcRehashing(int novoM) {
        nivelOcupacao = 0; vagasOcupadas = 0;

        No **vetorAux = new No * [novoM];

        for (int i = 0; i < m; i++) {
            if (vetor[i] != NULL) {
                if (vetor[i]->chave != -1){
                    int pos;
                    pos = hash(vetor[i]->chave, novoM);

                    while (vetorAux[pos] != NULL) {
                        pos++;
                        pos = hash(pos, novoM);
                    }
                    
                    vetorAux[pos] = vetor[i];
                    nivelOcupacao++; vagasOcupadas++;
                }
            }

        }
        vetor = vetorAux;
    }

};

class Estacinamento2 {
private:
    No **vetor;
    int fMin, fMax, mMin, m, vagasOcupadas, nivelOcupacao;

public:
    Estacinamento2(int fMin, int fMax, int mMin) {
        this->fMin = fMin;
        this->fMax = fMax;
        this->mMin = mMin;
        this->m = mMin;
        this->nivelOcupacao = 0;
        this->vagasOcupadas = 0;
        vetor = new No *[m];

        for (int i = 0; i < m; i++) {
            vetor[i] = NULL;
        }
    }

    pair<int, int> inserir(int chave, string valor) {
        if (100 * nivelOcupacao > m * fMax) {
            int novoM = m * 2;
            funcRehashing(novoM);
            m *= 2;
            return auxInserir(chave, valor);
        } else {
            return auxInserir(chave, valor);
        }
    }

    pair<int, int> auxInserir(int chave, string valor) {
        bool primeiro = true;
        pair<int, int> p, aux;

        p.first = hash(chave, m);
        p.second = 0;

        while (vetor[p.first] != NULL) {
            int distancia;
            distancia = hash(p.first - ((vetor[p.first]->chave) % m),m);
            if (vetor[p.first]->chave == -1 || distancia >= p.second) {
                p.second++;
                p.first = hash(chave + (p.second), m);
            } else {
                No *no = new No(vetor[p.first]->chave,vetor[p.first]->valor);

                vetor[p.first]->chave = chave;
                vetor[p.first]->valor = valor;

                chave = no->chave;
                valor = no->valor;

                if (primeiro == true) {
                    primeiro = false;
                    aux.first = p.first;
                    aux.second = p.second;

                    distancia++;

                    p.second = distancia;
                    p.first = hash(chave + p.second, m);

                } else {
                    distancia++;

                    p.second = distancia;
                    p.first = hash(chave + p.second, m);
                }
            }
        }
        nivelOcupacao++; vagasOcupadas++;
        vetor[p.first] = new No(chave, valor);

        if (primeiro) {
            return p;
        } else {
            return aux;
        }
    }

    int hash(int chave, int k) {

        if (chave >= 0) {
            return (chave % k);
        } else {
            return (chave + k) % k;
        }
    }

    pair<int, int> procurar(int chave) {
        bool encontrou = false;
        pair<int, int> p;

        p.first = hash(chave, m);
        p.second = 0;

        while (!encontrou && vetor[p.first] != NULL) {
            if (vetor[p.first]->chave == chave) {
                if (vetor[p.first]->chave > 0) {
                    return p;
                } else {
                    encontrou = true;
                }
            } else {
                int distancia;
                distancia = hash(p.first - ((vetor[p.first]->chave) % m), m);
                p.second++;
                p.first = hash(chave + p.second, m);

            }
        }

        p.first = -1; p.second = -1;

        return p;
    }

    pair<int, int> remover(int chave) {
        pair<int,int> p;

        p = procurar(chave);

        if (p.first >= 0) {
            vagasOcupadas--;
            vetor[p.first]->chave = -1;

            if (m / 2 >= mMin && 100 * vagasOcupadas < m * fMin ) {
                int novoM = m / 2;
                funcRehashing(novoM);
                m = m / 2;
            }
        }

        return p;
    }

    void funcRehashing(int novoM) {
        nivelOcupacao = 0; vagasOcupadas = 0;
        No **vetorAux = new No *[novoM];

        for (int i = 0; i < m; i++) {
            if (vetor[i] != NULL){
                if(vetor[i]->chave != -1){
                    int pos, d = 0;
                    pos = hash(vetor[i]->chave, novoM);

                    while (vetorAux[pos] != NULL ) {
                        int distancia;
                        distancia = hash((pos - hash(vetorAux[pos]->chave, novoM)), novoM);
                        if (d <= distancia) {
                            d++;
                            pos = hash(vetor[i]->chave + d, novoM);
                        } else {
                            d = distancia + 1;
                            No *no = new No(vetorAux[pos]->chave, vetorAux[pos]->valor);
                            vetorAux[pos] = vetor[i];
                            vetor[i] = no;
                            pos = hash(vetor[i]->chave + d, novoM);
                        }
                    }
                    vetorAux[pos] = vetor[i];
                    nivelOcupacao++; vagasOcupadas++;
                }
            }

        }
        vetor = vetorAux;
    }
};

int enderecador(string placa, int pot[]){
    int p = 0;
    int chave = 0;
    for(int i = 0;i < placa.size(); i++){
        p= (int) (placa[i] - 65);
        chave += p * pot[i];
    }
    return chave;
}

int main() {
    int pot [6] = {1, 26, 676, 17576, 456976, 11881376};
    int fMin, fMax, mMin, cont1 = 0, cont2 = 0, contador = 0, vsf = 1;
    cin >> mMin >> fMin >> fMax;

    Estacionamento1 *e1 = new Estacionamento1(fMin, fMax, mMin);
    Estacinamento2 *e2 = new Estacinamento2(fMin, fMax, mMin);

    string comando, placa;
    cin >> comando;

    while (comando != "END") {
        cin >> placa;
        contador++;
        if (comando == "IN") {
            int chave = enderecador(placa, pot);

            pair<int, int> r1 = e1->inserir(chave, placa);
            pair<int, int> r2 = e2->inserir(chave, placa);

            cout << r1.first << " " << r1.second << " " << r2.first << " " << r2.second << endl;
            if(vsf == 39){
                vsf = 39;
            }
            cin >> comando;
        } else if (comando == "OUT") {
            int chave = enderecador(placa, pot);

            pair<int,int> r1 = e1->remover(chave);
            pair<int, int> r2 = e2->remover(chave);

            cout << r1.first << " " << r1.second << " " << r2.first << " " << r2.second << endl;

            cin >> comando;
        }
        else if (comando == "SCH"){
            int chave = enderecador(placa, pot);

            pair<int,int> r1 = e1->procurar(chave);
            pair<int, int> r2 = e2->procurar(chave);

            cout << r1.first << " " << r1.second << " " << r2.first << " " << r2.second << endl;

            cin >> comando;

            if (r1.second > cont1) {
                cont1 = r1.second;
            }
            if (r2.second > cont2) {
                cont2 = r2.second;
            }
        }
    }

    cout << cont1 << " " << cont2 << endl;

    return 0;

}

