#include <bits/stdc++.h>
using namespace std;

int main(){
    int k;
    int kase= 0;
   // freopen("in.txt", "r", stdin);
   // freopen("out.txt", "w", stdout);
    while(cin >> k){
        if(k == 0) break;
        for(int i = 0 ; i < k; i++){
            char s[3];
            cin>>s;
        }
        char s[1010];
        cin>>s;
        int m;
        cin>>m;
        cout<<"S-Tree #"<<++kase<<":\n";
        while(m--){
            char p[20];
            cin>>p;
            int len = strlen(p);
            int ans = 0;
            for(int i = len- 1; i >= 0; i--){
                ans = ans + ((1<<(len - 1 - i) )* (p[i] - '0'));
            }
            cout<<s[ans];
        }
        cout<<"\n\n";
    }
}