#include <iostream>
#include <vector>
#include <math.h>
#include <bits/stdc++.h>

using namespace std;

struct Coordinate {
    pair<int, int> coordinate;
    bool coinPos;
    vector<int> adjacent;

    Coordinate(int x, int y, bool coinPos, vector<int> adjacent){
        this->coordinate = make_pair(x,y);
        this->coinPos = coinPos;
        this->adjacent = adjacent;
    }
};

struct MarcosBros {
    vector<Coordinate> map;

    void BellmanFord(vector<Coordinate> map, int s, vector<int> D){
        for(int i = 0; i < map.size(); i++){
            D[i] = INT_MAX;
        }
        D[s] = 0;
        for (int j = 0; j < (map.size()-1); j++) {
            for (int i = 0; i < map.size(); i++) {
                int k =
            }
        }

    }

};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    vector<Coordinate> map;
    vector<int> xVal, yVal, coinPos, D;

    int t,n,x,y,m,w = 0, dj, vj;
    cin >> t;
    for(int i = 0; i < t; i++){
        cin >> n;
        for(int j = 0; j < n; j++){
            cin >> x >> y;
            xVal.push_back(x);
            yVal.push_back(y);
        }
        cin >> m;
        for(int k = 0; k < m; k++){
            cin >> i;
            coinPos.push_back(i);
        }
        vector<vector<int>> adjacent(n);
        for (int p = 0; p < n; p++) {
            cin >> dj;
            for (int j = 0; j < dj; j++) {
                cin >> vj;
                adjacent[p].push_back(vj);
            }
        }

        for(int l = 0; l < n; l++){
            if(!coinPos.empty()){
                if(l == coinPos.at(w)){
                    Coordinate *c = new Coordinate(xVal.at(l), yVal.at(l), true, adjacent.at(l));
                    w++;
                } else {
                    Coordinate *c = new Coordinate(xVal.at(l), yVal.at(l), false, adjacent.at(l));
                }
            } else {
                map.push_back(Coordinate(xVal.at(l), yVal.at(l), false, adjacent.at(l)));
            }
        }
        MarcosBros *gameMap = new MarcosBros();
        gameMap->BellmanFord(map, 0, D);
        w = 0;
        map.clear();
    }


//    int result = pow((xVal.at(1) - xVal.at(0)),2) + pow((yVal.at(1) - yVal.at(0)) ,2);
//    cout << result << endl;
    return 0;
}