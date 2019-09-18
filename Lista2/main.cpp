#include <iostream>
#include <cmath>

using namespace std;

int maximo (int a, int b){
    if(a > b){
        return a;
    }else
        return b;
}

int calcularChave(string placa){
    int *p = new int[6];
    int chave = 0;
    for(int i = 0;i < placa.size(); i++){
        p[i] = (int) (placa[i] - 65);
        chave += p[i] * (pow(26,i));
    }
    return chave;
}

class HashTable {
private:
    int mVagas, vagasOcup, vagasEfet;
    int *vagas;
public:
     HashTable(int mVagas){
        this->mVagas = mVagas;
        this->vagasOcup = vagasOcup;
        this->vagas = new int[mVagas];
        this->vagasEfet = vagasOcup;
    }

     void in(int chave, int fMax){
        int j = 0;
        if(100 * this->vagasOcup > fMax * this->mVagas){
            int *aux = this->vagas;
            this->mVagas *= 2;
            //this->tamanho = tamanho / 2;
            this->vagas = new int[this->mVagas];
            for(int i = 0; i < mVagas; i++){
                if(aux[i] != -1){
                    int y = 0;
                    if(this->vagas[aux[i] % this->mVagas] != 0){
                        bool cond = true;
                        while(cond){
                            if(this->vagas[(aux[i]+y)% this->mVagas] != 0){
                                y++;
                            } else {
                                cond = false;
                            }
                        }
                    }
                    this->vagas[(aux[i] + y) % this->mVagas] = aux[i];
                }
            }
        }
        if (this->vagas[chave % this->mVagas] != 0) {
            bool cond = true;
            while (cond) {
                if (this->vagas[(chave + j) % this->mVagas] != 0) {
                    j++;
                } else {
                    cond = false;
                }
            }
        }
        this->vagasOcup++;
        this->vagas[(chave + j) % this->mVagas] = chave;
        this->vagasEfet++;

        cout << ((chave + j) % this->mVagas) << endl;
        cout << " " << j << " " << endl;
    }

    void out(int chave, int fMin, int mMin) {
        this->procurar(chave, true, 0);
        if (this->mVagas >= mMin && 100 * this->vagasEfet < this->mVagas * fMin) {
            this->mVagas = maximo((this->mVagas / 2), mMin);
            int *aux = this->vagas;
            this->vagas = new int[this->mVagas];
            //this.tamanho = tamanho / 2;
            for (int i = 0; i < mVagas; i++) {
                if (aux[i] != 0 && aux[i] != -1) {
                    int y = 0;
                    if (this->vagas[aux[i] % this->mVagas] != 0) {
                        bool cond = true;
                        while (cond) {
                            if (this->vagas[(aux[i] + y) % this->mVagas] != 0) {
                                y++;
                            } else {
                                cond = false;
                            }
                        }
                    }
                    this->vagas[(aux[i] + y) % this->mVagas] = aux[i];
                }
            }
            this->vagasEfet = this->vagasOcup;
        }
    }

    int procurar(int chave, bool out, int dMax){
        int i = 0;
        if (this->vagas[chave % this->mVagas] == chave) {
            cout << (chave % this->mVagas + " 0 ");
            if (out == true) {
                this->vagas[chave % this->mVagas] = -1;
                this->vagasEfet--;
            }
        } else if (this->vagas[chave % this->mVagas] == 0) {
            cout << ("-1 -1 ");
        } else {
            bool cond = true;
            i = 1;
            while (cond) {
                if (this->vagas[(chave + i) % this->mVagas] != 0 && this->vagas[(chave + i) % this->mVagas] != chave) {
                    i++;
                } else if (this->vagas[(chave + i) % this->mVagas] != 0 && this->vagas[(chave + i) % this->mVagas] == chave) {
                    cond = false;
                    cout << ((chave + i) % this->mVagas) << endl;
                    cout << " " << i << " ";
                    if (out == true) {
                        this->vagas[chave % this->mVagas] = -1;
                        this->vagasEfet--;
                    }
                    if (i > dMax) {
                        dMax = i;
                    }
                } else {
                    cond = false;
                    cout << ("-1 -1 ");
                }
            }
        }
        return dMax;
    }
};

