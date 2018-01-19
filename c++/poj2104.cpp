#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
#define lson l, m
#define rson m + 1, r
const int maxn = 1e5+10;
int L[maxn<<5], R[maxn<<5], sum[maxn<<5];
int tot;
int a[maxn], T[maxn], Hash[maxn];

int build(int l, int r){
    int rt = (++tot);
    sum[rt] = 0;
    if(l < r){
        int m = (l + r) >> 1;
         L[rt] = build(lson);
         R[rt] = build(rson);
    }
    return rt;
}

int update(int pre, int l, int r, int x){
    int rt = (++tot);
    L[rt] = L[pre], R[rt] = R[pre], sum[rt] = sum[pre] + 1;
    if(l < r){
        int m = (l + r) >> 1;
        if(x <= m) L[rt] = update(L[pre], lson, x);
        else R[rt] = update(R[pre], rson, x);
    }
    return rt;
}

int query(int u, int v, int l, int r, int k){
    if(l >= r) return l;
    int m = (l + r) >> 1;
    int num = sum[L[v]] - sum[L[u]];
    if(num >= k) return query(L[u], L[v], lson, k);
    else return query(R[u], R[v], rson, k - num);
}


int main(){
    int n, m;
    while(scanf("%d %d", &n, &m) != EOF){
        tot = 0;
        for(int i = 1; i <= n; i++){
            scanf("%d", &a[i]);
            Hash[i] = a[i];
        }
        sort(Hash + 1, Hash + 1 + n);
        int d = unique(Hash + 1, Hash + 1 + n) - Hash - 1;
        T[0] = build(1, d);
        for(int i = 1; i <= n; i++){
            int x = lower_bound(Hash + 1, Hash + 1 + d, a[i]) - Hash;
            //cout<<"=== " <<x<<"  === \n";
            T[i] = update(T[i-1], 1, d, x);
        }
        while(m--){
            int l, r, k;
            scanf("%d %d %d", &l, &r, &k);
            int x = query(T[l-1], T[r], 1, d, k);
            printf("%d\n", Hash[x]);
        }
    }

}