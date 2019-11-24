#include <iostream>
#include <string>
#include <cmath>

using namespace std;

struct hashNode {
    int key;
    string value;

    hashNode(int key, string value)
    {
        this->key = key;
        this->value = value;
    }
};

class a_hashTable {
private:
    int Mactual, Fmin, Fmax, Mmin;
    int occupancyRate, effectiveOccupancyRate;
    hashNode **array;

public:
    a_hashTable(int Mmin, int Fmin, int Fmax) {
        this->Mmin = Mmin;
        this->Mactual = Mmin;
        this->Fmin = Fmin;
        this->Fmax = Fmax;
        this->occupancyRate = 0;
        this->effectiveOccupancyRate = 0;
        array = new hashNode * [Mactual];
        for (int i = 0; i < Mactual; i++) {
            array[i] = NULL;
        }
    }

    int a_hashFunction(int key, int M) {
        return (key % M);
    }

    pair<int, int> a_insert(int key, string value) {
        pair<int,int> positionAndDistance;
        if (100 * occupancyRate > Mactual * Fmax) { // Se precisar aumentar o tamanho
            int newMactual = Mactual * 2;
            a_rehash(newMactual);
            Mactual *= 2;
            return a_inserting(key, value);
        }
        else { // Caso não precise aumentar o tamanho
            return a_inserting(key, value);
        }
    }

    pair<int,int> a_inserting(int key, string value) {
        pair<int,int> positionAndDistance;
        positionAndDistance.first = a_hashFunction(key, Mactual);
        positionAndDistance.second = 0; // Inicialmente a distância é 0
        while (array[positionAndDistance.first] != NULL) { // Procura pela primeira posição vazia (NULL)
            positionAndDistance.second++; // Aumentar a distância
            positionAndDistance.first = a_hashFunction(key + positionAndDistance.second, Mactual); // Anda um para hash Function
        }
        array[positionAndDistance.first] = new hashNode(key, value); // Na posição que estava NULL, cria-se um novo node
        occupancyRate++; // Aumenta o valor de ocupação
        effectiveOccupancyRate++; // Aumenta a ocupação efetiva
        return positionAndDistance;
    }

    void a_rehash(int newMactual) {
        occupancyRate = 0;
        effectiveOccupancyRate = 0;
        hashNode **tempArray = new hashNode * [newMactual]; // Cria um array de nós temporário com o dobro ou metade do tamanho original
        for (int i = 0; i < Mactual; i++) {
            if (array[i] != NULL && array[i]->key != -1) { // Selecionar somente os arrays não nulos e que o key seja diferente de -1 (indisponível)
                int h = a_hashFunction(array[i]->key, newMactual); // Calcula a função de acordo com a key e com a nova capacidade
                while (tempArray[h] != NULL) { // Procura uma posição não nula a partir de h
                    h++;
                    h = a_hashFunction(h, newMactual);
                }
                tempArray[h] = array[i];
                occupancyRate++;
                effectiveOccupancyRate++;
            }
        }
        array = tempArray;
    }

    pair<int, int> a_remove(int key) {
        pair<int,int> positionAndDistance;
        positionAndDistance = a_search(key);
        if (positionAndDistance.first >= 0) {
            array[positionAndDistance.first]->key = -1;
            effectiveOccupancyRate--;
            if (100 * effectiveOccupancyRate < Mactual * Fmin && Mactual/2 >= Mmin) {
                int newMactual = Mactual / 2;
                a_rehash(newMactual);
                Mactual = Mactual / 2;
            }
        }
        return positionAndDistance;
    }

    pair<int, int> a_search(int key) {
        pair<int,int> positionAndDistance;
        positionAndDistance.first = a_hashFunction(key, Mactual);
        positionAndDistance.second = 0;
        bool found = false;
        while (array[positionAndDistance.first] != NULL && !found) {
            if (array[positionAndDistance.first]->key == key) {
                if (array[positionAndDistance.first]->key > 0) {
                    return positionAndDistance;
                } else {
                    found = true;
                }
            } else {
                positionAndDistance.second++;
                positionAndDistance.first = a_hashFunction(key + positionAndDistance.second, Mactual);
            }
        }
        positionAndDistance.first = -1;
        positionAndDistance.second = -1;
        return positionAndDistance;
    }

};

