//比主席树慢了挺多
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int maxn = 5e4 + 10;
const int maxq = 2e4 + 10;
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
                bit.add(q[i].id, q[i].y);
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
    for(int i = 0; i < f; i++) if(q1[i].type == 1) bit.add(q1[i].id, -q1[i].y);
    memcpy(q + L, q1, f * sizeof(Qry));
    memcpy(q + L + f, q2, g * sizeof(Qry));
    solve(L, L + f - 1, l, m);
    solve(L + f, R, m + 1, r);
}
int main(){
    ios::sync_with_stdio(0);
    int t;
    cin>>t;
    while(t--){
        cin>>n>>m;
        bit.init(n);
        int idx = 0;
        for(int i = 1; i <= n; i++){
            cin>>a[i];
            q[++idx] = Qry(a[i], 1, 0, i, 1);
        }
        int id = 0;
        for(int i = 1; i <= m; i++) {
            char op[3];
            int x, y, k;
            cin>>op;
            if(op[0] == 'Q'){
                cin>>x>>y>>k;
                q[++idx] = Qry(x, y, k, id++, 2);
            }else{
                cin>>x>>y;
                q[++idx] = Qry(a[x], -1, 0, x, 1);
                a[x] = y;
                q[++idx] = Qry(y, 1, 0, x, 1);
            }
        }
        solve(1, idx, 0, inf);
        for(int i = 0; i < id; i++){
            cout<<ans[i]<<endl;
            
        }
    }
}