#include <bits/stdc++.h>
using namespace std;
const int MAXN = 110;
int a[MAXN];


int main(){
    int n;
    cin>>n;
    for(int i = 1; i <= n; i++) cin>>a[i];
    int res = 1e9;
    for(int i = 1; i <= n; i++){
        int temp = 0;
        for(int j = 1; j <= n; j++){
            if(j >= i){
                temp += (j - 1) * 4 * a[j];
            }else{
                temp += (i - 1) * 4 * a[j];
            }
        }
        res = min(res, temp);
    }
    cout<<res<<endl;

}