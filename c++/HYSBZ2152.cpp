#include <bits/stdc++.h>
using namespace std;
const int maxn = 20010;
const int maxd = 4;
const int inf = 0x3f3f3f3f;
int n, k;
int ct[maxd], temp[maxd];  // 开太大会TLE...反复memset耗时严重...
int rt, snode, ans;
int size[maxn];
int maxson[maxn], vis[maxn];

struct Edge{
    int v, w, nxt;
    Edge(int v = 0, int w = 0, int nxt = 0) : v(v), w(w), nxt(nxt) {}
}e[maxn<<1];
int head[maxn], cnt;
void init(){
    cnt = 0;
    memset(head, -1, sizeof head);
}
void add(int u, int v, int w){
    e[cnt] = Edge(v, w, head[u]);
    head[u] = cnt++;
}

void getrt(int u, int f){
    size[u] = 1;
    maxson[u] = 0;
    for(int i = head[u]; ~i; i = e[i].nxt){
        int v = e[i].v;
        if(vis[v] || v == f) continue;
        getrt(v, u);
        size[u] += size[v];
        maxson[u] = max(maxson[u], size[v]);
    }
    maxson[u] = max(maxson[u], snode - size[u]);
    if(maxson[u] < maxson[rt]) rt = u;
}

void dfs(int u, int f, int d){
    if(d == 0) ans += ct[0];   //特殊处理
    else ans += ct[k - d];
    ++temp[d];
    for(int i = head[u]; ~i; i = e[i].nxt){
        int v = e[i].v;
        if(vis[v] || v == f) continue;
        dfs(v, u, (d + e[i].w) % 3);
    }
}

void cal(int u){
    memset(ct, 0, sizeof ct);  
    ct[0] = 1;
    for(int i = head[u]; ~i; i = e[i].nxt){
        int v = e[i].v;
        if(vis[v]) continue;
        memset(temp, 0, sizeof temp);
        dfs(v, u, e[i].w);
        for(int i = 0; i < k ; i++) ct[i] = ct[i] + temp[i];
    }
}

void divide(int u){
    getrt(u, u);
    u = rt;
    vis[u] = 1;
    cal(u);
    for(int i = head[u]; ~i; i = e[i].nxt){
        int v = e[i].v;
        if(vis[v]) continue;
        rt = 0;
        snode = size[v];
        divide(v);
    }
}

int main(){
    //freopen("in.txt", "r", stdin);
    //freopen("out1.txt", "w", stdout);
    while(scanf("%d", &n) != EOF){
        int u, v, w;
        k = 3;
        init();
        memset(vis, 0, sizeof vis);
        for(int i = 1; i  < n; i++){
            scanf("%d %d %d", &u, &v, &w);
            w %= 3;
            add(u, v, w);
            add(v, u, w);
        }
        rt = ans  = 0;
        snode = n;
        maxson[0] = inf;
        divide(1);
        ans = ans * 2 + n;
        int temp = n * n;
        int g = __gcd(ans, temp);
        printf("%d/%d\n", ans/g, temp/g);

    }
}

++++