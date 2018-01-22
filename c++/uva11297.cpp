//整体二分  
//有bug！！！
//=_=||
#include <bits/stdc++.h>
using namespace std;
const int maxn = 510;
const int maxq = 100010;
const int inf = 1<<30;
struct BIT{
    int n, m;
    int a[maxn][maxn];

    void init(int _n, int _m){
        n = _n; m = _m;
        memset(a, 0, sizeof(a));
    }

    void add(int i, int j, int v){
        for(; i <= n; i += i & -i){
            for(; j <= m; j += j & -j){
                a[i][j] += v;
            }
        }
    }
    int sum(int i, int j){
        int res = 0;
        for(; i; i -= i & -i){
            for(; j; j -= j & -j){
                res += a[i][j];
            }
        }
        return res;
    }
}bit;
struct Qry{
    int v;
    int x1, y1, x2, y2;
    int id, type;
    Qry(int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0, int v = 0, int id = 0, int type = 0) : 
        x1(x1), y1(y1), x2(x2), y2(y2), v(v), id(id), type(type){}
    void print(){
        printf("  ==  %d %d %d %d v=%d %d %d\n", x1, y1, x2, y2, v, id, type);
    }
}q[maxq], q1[maxq], q2[maxq];

int a[maxn][maxn];
int ans[maxq];

void CDQ(int L, int R, int l, int r){
    if(L > R) return ;
    if(l == r){
        for(int i = L; i <= R; i++){
            if(q[i].type == 2) ans[q[i].id] = l;
        }
        return ;
    }
    int m = l + r >> 1;
    int f = 0, g = 0;
    for(int i = L; i <= R; i++){
        if(q[i].type == 1){
            if(q[i].v <= m){
                bit.add(q[i].x1, q[i].y1, q[i].id);
                q1[f++] = q[i];
            }else q2[g++] = q[i];
        }else{
            int temp = bit.sum(q[i].x2, q[i].y2) - bit.sum(q[i].x1 - 1, q[i].y2) - bit.sum(q[i].x2, q[i].y1 - 1) + bit.sum(q[i].x1 - 1, q[i].y1 - 1);
            q[i].print();
            cout<<temp<<endl;
            if(q[i].v <= temp) q1[f++] = q[i];
            else{
                q[i].v -= temp;
                q2[g++] = q[i];
            }
        }
    }
    //for(int i = 1; i <= bit.n; i++){
    //    for(int j = 1; j <= bit.n; j++){
    //        cout<<bit.a[i][j]<<" ";
    //    }
    //    cout<<endl;
    //}
    for(int i = 0; i < f; i++) if(q1[i].type == 1) bit.add(q1[i].x1, q1[i].y1, -q1[i].id);
    memcpy(q + L, q1, f * sizeof(Qry));
    memcpy(q + L + f, q2, g * sizeof(Qry));
    CDQ(L, L + f - 1, l, m);
    CDQ(L + f, R, m + 1, r);
}

int main(){
    int n;
    while(scanf("%d", &n) != EOF){
        int idx = 0;
        int x;
        bit.init(n, n);
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                scanf("%d", &x);
                a[i][j] = x;
                q[++idx] = Qry(i, j, 0, 0, x, 1, 1);
            }
        }
        int m;
        scanf("%d", &m);
        int cnt = 0;
        while(m--){
            char op[5];
            int x1, y1, x2, y2, v;
            scanf("%s", op);
            if(op[0] == 'q'){
                scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
                q[++idx] = Qry(x1, y1, x2, y2, 2, ++cnt, 2);
                q[++idx] = Qry(x1, y1, x2, y2, (x2 - x1 + 1) * (y2 - y1 + 1), ++cnt, 2);
            }else{
                scanf("%d %d %d", &x1, &y1, &v);
                q[++idx] = Qry(x1, y1, 0, 0, a[x1][y1], -1, 1);
                a[x1][y1] = v;
                q[++idx] = Qry(x1, y1, 0, 0, v, 1, 1);
            }
        }
        CDQ(1, idx, 0, inf);
        for(int i = 1; i <= cnt; i += 2){
            printf("%d %d\n", ans[i + 1], ans[i]);
        }
    }
}