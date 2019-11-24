#include <bits/stdc++.h>

using namespace std;

#define inf 1e9

int m,n,s;
int di,dj,dk;
int si,sj,sk;

vector<vector<vector<int>>> v;
vector<vector<vector<int>>> saving;

int recursion(int i, int j, int k) {
    if(i == di & j == dj && k == dk) return v[i][j][k];
    if(saving[i][j][k] != -1) return saving[i][j][k];
    int a = -inf;
    int b = -inf;
    int c = -inf;

    if(i > 0) {
        if(saving[i-1][j][k] != -1) a = saving[i-1][j][k];
        else a = recursion(i-1,j,k);
        saving[i-1][j][k] = a;
    }
    if(j < n-1){
        if(saving[i][j+1][k] != -1) b = saving[i][j+1][k];
        else b = recursion(i,j+1,k);
        saving[i][j+1][k] = b;
    }
    if(k < s-1){
        if(saving[i][j][k+1] != -1) c = saving[i][j][k+1];
        else c = recursion(i,j,k+1);
        saving[i][j][k+1] = c;
    }
    else{
        int ret = (max(max(a,b),c)+v[i][j][k]);
        saving[i][j][k] = ret;
        return ret;
    }
}
int main(){
    cin >> m >> n >> s;
    cin >> di >> dj >> dk;
    v.resize(m);
    saving.resize(m);
    for (int i = 0; i < m; i++){
        v[i].resize(n);
        saving[i].resize(n);
    }
    for (int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            v[i][j].resize(s);
            saving[i][j].resize(s,-1);
        }
    }
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < s; k++){
                cin >> v[i][j][k];
            }
        }
    }
    int p;
    cin >> p;
    while(p--){
        cin >> si >> sj>> sk;
        cout << recursion(si, sj, sk) << endl;
    }

    return 0;
}