#include <bits/stdc++.h>
using namespace std;
int main(){
    int t;
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    scanf("%d", &t);
    getchar();
    while(t--){
        string s;
        getline(cin, s);
        int n = s.length();
        stack<char> sta;
        int ok = 1;
        if(n & 1) ok = 0;
        for(int i = 0; i < n && ok; i++){
            char temp = s[i];
            if(temp == '(' || temp == '[') sta.push(temp);
            if(temp == ')'){
                if(sta.empty()){
                    ok = 0;
                    break;
                }
                char a = sta.top();
                sta.pop();
                if(a == '(') continue;
                else ok = 0;
            }
            if(temp == ']'){
                if(sta.empty()){
                    ok = 0;
                    break;
                }
                char a = sta.top();
                sta.pop();
                if(a == '[') continue;
                else ok = 0;
            }
        }
        if(!sta.empty()) ok = 0;
        if(ok) puts("Yes");
        else puts("No");
    }
    return 0;
}