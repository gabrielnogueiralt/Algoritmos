#include <bits/stdc++.h>

using namespace std;

#define inf 1e9

int m, n, s, fi, fj, fk, ci, cj, ck, p;

vector<vector<vector<int>>> descoberto;
vector<vector<vector<int>>> vetor;

int backtraking(int i, int j, int k) {

    if(i < 0 || j >=n || k >=s){
        return INT_MIN;  
    }

    if(i == fi & j == fj && k == fk){
        return vetor[i][j][k];  
    } 
    if(descoberto[i][j][k] != -1){
        return descoberto[i][j][k];
    }

    int x,y,z;
    x=backtraking(i-1,j,k);
    y=backtraking(i,j+1,k);
    z=backtraking(i,j,k+1);
   
    int maximo = (max(max(x, y), z) + vetor[i][j][k]);
    descoberto[i][j][k] = maximo;
    return maximo;
}
int main(){
    cin >> m >> n >> s >> fi >> fj >> fk;

    vetor.resize(m);
    descoberto.resize(m);

    for (int i = 0; i < m; i++){
        vetor[i].resize(n);
        descoberto[i].resize(n);
    }
    for (int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            vetor[i][j].resize(s);
            descoberto[i][j].resize(s,-1);
        }
    }
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < s; k++){
                cin >> vetor[i][j][k];
            }
        }
    }

    cin >> p;
    while(p--){
        cin >> ci >> cj >> ck;

        cout << backtraking(ci, cj, ck) << endl;
    }

    return 0;
}