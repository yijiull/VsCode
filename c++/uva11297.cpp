#include <bits/stdc++.h>
using namespace std;

const int maxn = 2010;
const int inf = 1<<30;

struct SegTree2D{
    int Max[maxn][maxn], Min[maxn][maxn];
    int n, m;
    int xo, xleaf, x1, y1, x2, y2, x, y, v, vmax, vmin;

    void query1D(int l, int r, int rt){
        if(y1 <= l && r <= y2){
            vmax = max(Max[xo][rt], vmax);
            vmin = min(Min[xo][rt], vmin);
            return;
        }
        int M  = (l + r) / 2;
        if(y1 <= M) query1D(l, M, rt << 1);
        if(y2 > M) query1D(M + 1, r, rt << 1 | 1);
    }
    void query2D(int l, int r, int rt){
        if(x1 <= l && r <= x2){
            xo = rt;
            query1D(1, m, 1);
            return;
        }
        int M = (l + r) >> 1;
        if(x1 <= M) query2D(l, M, rt<<1);
        if(x2 > M) query2D(M + 1, r, rt << 1 | 1);
    }
    void modify1D(int l, int r, int rt){
        if(l == r){
            if(xleaf){
                Max[xo][rt] = Min[xo][rt] = v;
            }else{
                Max[xo][rt] = max(Max[xo << 1][rt], Max[xo << 1 | 1][rt]);
                Min[xo][rt] = min(Min[xo << 1][rt], Min[xo << 1 | 1][rt]);
            }
            return ;
        }
        int M = l + r >> 1;
        if(y <= M) modify1D(l, M, rt << 1);
        else modify1D(M + 1, r, rt << 1 | 1);
        Max[xo][rt] = max(Max[xo][rt << 1], Max[xo][rt << 1 | 1]);
        Min[xo][rt] = min(Min[xo][rt << 1], Min[xo][rt << 1 | 1]);
    }

    void modify2D(int l, int r, int rt){
        if(l == r){
            xo = rt; xleaf = 1;
            modify1D(1, m, 1);
            return ;
        }
        int M = (l + r) >> 1;
        if(x <= M) modify2D(l, M, rt << 1);
        else modify2D(M + 1, r, rt << 1 | 1);
        xo = rt; xleaf = 0;
        modify1D(1, m, 1);
    }

    void query(){
        vmax = -inf; vmin = inf;
        query2D(1, n, 1);
    }
    void modify(){
        modify2D(1, n, 1);
    }
};

SegTree2D t;

int main(){
    int n, m, q;
    char op[10];
   // freopen("in.txt", "r", stdin);
   // freopen("out.txt", "w", stdout);
    while(scanf("%d", &n) != EOF){
        t.n = n; t.m = n;
        m = n;
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                scanf("%d", &t.v);
                t.x = i, t.y = j;
                t.modify();
            }
        }
        scanf("%d", &q);
        while(q--){
            scanf("%s", op);
            if(op[0] == 'q'){
                scanf("%d %d %d %d", &t.x1, &t.y1, &t.x2, &t.y2);
                t.query();
                printf("%d %d\n", t.vmax, t.vmin);
            }else{
                scanf("%d %d %d", &t.x, &t.y, &t.v);
                t.modify();
            }
        }
    }
    return 0;
}