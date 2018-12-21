/**
 * 题目：https://codejam.withgoogle.com/codejam/contest/3324486/dashboard#s=p2
 * 容斥原理
 * res = 全部的排列 - 1对夫妻相邻 + 两对夫妻相邻 - 三对夫妻相邻...
 * 注意求组合数的时候有除法要求逆元。
 * O(n + m)
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MOD = 1e9+7;
const int MAXN = 200010;
LL a[MAXN], b[MAXN]; //阶乘、2的幂

LL quickpow(LL a, LL b){
    LL res = 1, temp = a % MOD;
    while(b){
        if(b & 1) res = res * temp % MOD;
        b >>= 1;
        temp = temp * temp % MOD;
    }
    return res;
}

int inv(int x){
    return quickpow(x, MOD-2);
}

int main(){
    fstream cin, cout;
    cin.open("large.in", ios::in);
    cout.open("out.txt", ios::out);
    int t;
    a[0] = 1;
    b[0] = 1;
    for(int i = 1; i < MAXN; i++){
        a[i] = a[i - 1] * i % MOD;
        b[i] = b[i - 1] * 2 % MOD;
    }
    cin>>t;
    int n, m;
    for(int k = 1; k <= t; k++){
        cin>>n>>m;
        int nn = n * 2;
        int res = 0;
        LL c = m;
        for(int i = 1; i <= m; i++){
            if(i&1){
                res = (res + a[nn-i] * b[i] % MOD * c % MOD) % MOD;
            }else{
                res = (res - a[nn-i] * b[i] % MOD * c % MOD + MOD) % MOD;
            }
            c = c * (m - i) % MOD * inv(i + 1) % MOD;
            //c = c * (m - i) / (i + 1);
        }
        cout<<"Case #"<<k<<": "<<(a[nn] - res + MOD) % MOD<<endl;
    }
}