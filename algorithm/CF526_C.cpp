#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;
string s;
typedef long long LL;
int main(){
    cin>>s;
    vector<int> v;
    int n = s.length();
    for(int i = 0; i < n; i++){
        if(s[i] == 'a'){
            int temp = 0;
            while(i < n && s[i] != 'b'){
                if(s[i] == 'a') temp++;
                i++;
            }
            v.push_back(temp);
        }
    }
    if(v.size() >= 1){
        LL res = v[0];
        for(int i = 1; i < v.size(); i++){
            res = res + res * v[i] % MOD + v[i];
        }
        cout<<res%MOD<<endl;
    }else{
        cout<<0<<endl;
    }
}