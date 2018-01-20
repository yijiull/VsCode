#include <bits/stdc++.h>
using namespace std;
const int inf = 0x3f3f3f3f;
const int maxv = 410;
const int maxe = maxv * maxv;
struct Edge{
    int u, v, cap, flow, cost;
    int nxt;
    Edge(int u = 0, int v = 0, int cap = 0, int flow = 0, int cost = 0, int nxt = 0) : 
        u(u), v(v), cap(cap), flow(flow), cost(cost), nxt(nxt) {}
}e[maxe << 1];
int head[maxv];
int cnt;
int tr;
void init(){
    cnt = 0;
    tr = 0;
    memset(head, -1, sizeof head);
}
void add(int u, int v, int cap, int cost){
    e[cnt] = Edge(u, v, cap, 0, cost, head[u]);
    head[u] = cnt++;
    e[cnt] = Edge(v, u, 0, 0, -cost, head[v]);
    head[v] = cnt++;
}


int N;
int d[maxv], p[maxv], a[maxv], inq[maxv];
bool BellmanFord(int s, int t, int &flow, int &cost){
    for(int i = 0; i < N; i++) d[i] = inf;
    memset(inq, 0, sizeof inq);
    d[s] = 0, a[s] = inf, p[s] = 0, inq[s] = 1;
    queue<int> q;
    q.push(s);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        inq[u] = 0;
        for(int i = head[u]; ~i; i = e[i].nxt){
            Edge &tp = e[i];
            if(tp.cap > tp.flow && d[tp.v] > d[u] + tp.cost){
                d[tp.v] = d[u] + tp.cost;
                p[tp.v] = i;
                a[tp.v] = min(a[u], tp.cap - tp.flow);
                if(!inq[tp.v]){
                    q.push(tp.v);
                    inq[tp.v] = 1;
                }
            }
        }
    }
    if(d[t] == inf) return false;
    flow += a[t];
    cost += a[t] * d[t];
    int u = t;
    while(u != s){
        e[p[u]].flow += a[t];
        e[p[u] ^ 1].flow -= a[t];
        u = e[p[u]].u;
    }
    return true;
}


int MCMF(int s, int t){
    int flow = 0, cost = 0;
    while(BellmanFord(s, t, flow, cost));
    return cost;
}

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        init();
        int n, m;
        scanf("%d %d", &n, &m);
        int u, v, w;
        for(int i = 0; i < m; i++){
            scanf("%d %d %d", &u, &v, &w);
            add(u, v + n, 1, w);
        }
        int S = 0, T = n * 2 + 1;
        N = 2 * n + 2;
        for(int i = 1; i <= n; i++){
            add(S, i, 1, 0);
            add(i + n, T, 1, 0);
        }
        printf("%d\n", MCMF(S, T));
    }
    return 0;
}