class E2{
private:
    int mVagas, vagasOcup, vagasEfet;
    int *vagas;
    int *dist;

public:
    E2(int mVagas){
        this->mVagas = mVagas;
        this->vagasOcup = 0;
        this->vagas = new int[mVagas];
        this->dist = new int[mVagas];
        this->vagasEfet = vagasOcup;
    }

    void in(int chave, int fMax, int j, bool g) {
        bool temp = false;
        if (100 * this->vagasOcup > fMax * this->mVagas && g == false) {
            int *aux = this->vagas;
            int *aux2 = this->dist;
            this->mVagas *= 2;
            //this-> tamanho = tamanho * 2;
            this->vagas = new int[this->mVagas];
            this->dist = new int[this->mVagas];
            this->vagasOcup = this->vagasEfet;
            for (int i = 0; i < mVagas; i++) {
                if (aux[i] != -1 && aux[i] != 0) {
                    int y = 0;
                    if (this->vagas[aux[i] % this->mVagas] != 0) {
                        bool cond = true;
                        y = 1;
                        while (cond) {
                            if (this->vagas[(aux[i] + y) % this->mVagas] != 0 && this->vagas[(aux[i] + y) % this->mVagas] != -1) {
                                if (y <= this->dist[(aux[i] + y) % this->mVagas]) {
                                    y++;
                                } else {
                                    int auxChave = this->vagas[(aux[i] + y) % this->mVagas];
                                    int distancia = this->dist[(aux[i] + y) % this->mVagas];
                                    this->vagas[(aux[i] + y) % this->mVagas] = aux[i];
                                    this->dist[(aux[i] + y) % this->mVagas] = y;
                                    this->in(auxChave, fMax, (distancia + 1) % this->mVagas, true);
                                    cond = false;
                                }
                            } else if (this->vagas[(aux[i] + y) % this->mVagas] == -1) {
                                y++;
                            } else {
                                cond = false;
                            }
                        }
                    }
                    this->vagas[(aux[i] + y) % this->mVagas] = aux[i];
                    this->dist[(aux2[i] + y) % this->mVagas] = y;
                }
            }
        }
        if (j == -5) {
            temp = true;
            j = 0;
            this->vagasOcup++;
        }
        if (this->vagas[(chave + j) % this->mVagas] != 0) {
            bool cond = true;
            while (cond) {
                if (this->vagas[(chave + j) % this->mVagas] != 0 && this->vagas[(chave + j) % this->mVagas] != -1) {
                    if (j <= this->dist[(chave + j) % this->mVagas]) {
                        j++;
                    } else {
                        int aux = this->vagas[(chave + j) % this->mVagas];
                        int distancia = this->dist[(chave + j) % this->mVagas];
                        this->vagas[(chave + j) % this->mVagas] = chave;
                        this->dist[(chave + j) % this->mVagas] = j;
                        this->in(aux, fMax, distancia % this->mVagas, true);
                        cond = false;
                    }
                } else if (this->vagas[(chave + j) % this->mVagas] == -1) {
                    j++;
                } else {
                    this->vagas[(chave + j) % this->mVagas] = chave;
                    this->dist[(chave + j) % this->mVagas] = j;
                    cond = false;
                }
            }
        } else {
            this->vagas[(chave + j) % this->mVagas] = chave;
            this->dist[(chave + j) % this->mVagas] = j;
        }
        if (temp) {
            cout << ((chave + j) % this->mVagas);
            cout << " " << j << endl;
            this->vagasEfet++;
        }
    }

