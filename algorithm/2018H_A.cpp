/**
 * 题目：https://codejam.withgoogle.com/codejam/contest/3324486/dashboard
 * 将字符串送进trie树，然后统计前缀，注意短的前缀确定的集合肯定包含了那些长的前缀的情况。
 * 除了前缀，后面的位置可以随意取。
 * O(p*n)
 */
#include <bits/stdc++.h>
using namespace std;
const int MAXSIGMA = 2;
struct Node{
    Node *p[MAXSIGMA];
    int v;
};
map<char, int> mp{
    {'B', 0},
    {'R', 1}
};

Node* newNode(){
    Node *res = new Node();
    res->v = 0;
    for(int i = 0; i < MAXSIGMA; i++){
        res->p[i] = nullptr;
    }
    return res;
};

void insert(Node *rt, string s){
    int n = s.length();
    for(int i = 0; i < n; i++){
        int c = mp[s[i]];       
        if(rt->p[c] == nullptr){
            rt->p[c] = newNode();
        }
        rt = rt->p[c];
    }
    rt->v = n;
}
map<int, int> cnt;//用来计数

int solve(Node *rt){
    for(int i = 0; i < MAXSIGMA; i++){
        if(rt->p[i]){
            if(rt->p[i]->v != 0){
                cnt[rt->p[i]->v]++;
            }else{
                solve(rt->p[i]);
            }
        }
    }
}

void mydel(Node *rt){
    for(int i = 0; i < MAXSIGMA; i++){
        if(rt->p[i]){
            mydel(rt->p[i]);
        }
    }
    delete rt;
}


int main(){
    //freopen("small.in", "r", stdin);
    //freopen("out.txt", "w", stdout);
    fstream in, out;
    in.open("large.in", ios::in);
    out.open("out.txt", ios::out);
    int t;
    in>>t;
    int n, m;
    for(int k = 1; k <= t; k++){
        in>>n>>m;
        cnt.clear();
        Node *trie = newNode();
        string s;
        for(int i = 0; i < m; i++){
            in>>s;
            auto rt = trie;
            insert(rt, s);
        }
        solve(trie);
        long long res = 0;
        for(auto c : cnt){
            res += (1LL << (n - c.first)) * c.second;
        }
        out<<"Case #"<<k<<": "<<(1LL << n) - res<<endl;
        mydel(trie);

    }
}