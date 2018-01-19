#include <bits/stdc++.h>
using namespace std;
char pre[30], in[30];
int lc[30], rc[30];
int cnt;
char tr[30];

int build(int s1, int e1, int s2, int e2){
    if(e1 <= s1) return -1;
    char rt = pre[s1];
    int i = s2;
    int cur = cnt++;
    while(in[i] != rt) i++;
    int ls = i - s2;
    lc[cur] = build(s1 + 1, s1 + 1 + ls, s2, s2 + ls);
    rc[cur] = build(s1 + 1 + ls, e1, s2 + ls + 1, e2);
    tr[cur] = rt;
    return cur;
}

void print(int cur){
    if(lc[cur] != -1) print(lc[cur]);
    if(rc[cur] != -1) print(rc[cur]);
    cout<<tr[cur];
}

int main(){
    while(cin>>pre>>in){
        memset(lc, -1, sizeof lc);
        memset(rc, -1, sizeof rc);
        int n = strlen(pre);
        cnt=  0;
        int rt = build(0, n, 0, n);
        print(0);
        cout<<endl;
    }
}