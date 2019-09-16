#include<bits/stdc++.h>
#include <math.h>

using namespace std;

int qteVagas, chave;

int hashFunction(char placa[]){
    return ( ((placa[0]-65)*pow(26,0)) + ((placa[1]-65)*pow(26,1)) + ((placa[2]-65)*pow(26,2)) + ((placa[3]-65)*pow(26,3)) + ((placa[4]-65)*pow(26,4)) + ((placa[5]-65)*pow(26,5)));
}

int alocador(int chave) {
    return chave % qteVagas;
}

int inserir(int chave){

}

int main(){
    cin >> qteVagas;
    int array[qteVagas];
    char placa [6];
    for(int i = 0; i < 6; i++){
        char letra;
        cin >> letra;
        placa[i] = letra;
    }
    chave = hashFunction(placa);
    cout << numVaga << endl;
    return 0;
}

