#include <bits/stdc++.h>

using namespace std;

int main(){

    int n;
    long l;
    cin >> n >> l;
    long array[n];
    
    for(int i = 0; i < n; i++){
        cin>>array[i];
    }
    
    sort(array,array+n);
    
    long distanciaE = -1; long distanciaF = max(array[0], l-array[n-1]);
    
    for(int i = 0; i < n-1; i++){
        distanciaE = max(distanciaE, abs(array[i]-array[i+1]));
    }
    
    float resultadoE = (float) distanciaE/2; float resultadoF = distanciaF;
    
    cout << setprecision(10) << fixed;
    
    cout << max(resultadoE,resultadoF);
}