    void out(int chave, int fMin, int mMin, int fMax) {
        this->procurar(chave, true, 0);
        if (this->mVagas > mMin && 100 * this->vagasEfet < this->mVagas * fMin) {
            this->mVagas = this->mVagas / 2;
            //this->tamanho = tamanho / 2;
            int *aux = this->vagas;
            int *aux2 = this->dist;
            this->vagas = new int[this->mVagas];
            this->dist = new int[this->mVagas];
            for (int i = 0; i < mVagas; i++) {
                if (aux[i] != 0 && aux[i] != -1) {
                    int y = 0;
                    if (this->vagas[aux[i] % this->mVagas] != 0) {
                        bool cond = true;
                        y = 1;
                        while (cond) {
                            if (this->vagas[(aux[i] + y) % this->mVagas] != 0 && this->vagas[(aux[i] + y) % this->mVagas] != -1) {
                                if (y <= this->dist[(aux[i] + y) % this->mVagas]) {
                                    y++;
                                } else {
                                    int auxChave = this->vagas[(aux[i] + y) % this->mVagas];
                                    int distancia = this->dist[(aux[i] + y) % this->mVagas];
                                    this->vagas[(aux[i] + y) % this->mVagas] = aux[i];
                                    this->dist[(aux[i] + y) % this->mVagas] = y;
                                    this->in(auxChave, fMax, distancia % this->mVagas, true);
                                    cond = false;
                                }
                            } else if (this->vagas[(aux[i] + y) % this->mVagas] == -1) {
                                y++;
                            } else {
                                cond = false;
                            }
                        }
                    }
                    this->vagas[(aux[i] + y) % this->mVagas] = aux[i];
                    this->dist[(aux2[i] + y) % this->mVagas] = y;
                }
            }
            this->vagasOcup = this->vagasEfet;
        }
    }

    int procurar(int chave, bool out, int dMax) {
        int i = 0;
        if (this->vagas[chave % this->mVagas] == chave) {
            cout << (chave % this->mVagas + " 0") << endl;
            if (out == true) {
                this->vagas[chave % this->mVagas] = -1;
                this->vagasEfet--;
            }
        } else if (this->vagas[chave % this->mVagas] == 0) {
            cout << ("-1 -1") << endl;
        } else {
            bool cond = true;
            i = 1;
            while (cond) {
                if (this->vagas[(chave + i) % this->mVagas] == -1) {
                    i++;
                } else if (this->vagas[(chave + i) % this->mVagas] != -1 && this->vagas[(chave + i) % this->mVagas] != 0 && this->vagas[(chave + i) % this->mVagas] != chave && this->dist[(chave + i) % this->mVagas] >= i) {
                    i++;
                } else if (this->vagas[(chave + i) % this->mVagas] == chave) {
                    cout << ((chave + i) % this->mVagas);
                    cout << (" " + i) << endl;
                    if (out == true) {
                        this->vagas[chave % this->mVagas] = -1;
                        this->vagasEfet--;
                    }
                    if (i > dMax) {
                        dMax = i;
                    }
                    cond = false;
                } else if (this->vagas[(chave + i) % this->mVagas] != -1 && this->vagas[(chave + i) % this->mVagas] != 0 && this->vagas[(chave + i) % this->mVagas] != chave && this->dist[(chave + i) % this->mVagas] < i) {
                    cout << ("-1 -1") << endl;
                    cond = false;
                } else {
                    cond = false;
                    cout << ("-1 -1") << endl;
                }
            }
        }
        return dMax;
    }
};

int main(){
    int mMin, fMin, fMax, maior = 0, maior2 = 0;
    cin >> mMin >> fMin >> fMax;
    HashTable table(mMin);
    E2 e2(mMin);
    string entrada = "", placa = "";
    while(entrada != "END"){
      cin >> entrada;
      if(entrada != "END"){
        cin >> placa;
        int chave = calcularChave(placa);
        if(entrada == "IN"){
            table.in(chave, fMax);
            e2.in(chave, fMax, -5, false);
        } else if(entrada == "OUT"){
            table.out(chave, fMin, mMin);
        } else {
            maior = table.procurar(chave, false, maior);
            maior2 = e2.procurar(chave, false, maior2);
        }
      }
    }
    cout << maior << " " << maior2;

    return 0;
}
