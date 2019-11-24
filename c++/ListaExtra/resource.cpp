#include <bits/stdc++.h>

using namespace std;
 
long long n, x1, x2;
 
struct No{
    long long numero, id;
    bool operator <(No no){
            return numero < no.numero;
        }
}
a[300010];
 
int main() {
    cin >> n >> x1 >> x2;
    for(long long i=1; i<=n; i++){
        cin >> a[i].numero;
    }
        
    for(long long i = 1; i <= n; i++){
        a[i].id = i;
    }
    sort(a + 1, a + 1 + n);
    bool b = 0;
     
    long long l = n;
    for(; l >= 1; l--) {
        if((n-l + 1) * a[l].numero >= x2)
            break;
    }
    bool cond = 1;
    if(!l) {
        cond = 0;
    }
    long long max = l - 1;
    for(l--; l >= 1; l--){
        if((max-l + 1) * a[l].numero >= x1)
            break;
    }
    if(!l) {
        cond=0;
    }
    long long max2 = l;
    if(cond){
        cout << "Yes" << endl;
        cout << max - max2 + 1 << " " << n-max << endl;
        for(long long i=max2; i <= max; i++)
            cout << a[i].id << " ";
        cout << endl;;
        for(long long i = max + 1; i <= n; i++)
            cout << a[i].id << " ";
        cout << endl;
    exit(0);
}
    swap(x1, x2);
    l = n;
    for(; l>=1; l--) {
        if((n - l + 1) * a[l].numero >= x2 )
            break;
    }
    cond = 1;
    if(!l) {
        cout << "No" << endl;
        exit(0);
    }
    max = l - 1;
    for(l--; l >= 1; l--) {
        if((max - l + 1) * a[l].numero >= x1)
            break;
    }
    if(!l) {
        cout << "No" << endl;
        exit(0);
    }
    max2 = l;
        cout << "Yes" << endl;
        cout << n - max << " " << max - max2 + 1 << endl;
        for(long long i= max + 1; i <= n; i++)
            cout << a[i].id << " ";
        cout << endl;
        for(long long i = max2; i <= max; i++)
            cout << a[i].id << " ";
        cout << endl;
         
    return 0;
     
}