class b_hashTable {
private:
    int Mactual, Fmin, Fmax, Mmin;
    int occupancyRate, effectiveOccupancyRate;
    hashNode **array;

public:
    b_hashTable(int Mmin, int Fmin, int Fmax) {
        this->Mmin = Mmin;
        this->Mactual = Mmin;
        this->Fmin = Fmin;
        this->Fmax = Fmax;
        this->occupancyRate = 0;
        this->effectiveOccupancyRate = 0;
        array = new hashNode *[Mactual];
        for (int i = 0; i < Mactual; i++) {
            array[i] = NULL;
        }
    }

    int b_hashFunction(int key, int M) {
        if (key >= 0) {
            return (key % M);
        } else {
            return (key + M) % M;
        }
    }

    pair<int, int> b_insert(int key, string value) {
        pair<int, int> positionAndDistance;
        if (100 * occupancyRate > Mactual * Fmax) {
            //cout << "precisei dar rehash" << endl;
            int newMactual = Mactual * 2;
            b_rehash(newMactual);
            Mactual *= 2;
            return b_inserting(key, value);
        } else {
            return b_inserting(key, value);
        }
    }

    pair<int, int> b_inserting(int key, string value) {
        pair<int, int> positionAndDistance, auxPositionAndDistance;
        positionAndDistance.first = b_hashFunction(key, Mactual);
        positionAndDistance.second = 0;
        bool isItFirst = true;
        while (array[positionAndDistance.first] != NULL) {
            int elementDistance = b_hashFunction(
                    positionAndDistance.first - ((array[positionAndDistance.first]->key) % Mactual),
                    Mactual);
            if (array[positionAndDistance.first]->key == -1 || elementDistance >= positionAndDistance.second) {
                positionAndDistance.second++;
                positionAndDistance.first = b_hashFunction(key + positionAndDistance.second, Mactual);
            } else {
                hashNode *tempNode = new hashNode(array[positionAndDistance.first]->key,
                                                  array[positionAndDistance.first]->value);
                array[positionAndDistance.first]->key = key;
                array[positionAndDistance.first]->value = value;
                key = tempNode->key;
                value = tempNode->value;
                if (isItFirst) {
                    auxPositionAndDistance.first = positionAndDistance.first;
                    auxPositionAndDistance.second = positionAndDistance.second;
                    elementDistance++;
                    positionAndDistance.second = elementDistance;
                    positionAndDistance.first = b_hashFunction(key + positionAndDistance.second, Mactual);
                    isItFirst = false;
                } else {
                    elementDistance++;
                    positionAndDistance.second = elementDistance;
                    positionAndDistance.first = b_hashFunction(key + positionAndDistance.second, Mactual);
                }
            }
        }
        array[positionAndDistance.first] = new hashNode(key, value);
        occupancyRate++;
        effectiveOccupancyRate++;
        if (isItFirst) {
            return positionAndDistance;
        } else {
            return auxPositionAndDistance;
        }
    }

    void b_rehash(int newMactual) {
        occupancyRate = 0; effectiveOccupancyRate = 0;
        hashNode **tempArray = new hashNode *[newMactual];
        for (int i = 0; i < Mactual; i++) {
            if (array[i] != NULL && array[i]->key != -1){
                int h = b_hashFunction(array[i]->key, newMactual);
                int distance = 0;
                while (tempArray[h] != NULL ) {
                    int elementDistance = b_hashFunction((h - b_hashFunction(tempArray[h]->key,newMactual)), newMactual);
                    if (elementDistance >= distance) {
                        distance++;
                        h = b_hashFunction(array[i]->key + distance, newMactual);
                    } else {
                        hashNode *tempNode = new hashNode(tempArray[h]->key, tempArray[h]->value);
                        tempArray[h] = array[i];
                        distance = elementDistance + 1;
                        array[i] = tempNode;
                        h = b_hashFunction(array[i]->key + distance, newMactual);
                    }
                }
                tempArray[h] = array[i];
                occupancyRate++; effectiveOccupancyRate++;
            }
        }
        array = tempArray;
    }

    pair<int, int> b_remove(int key) {
        pair<int,int> positionAndDistance;
        positionAndDistance = b_search(key);
        if (positionAndDistance.first >= 0) {
            array[positionAndDistance.first]->key = -1;
            effectiveOccupancyRate--;
            if (100 * effectiveOccupancyRate < Mactual * Fmin && Mactual/2 >= Mmin) {
                int newMactual = Mactual / 2;
                b_rehash(newMactual);
                Mactual = Mactual / 2;
            }
        }
        return positionAndDistance;
    }

