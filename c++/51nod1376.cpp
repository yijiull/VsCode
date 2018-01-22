//树状数组 dp
//求LIS的数量
#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
const int maxn = 50010;
struct Node{
    int len, cnt;
    Node(int len = 0, int cnt = 0) : len(len), cnt(cnt){}
    Node operator + (const Node &t) const{
        if(len < t.len) return t;
        if(len > t.len) return (*this);
        return Node(len, (cnt + t.cnt) % mod);
    }
};
struct Info{
    int x, pos;
    bool operator < (const Info &temp) const{
        if(x == temp.x) return pos > temp.pos;
        return x < temp.x;
    }
};

bool cmp(Info &a, Info &b){
    if(a.x == b.x) return a.pos > b.pos;
    return a.x < b.x;
}
Node c[maxn];
Info a[maxn];

int n;
void add(int i, Node v){
    for(; i <= n; i += i & -i) c[i] = c[i] + v;
}

Node sum(int i){
    Node res;
    for(; i; i -= i & -i) res = res + c[i];
    return res;
}

int main(){
    while(scanf("%d", &n) != EOF){
        for(int i = 0; i < n; i++){
            scanf("%d", &a[i].x);
            a[i].pos = i + 1;
        }
        sort(a, a + n);
        Node ans;
        for(int i = 0; i < n; i++){
            Node temp = sum(a[i].pos);
            if(++temp.len == 1) temp.cnt = 1;
            ans = ans + temp;
            add(a[i].pos, temp);
        }
        cout<<ans.cnt<<endl;

    }
}