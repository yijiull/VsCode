//umax是当前最大值， lmax是当前次大值
//分析可知，当新进入的值大于最大值时，只有移除本身使得recod减少1
//        当新进入的值介于最大值和次大值之间时，移除最大值可使得recod增加1
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
int a[maxn];


int main(){
    int n;
    ios::sync_with_stdio(0);
    while(cin>>n){
        int umax = -1e9, lmax = -1e9;
        for(int i = 1; i <= n; i++){
            int x;
            cin>>x;
            if(x > umax) {
                lmax = umax;
                umax = x;
                a[umax] = -1;
            }else if(x > lmax){
                a[umax]++;
                lmax = x;
            }
        }
        int res = 1;
        for(int i = 1; i <= umax; i++){
            if(a[res] < a[i]){
                res = i;
            }
        }
        cout<<res<<endl;
    }
}