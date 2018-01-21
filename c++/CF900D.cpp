//容斥（莫比乌斯反演）
#include <bits/stdc++.h>
using namespace std;
#define LL long long 
const int mod = 1e9+7;
LL quickpow(LL a, LL b, LL mod){
    LL temp = a % mod, res = 1;
    while(b){
        if(b & 1)  res = res * temp % mod;
        b >>= 1;
        temp = temp * temp % mod;
    }
    return res;
}
map<int, LL> mp;

LL solve(int x){
    if(x == 1) return 1;
    if(mp.count(x)) return mp[x];
    mp[x] = quickpow(2, x-1, mod);
    for(int i = 2; i * i <= x; i++){
        if(x % i == 0){
            mp[x] = (mp[x] - solve(i) + mod) % mod;
            if(i != x / i) mp[x] = (mp[x] - solve(x / i) + mod) % mod;
        }
    }
    mp[x] = (mp[x] - solve(1) + mod) % mod;
    return mp[x];
}

int main(){
    ios::sync_with_stdio(0);
    int x, y;
    while(cin>>x>>y){
        if(y % x != 0){
            cout<<0<<endl;
        }else{
            cout<<solve(y / x)<<endl;

        }
    }

}