    pair<int, int> b_search(int key) {
        pair<int, int> positionAndDistance;
        positionAndDistance.first = b_hashFunction(key, Mactual);
        positionAndDistance.second = 0;
        bool found = false;
        while (array[positionAndDistance.first] != NULL && !found) {
            if (array[positionAndDistance.first]->key == key) {
                if (array[positionAndDistance.first]->key > 0) {
                    return positionAndDistance;
                } else {
                    found = true;
                }
            } else {
                int elementDistance;
                elementDistance = b_hashFunction(
                        positionAndDistance.first - ((array[positionAndDistance.first]->key) % Mactual), Mactual);

                positionAndDistance.second++;
                positionAndDistance.first = b_hashFunction(key + positionAndDistance.second, Mactual);

            }
        }
        positionAndDistance.first = -1;
        positionAndDistance.second = -1;
        return positionAndDistance;
    }
};


int placaToKey(string placa);

int main() {
    int Mmin, Fmin, Fmax;
    cin >> Mmin; cin >> Fmin; cin >> Fmax;
    a_hashTable *teste = new a_hashTable(Mmin, Fmin, Fmax);
    b_hashTable *secondHash = new b_hashTable(Mmin, Fmin, Fmax);
    string operation; string placa;
    int a_sch = 0; int b_sch = 0;
    cin >> operation;
    int cont=0;
    while (operation != "END") {
        cin >> placa;
        cont++;
        if (operation == "IN") {
            int key = placaToKey(placa);
            pair<int, int> testando = teste->a_insert(key, placa);
            pair<int, int> second = secondHash->b_insert(key, placa);
            cout << testando.first << " " << testando.second << " " << second.first << " " << second.second << endl;
            cin >> operation;
        } else if (operation == "OUT") {
            int key = placaToKey(placa);
            pair<int,int> out = teste->a_remove(key);
            pair<int, int> second = secondHash->b_remove(key);
            cout << out.first << " " << out.second << " " << second.first << " " << second.second << endl;
            cin >> operation;
        }
        else {
            int key = placaToKey(placa);
            pair<int,int> search = teste->a_search(key);
            pair<int, int> second = secondHash->b_search(key);
            cout << search.first << " " << search.second << " " << second.first << " " << second.second << endl;
            cin >> operation;
            if (search.second > a_sch) {
                a_sch = search.second;
            }
            if (second.second > b_sch) {
                b_sch = second.second;
            }
        }
    }
    cout << a_sch << " " << b_sch << endl;
    return 0;
}


int placaToKey(string placa) {
    int key = 0;
    for (int i = 0; i < 6; i ++){
        switch (placa[i]){
            case 'A':
                break;
            case 'B':
                key += pow(26, i);
                break;
            case 'C':
                key += 2*pow(26, i);
                break;
            case 'D':
                key += 3*pow(26, i);
                break;
            case 'E':
                key += 4*pow(26, i);
                break;
            case 'F':
                key += 5*pow(26, i);
                break;
            case 'G':
                key += 6*pow(26, i);
                break;
            case 'H':
                key += 7*pow(26, i);
                break;
            case 'I':
                key += 8*pow(26, i);
                break;
            case 'J':
                key += 9*pow(26, i);
                break;
            case 'K':
                key += 10*pow(26, i);
                break;
            case 'L':
                key += 11*pow(26, i);
                break;
            case 'M':
                key += 12*pow(26, i);
                break;
            case 'N':
                key += 13*pow(26, i);
                break;
            case 'O':
                key += 14*pow(26, i);
                break;
            case 'P':
                key += 15*pow(26, i);
                break;
            case 'Q':
                key += 16*pow(26, i);
                break;
            case 'R':
                key += 17*pow(26, i);
                break;
            case 'S':
                key += 18*pow(26, i);
                break;
            case 'T':
                key += 19*pow(26, i);
                break;
            case 'U':
                key += 20*pow(26, i);
                break;
            case 'V':
                key += 21*pow(26, i);
                break;
            case 'W':
                key += 22*pow(26, i);
                break;
            case 'X':
                key += 23*pow(26, i);
                break;
            case 'Y':
                key += 24*pow(26, i);
                break;
            case 'Z':
                key += 25*pow(26, i);
                break;
        }
    }
    return key;
}