#include <bits/stdc++.h>

using namespace std;

int main() {
    int x; cin >> x;
    for (int i = 0; i < x; i++) {
        int y; cin >> y;
        cout << ceil((sqrt(8 * y + 1) - 1) / 2) << endl;
    }
    return 0;
}