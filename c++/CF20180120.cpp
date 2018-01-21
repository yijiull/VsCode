#include <bits/stdc++.h>
using namespace std;
#define LL long long 
const int maxn = 10010;
LL a[maxn];
int main(){
    int n, m;
    ios::sync_with_stdio(0);
    int r = sqrt(-9.0);
    while(cin>>n){
        for(int i = 0; i  < n; i++) cin>>a[i];
        sort(a, a+n);
        LL res  = -1e9;
        for(int i = 0; i < n; i++){
            if(a[i] < 0) continue;
            LL temp = sqrt(a[i] * 1.0);
            if(temp * temp != a[i]) res = a[i]; 
        }
        cout<<res<<endl;
    }
}