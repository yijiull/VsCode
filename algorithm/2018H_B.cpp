/**
 * 题目：https://codejam.withgoogle.com/codejam/contest/3324486/dashboard#s=p1
 * 墙只能从两边倒，而我们需要选连续的一半的墙使得value最大即可，
 * 其实我们只要选了第一块x，使得x两侧的墙中，不打算涂的数量不少于要涂的数量即可,这样我们总能保证在墙倒之前给它涂色
 * 于是转化为求最大连续子串和。
 * O(n)
 */
#include <bits/stdc++.h>
using namespace std;

int main(){
    fstream in, out;
    in.open("large.in", ios::in);
    out.open("out.txt", ios::out);
    int t;
    in>>t;
    int n;
    string s;
    for(int k = 1; k <= t; k++){
        in>>n;
        in>>s;
        int res = 0;
        int m = (n + 1) / 2;
        int j = 0;
        for(; j < m; j++){
            res += s[j] - '0';
        }
        int ans = res;
        for(; j < n; j++){
            res = res - s[j-m]  + s[j];
            ans = max(ans, res);
        }
        out<<"Case #"<<k<<": "<<ans<<endl;
    }
}