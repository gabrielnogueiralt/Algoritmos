#include <bits/stdc++.h>

using namespace std;

int primos[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31 };
int p[17];
int c[17];
int tamanho;

bool verificar(int num) {

	for (int i = 0; i < 11; i++) {
		if (num == primos[i])
			return true;
	}
	return false;
}

void backTracking(int num) {

	if (num == tamanho) {
		if (verificar(c[num-1] + 1)) {
			cout << c[0];
			for (int i = 1; i < tamanho; i++)
				cout << " " << c[i];
			cout << endl;
		}
		return;
	}

	for (int j = 2; j <= tamanho; j++) {
		if (!p[j]) {
			if (verificar(j + c[num-1])) {
				p[j] = 1;
				c[num] = j;
				backTracking(num + 1);
				p[j] = 0;
			}
		}
	}

}

int main() {

	int i = 1;

	while (cin >> tamanho) {
		if(i > 1) cout << endl;
		c[0] = 1;
		p[17] = {0};
		cout << "Case " << i << ":" << endl;
		backTracking(1);
		i++;
	}

	return 0;
}
