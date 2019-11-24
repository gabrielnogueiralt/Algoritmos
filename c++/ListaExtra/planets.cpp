#include <bits/stdc++.h>

using namespace std;

vector<int>vec1[150000];
vector<int>vec2[150000];

struct No {
    int origem, para, proximo, w;
}

        aux[5151111];

int n , m, it;
int head[150000];
void add(int origem,int para,int w) {
    aux[it].para=para;
    aux[it].w=w;
    aux[it].proximo=head[origem];
    head[origem]=it++;
}


int procurar(int x, int y) {
    int l = 0;
    int r = vec1[x].size() - 1;
    while(r-l>=0) {
        int m = (l+r) / 2;
        if(vec1[x][m] > y) {
            r = m - 1;
        }
        else if(vec1[x][m] < y) {
            l = m + 1;
        }
        else {
            return vec2[x][m];
        }
    }
    return y;
}

int distancia[150000];
int v[150000];

void planets() {

    queue<int>s;
    memset(v, 0, sizeof(v));
    for(int i = 1; i <= n; i++){
        distancia[i]=0x3f3f3f3f;
    }
    distancia[1] = procurar(1,0);
    s.push(1);
    while(!s.empty()) {
        int u = s.front();
        v[u] = 0;
        s.pop();
        for(int i = head[u]; i != -1; i = aux[i].proximo) {
            int z = aux[i].para;
            int w = aux[i].w;
            int y = distancia[u] + w;
            if(z!=n){
                y = procurar(z,y);
            }
            if(distancia[z]>y) {
                distancia[z]=y;
                if(v[z] == 0) {
                    v[z] = 1;
                    s.push(z);
                }
            }
        }
    }
    if(distancia[n] == 0x3f3f3f3f)
        cout << -1 << endl;
    else
        cout << distancia[n] << endl;
}

int main() {
    while(cin >> n >> m) {
        it=0;
        memset(head,-1,sizeof(head));
        for(int i=1;i<=n;i++) {
            vec1[i].clear(),vec2[i].clear();
        }
        for(int i=1;i<=m;i++) {
            int x,y,w;
            cin >> x >> y >>w;
            add(x,y,w);
            add(y,x,w);
        }
        for(int i=1;i<=n;i++) {
            int k;
            cin >> k;
            while(k--) {
                int v;
                cin >> v;
                vec1[i].push_back(v);
            }
            for(int j = vec1[i].size() - 1; j >= 0; j--) {
                int pre;
                if(j == vec1[i].size() - 1 || vec1[i][j] != vec1[i][j + 1] - 1) {
                    pre = vec1[i][j] + 1;
                    vec2[i].push_back(vec1[i][j]+1);
                }
                else vec2[i].push_back(pre);
            }
            reverse(vec2[i].begin(), vec2[i].end());
        }
        planets();
    }
}
