#include <bits/stdc++.h>

using namespace std;

struct Vertex {
    int xCoord, yCoord, numEdges;
    bool coin;
    vector<int> coordinate;
};

struct Graph {
    Vertex *vertices;
    int indexVertices;
    int numVertices;

    Graph(int numVertices) {
        this->numVertices = numVertices;
        this->indexVertices = 0;
        vertices = new Vertex [numVertices];
    }

    void insert(int xCoord, int yCoord) {
        vertices[indexVertices].xCoord = xCoord;
        vertices[indexVertices].yCoord = yCoord;
        vertices[indexVertices].coin = false;
        indexVertices++;

    }

    int cost(Vertex in, Vertex out){
        return (pow((out.xCoord - in.xCoord),2)) + (pow((out.yCoord - in.yCoord),2));
    }

    void bellmanFord(){
        vector<vector<int>> D;
        vector<int> F;

        D.resize(numVertices);
        for (int i = 0; i < numVertices; i ++) {
            for (int j = 0; j < numVertices; j++) {
                D.at(i).push_back(10000000);
            }
            F.push_back(-1);
        }
        D.at(0).at(0) = 0;

        for (int k = 1; k < numVertices; k++) {
            for (int t = 0; t < numVertices; t++) {
                D.at(k).at(t) = D.at(k - 1).at(t);
            }
            for (int u = 0; u < numVertices - 1; u++) {
                vector<int> edge = vertices[u].coordinate;
                for (int cont = 0; cont < edge.size(); cont++) {
                    int t = edge.at(cont);
                    int w = cost(vertices[u], vertices[t]);
                    if (vertices[t].coin) {
                        w = w * -1;
                    }
                    if (D[k - 1][u] != 10000000 && D[k - 1][u] + w < D[k][t]) {
                        D.at(k).at(t) = D[k - 1][u] + w;
                        F.at(t) = u;
                    }
                }
            }
        }

        for (int u = 0; u < numVertices - 1; u++) {
            vector<int> edge = vertices[u].coordinate;
            for (int cont = 0; cont < edge.size(); cont++) {
                int t = edge.at(cont);
                int w = cost(vertices[u], vertices[t]);
                if (vertices[t].coin) {
                    w = w * -1;
                }
                if (D[numVertices-1][t] != 10000000 && D[numVertices - 1][u] + w < D[numVertices - 1][t]) {
                    cout << "LOOP" << endl;
                    return;
                }
            }
        }

        cout << D.at(numVertices - 1).at(numVertices - 1) << " ";
        vector<int> path;
        path.push_back(numVertices - 1);
        int cur = numVertices - 1;
        while (F[cur] != 0) {
            path.insert(path.begin(), F[cur]);
            cur = F[cur];
        }
        path.insert(path.begin(), 0);
        cout << path[0] << " ";
        for (int i = 1; i < path.size()-1; i++){
            cout << path[i];
            if (i) cout << " ";
        }
        cout << path[path.size()-1] << endl;
    }

};

int main() {
    int t, n, m, xCoord ,yCoord;
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> n;
        Graph *graph = new Graph(n);
        for (int j = 0; j < n; j++) {
            cin >> xCoord >> yCoord;
            graph->insert(xCoord, yCoord);
        }
        cin >> m;
        int coinPos;
        for (int j = 0; j < m; j++) {
            cin >> coinPos;
            graph->vertices[coinPos].coin = true;
        }
        for (int j = 0; j < n; j++) {
            int dj, coordinate;
            cin >> dj;
            graph->vertices[i].numEdges = dj;
            for (int l = 0; l < dj; l++) {
                cin >> coordinate;
                graph->vertices[j].coordinate.push_back(coordinate);
            }
        }
        graph->bellmanFord();
    }
    return 0;
}