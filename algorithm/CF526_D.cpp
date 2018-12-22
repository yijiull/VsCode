#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int MAXN = 3e5+10;

struct Edge{
    int v, w;
};
vector<Edge> e;

vector<int> p[MAXN];
int gas[MAXN];

void add(int u, int v, int w){
    e.push_back({v, w});
    p[u].push_back(e.size()-1);
    e.push_back({u, w});
    p[v].push_back(e.size()-1);
}
LL d[MAXN];
LL res = 0;
void dfs(int u, int f){
    LL m1 = 0, m2 = 0;
    for(int i = 0; i < p[u].size(); i++){
        Edge &temp = e[p[u][i]];
        if(temp.v == f) continue;
        dfs(temp.v, u);
        LL x = d[temp.v] - temp.w;
        if(x > m1){
            m2 = m1;
            m1 = x;
        }else if(x > m2){
            m2 = x;
        }
    }
    d[u] = max(m1, 0LL) + gas[u];
    res = max(res, m1 + m2 + gas[u]);
}

int main(){
    int n;
    cin>>n;
    for(int i = 1; i <= n; i++) cin>>gas[i];
    int u, v, w;
    for(int i = 1; i < n; i++){
        cin>>u>>v>>w;
        add(u, v, w);
    }
    dfs(1, 0);
    //for(int i = 1; i <= n; i++) cout<<d[i]<<endl;
    cout<<res<<endl;
}