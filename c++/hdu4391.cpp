// lazy 分块
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010;

int c[maxn], ov[maxn];
map<int, int> mp[maxn];
int n, m, SZ;

void pushdown(int id){
    if(ov[id] != -1){
        for(int i = id * SZ; i < min((id + 1) * SZ, n); i++) c[i] = ov[id];
        mp[id].clear();
        mp[id][ov[id]] = min((id + 1) * SZ, n) - id * SZ;
        ov[id] = -1;
    }
}

void update(int l, int r, int z){
    int pl = l / SZ, pr = r / SZ;
    pushdown(pl);
    for(int i = l; i <= min(r, (pl + 1) * SZ - 1); i++){
        mp[pl][c[i]]--;
        c[i] = z;
        mp[pl][z]++;
    }
    if(pl != pr){
        pushdown(pr);
        for(int i = pr * SZ; i <= r; i++){
            mp[pr][c[i]]--;
            c[i] = z;
            mp[pr][z]++;
        } 
    }
    for(int i = pl + 1; i < pr; i++) ov[i] = z;
}
int query(int l, int r, int z){
    int res = 0;
    int pl = l / SZ, pr = r / SZ;
    pushdown(pl);
    for(int i = l; i <= min(r, (pl + 1) * SZ - 1); i++) if(c[i] == z) res++;
    if(pl != pr) {
        pushdown(pr);
        for(int i = pr * SZ; i <= r; i++) if(c[i] == z) res++;
    }
    for(int i = pl + 1; i < pr; i++){
        if(ov[i] == -1){
            if(mp[i].find(z) != mp[i].end()) res += mp[i][z];
        }else if(ov[i] == z) res += min((i + 1) * SZ, n) - i * SZ;
    } 
    return res;
}
int main(){
    while(scanf("%d %d", &n, &m) != EOF){
        SZ = sqrt(n * 1.0);
        memset(ov, -1, sizeof ov);
        for(int i = 0; i < n; i++) mp[i].clear();
        for(int i = 0; i < n; i++){
            scanf("%d", &c[i]);
            mp[i / SZ][c[i]]++; 
        }
        while(m--){
            int op, l, r, z;
            scanf("%d %d %d %d", &op, &l, &r, &z);
            if(op == 1){
                update(l, r, z);
            }else{
                printf("%d\n", query(l, r, z));
            }
        }
    }
    return 0;
}