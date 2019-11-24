#include <bits/stdc++.h>

using namespace std;

typedef long long int x;

int main(){
	x n; 
	cin >> n;
	vector<x> anterior(n + 1);
	for(int i=2;i<=n;i++){
		cin >> anterior[i];
		anterior[1] = -1;
	}

	vector<x> caminho;
	x atual = n;
	
	while(atual != -1){
		caminho.push_back(atual);
		atual = anterior[atual];
	}
	
	reverse(caminho.begin(),caminho.end());
	
	for(auto y:caminho){
		cout << y << " ";
	}
}

