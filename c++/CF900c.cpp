#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int a[maxn];


int main(){
    int n;
    ios::sync_with_stdio(0);
    while(cin>>n){
        int umax = -1e9, lmax = -1e9;
        for(int i = 1; i <= n; i++){
            int x;
            cin>>x;
            if(x > umax) {
                lmax = umax;
                umax = x;
                a[umax] = -1;
            }else if(x > lmax){
                a[umax]++;
                lmax = x;
            }
        }
        int res = 1;
        for(int i = 1; i <= umax; i++){
            if(a[res] < a[i]){
                res = i;
            }
        }
        cout<<res<<endl;
    }
}