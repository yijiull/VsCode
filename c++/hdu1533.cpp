//费用流初探
#include <iostream>
#include <queue>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
const int inf = 0x3f3f3f3f;
const int maxn = 110;
char gra[maxn][maxn];

const int maxv =  210;
const int maxe = 210 * 210;
struct Edge{
    int u, v, cap, flow, cost;
    int nxt;
    Edge(int u = 0, int v = 0, int cap = 0, int flow = 0, int cost = 0, int nxt = 0) : u(u), v(v), cap(cap), flow(flow), cost(cost), nxt(nxt) {}
}e[maxe << 1];
int head[maxv];
int cnt = 0;
void init(){
    memset(head, -1, sizeof(head));
    cnt = 0;
}
void add(int u, int v, int cap, int flow, int cost){
    e[cnt] = Edge(u, v, cap, flow, cost, head[u]);
    head[u] = cnt++;
    e[cnt] = Edge(v, u, 0, flow, -cost, head[v]);
    head[v] = cnt++;
}
int mx[maxv], my[maxv], hx[maxv], hy[maxv];

int s, t, N;
int d[maxv], p[maxv], inq[maxv], a[maxv];
bool BellmandFord(int s, int t, int &flow, int &cost){
    for(int i = 0; i < N; i++) d[i] = inf;
    memset(inq, 0, sizeof inq);
    d[s] = 0; inq[s] = 1; p[s] = 0; a[s] = inf;
    queue<int> q;
    q.push(s);
    while(!q.empty()){
        int u = q.front(); q.pop();
        inq[u] = 0;
        for(int i = head[u]; ~i; i = e[i].nxt){
            Edge &tp = e[i];
            if(tp.cap > tp.flow && d[tp.v] > d[u] + tp.cost){
                d[tp.v] = d[u] + tp.cost;
                p[tp.v] = i;
                a[tp.v] = min(a[u], tp.cap - tp.flow);
                if(!inq[tp.v]) {
                    q.push(tp.v);
                    inq[tp.v] = 1;
                }
            }
        }
    }
    if(d[t] == inf) return false;
    flow += a[t];
    cost += d[t] * a[t];
    int u = t;
    while(u != s){
        e[p[u]].flow += a[t];
        e[p[u] ^ 1].flow -= a[t];
        u = e[p[u]].u;
    }
    return true;
}
int MCMF(){
    int flow = 0, cost = 0;
    while(BellmandFord(s, t, flow, cost)) ;
    return cost;
}

int main(){
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    int n, m;
    while(scanf("%d %d", &n, &m) && (n || m)){
        int cth = 0, ctm = 0;

        init();
        for(int i = 0; i < n; i++) {
            scanf("%s", gra[i]);
            for(int j = 0; j < m; j++){
                if(gra[i][j] == 'H'){
                    hx[cth] = i;
                    hy[cth++] = j;
                }
                if(gra[i][j] == 'm'){
                    mx[ctm] = i;
                    my[ctm++] = j;
                }
            }
        }
        for(int i = 0; i < cth; i++){
            for(int j = 0; j < ctm; j++){
                int dis = abs(hx[i] - mx[j]) + abs(hy[i] - my[j]);
                add(i, cth + j, 1, 0, dis);
            }
        }
        s = cth + ctm;
        t = s + 1;
        N = t + 1;
        for(int i = 0; i < cth; i++){
            add(s, i, 1, 0, 0);
        }
        for(int i = 0; i < ctm; i++){
            add(cth + i, t, 1, 0, 0);
        }
        int ans = MCMF();
        printf("%d\n", ans);
    }
    return 0;
}
