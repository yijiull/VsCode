//比主席树慢了挺多
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int maxn = 1e5 + 10;
const int maxq = 5010;
const int inf = 0x3f3f3f3f;

struct Qry{
    int x, y, k;
    int id, type;
    Qry(int x = 0, int y = 0, int k = 0, int id = 0, int type = 0):
        x(x), y(y), k(k), id(id), type(type){}
}q[maxn + maxq], q1[maxn + maxq], q2[maxn + maxq];

struct Bit{
    int n;
    int a[maxn];
    void init(int _n){
        n = _n;
        memset(a, 0, sizeof a);
    }
    void add(int i, int x){
        for(; i <= n; i += i & -i) a[i] += x;
    }
    int sum(int i){
        int res = 0;
        for(; i; i -= i & -i) res += a[i];
        return res;
    }
}bit;

int n, m, a[maxn];
int ans[maxq];

void solve(int L, int R, int l, int r){
    if(L > R) return;
    if(l == r){
        for(int i = L; i <= R; i++){
            if(q[i].type == 2) ans[q[i].id] = l;
        }
        return;
    }
    int m = l + r >> 1;
    int f = 0, g = 0;
    for(int i = L; i <= R; i++){
        if(q[i].type == 1){
            if(q[i].x <= m) {
                bit.add(q[i].id, 1);
                q1[f++] = q[i];
            }else q2[g++] = q[i];
        }else{
            int temp = bit.sum(q[i].y) - bit.sum(q[i].x - 1);
            if(temp >= q[i].k) {
                q1[f++] = q[i];
            }else{
                q[i].k -= temp;
                q2[g++] = q[i];
            }
        }
    }
    for(int i = 0; i < f; i++) if(q1[i].type == 1) bit.add(q1[i].id, -1);
    memcpy(q + L, q1, f * sizeof(Qry));
    memcpy(q + L + f, q2, g * sizeof(Qry));
    solve(L, L + f - 1, l, m);
    solve(L + f, R, m + 1, r);
}
int main(){
    ios::sync_with_stdio(0);
    while(cin>>n>>m){
        bit.init(n);
        int idx = 0;
        for(int i = 1; i <= n; i++){
            cin>>a[i];
            q[++idx] = Qry(a[i], 0, 0, i, 1);
        }
        for(int i = 1; i <= m; i++){
            int x, y, k;
            cin>>x>>y>>k;
            q[++idx] = Qry(x, y, k, i, 2);
        }
        solve(1, idx, -inf, inf);
        for(int i = 1; i <= m; i++){
            cout<<ans[i]<<endl;
        }
    }
}