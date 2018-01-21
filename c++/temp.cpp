#include <bits/stdc++.h>
using namespace std;
#define LL long long 
const int maxn = 100010;
int a[maxn];

int main(){
    int n;
    while(cin>>n){
        int maxx = -1;
        for(int i = 0; i < n; i++){
            int x;
            cin>>x;
            maxx = max(maxx, x);
            a[x]++;
        }
        int temp = 0;
        for(int i = maxx; i >= 0; i--){
            if(a[i]) {
                if(a[i] & 1) temp = 1;
            } 
        }
        if(temp) cout<<"Conan\n";
        else cout<<"Agasa\n";
        
    }
}