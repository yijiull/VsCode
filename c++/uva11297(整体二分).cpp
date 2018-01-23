#include <bits/stdc++.h>
using namespace std;
#define LL long long 
const int maxn = 520;
const int maxq = 350010;     //数组开小了WA到死。。。。 500 × 500 + 40000 × 2
const int inf = 1<<30;
struct Qry{
    int x1, y1, x2, y2, v;
    int id, type;
}q[maxq], q1[maxq], q2[maxq];

struct BIT{
    int n;
    int b[maxn][maxn];
    void init(int _n){
        n = _n;
        memset(b, 0, sizeof(b));
    }
    void add(int x, int y, int v){
        for(int i = x; i <= n; i += i & -i){
            for(int j = y; j <= n; j += j & -j){
                b[i][j] += v;
            }
        }
    }
    int sum(int x, int y){
        int res = 0;
        for(int i = x; i; i -= i & -i){
            for(int j = y; j; j -= j & -j){
                res += b[i][j];
            }
        }
        return res;
    }
    int sum(int x1, int y1, int x2, int y2){
        return sum(x2, y2) - sum(x1 - 1, y2) - sum(x2, y1 - 1) + sum(x1 - 1, y1 - 1);
    }
}bit;
int a[maxn][maxn], ans[maxq];
void solve(int L, int R, LL l, LL r){
    if(L > R) return ;
    if(l == r){
        for(int i = L; i <= R; i++){
            if(q[i].type == 2) ans[q[i].id] = l;
        }
        return ;
    }
    LL m = (l + r) >> 1;
    int f = 0, g = 0;
    for(int i = L; i <= R; i++){
        if(q[i].type == 1){
            if(q[i].v <= m) {
                bit.add(q[i].x1, q[i].y1, q[i].id);
                q1[f++] = q[i];
            }else q2[g++] = q[i];
        }else{
            int temp = bit.sum(q[i].x1, q[i].y1, q[i].x2, q[i].y2);
            if(temp >= q[i].v) q1[f++] = q[i];
            else {
                q[i].v -= temp;
                q2[g++] = q[i];
            }
        }
    }
    for(int i = 0; i < f; i++) if(q1[i].type == 1) bit.add(q1[i].x1, q1[i].y1, -q1[i].id);
    memcpy(q + L, q1, f * sizeof(Qry));
    memcpy(q + L + f, q2, g * sizeof(Qry));
    solve(L, L + f - 1, l, m);
    solve(L + f, R, m + 1, r);
}

int main(){
    int n;
    //freopen("in.txt", "r", stdin);
    //freopen("out1.txt", "w", stdout);
    while(scanf("%d", &n) != EOF){
        bit.init(n);
        int idx = 0, cnt = 0;
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                scanf("%d", &a[i][j]);
                q[++idx] = Qry{i, j, 0, 0, a[i][j], 1, 1};
            }
        }
        int m;
        scanf("%d",&m);
        for(int i = 1; i <= m; i++){
            int x1, y1, x2, y2, v;
            char op[4];
            scanf("%s", op);
            if(op[0] == 'q'){
                scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
                q[++idx] = Qry{x1, y1, x2, y2, 1, ++cnt, 2};
                int temp = (x2 - x1 + 1) * (y2 - y1 + 1);
                q[++idx] = Qry{x1, y1, x2, y2, temp, ++cnt, 2};
            }else{
                scanf("%d %d %d", &x1, &y1, &v);
                q[++idx] = Qry{x1, y1, 0, 0, a[x1][y1], -1, 1};
                a[x1][y1] = v;
                q[++idx] = Qry{x1, y1, 0, 0, v, 1, 1};
            }
        }
        solve(1, idx, 0, inf);
        for(int i = 1; i <= cnt; i += 2){
            printf("%d %d\n", ans[i + 1], ans[i]);
        }
    }
}