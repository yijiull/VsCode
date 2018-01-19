#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
#define LL long long 

LL quickmul(LL a, LL b, LL mod){
    LL temp = a % mod, res = 0;
    while(b){
        if(b & 1) res = (res + temp) % mod;
        b >>= 1;
        temp = (temp + temp) % mod;
    }
    return res;
}
LL quickpow(LL a, LL b, LL mod){
    LL temp = a % mod, res = 1;
    while(b){
        if(b & 1) res = quickmul(res, temp, mod);
        b >>= 1;
        temp = quickmul(temp, temp, mod);
    }
    return res;
}
LL random(LL n){
    return ((double)rand() / RAND_MAX * n + 0.5);
}
bool check(LL a, LL n){
    LL t = n - 1;
    while(!(t & 1)) t >>= 1;
    LL temp = quickpow(a, t, n);
    while(t != n-1 && temp != 1 && temp != n-1){
        temp = quickmul(temp, temp, n);
        t <<= 1;
    }
    return temp == n-1 || t & 1;  // ture可能是素数，false一定不是素数
}
bool millerRobin(LL n, int t){
    if(n == 2) return true;
    if(n < 2 || !(n & 1)) return false;
    for(int i = 0; i < t; i++){
        LL a = random(n - 2) + 1;
        if(!check(a, n)) return false;
    }
    return true;
}
LL gcd(LL a, LL b){
    return b == 0 ? a : gcd(b, a % b);
}
LL pollardRho(LL n, LL c){
    LL x, y, d, i = 1, k = 2;
    x = random(n - 2) + 1;
    y = x;
    while(1){
        i++;
        x = (quickmul(x, x, n) + c) % n;
        d = gcd(y - x, n);
        if(d > 1 && d < n) return d;
        if(y == x) return n;
        if(i == k){
            y = x;
            k <<= 1;
        }
    }
}
LL fac[1100];
int cnt = 0;
void getfac(LL n, LL c){
    if(n == 1) return;
    if(millerRobin(n, 10)) {
        fac[cnt++] = n;
        return;
    }
    LL p = n;
    while(p >= n) p = pollardRho(p, c--);
    getfac(p, c);
    getfac(n / p, c);
    return;
}

int main(){
//    freopen("in.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
    int t;
    scanf("%d", &t);
    while(t--){
        LL n;
        scanf("%lld", &n);
        if(millerRobin(n, 10)){
            puts("Prime");
        }else{
            cnt = 0;
            getfac(n, 12312);
            LL ans = n;
            for(int i = 0; i < cnt; i++){
                ans = min(ans, fac[i]);
            }
            printf("%lld\n", ans);
            //cout<<ans<<endl;
        }
    }
    return 0;
}