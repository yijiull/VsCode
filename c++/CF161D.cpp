#include <bits/stdc++.h>
using namespace std;
const int maxn = 50010;
const int maxd = 510;
int dp[maxn][maxd];
struct Edge{
    int v, nxt;
    Edge(int v = 0, int nxt = 0) : v(v), nxt(nxt){}
}e[maxn<<1];
int head[maxn], cnt;
void init(){
    cnt = 0;
    memset(head, -1, sizeof head);
}
void add(int u, int v){
    e[cnt] = Edge(v, head[u]);
    head[u] = cnt++;
}

int n, k;

void dp1(int u, int f){
    dp[u][0] = 1;
    for(int i = 1; i <= k; i++) dp[u][i] = 0;
    for(int i = head[u]; ~i; i = e[i].nxt){
        int v = e[i].v;
        if(v == f) continue;
        dp1(v, u);
        for(int i = 1; i <= k; i++) dp[u][i] += dp[v][i - 1];
    }
}
void dp2(int u, int f){
    for(int i = head[u]; ~i; i = e[i].nxt){
        int v = e[i].v;
        if(v == f) continue;
        for(int i = k; i >= 1; i--){
            dp[v][i] += dp[u][i - 1];
            if(i > 1) dp[v][i] -= dp[v][i - 2];
        }
        dp2(v, u);
    }
}

int main(){
    while(scanf("%d %d", &n, &k) != EOF){
        init();
        int u, v;
        for(int i = 1; i < n; i++){
            scanf("%d %d", &u, &v);
            add(u, v); add(v, u);
        }
        dp1(1, 0);
        dp2(1, 0);
        long long ans = 0;
        for(int i = 1; i <= n; i++){
            ans += dp[i][k];
        }
        printf("%lld\n", ans / 2);
    }
}