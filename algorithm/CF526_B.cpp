#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1010;
int a[MAXN];
typedef long long LL;
int n;
LL s;
int main(){
    cin>>n>>s;
    for(int i = 0; i < n; i++){
        cin>>a[i];
    }
    sort(a, a+n);
    LL res = 0;
    for(int i = 0; i < n; i++) res += a[i] - a[0];
    if(res >= s){
        cout<<a[0]<<endl;
    }else{
        LL temp = s - res;
        cout<< max(a[0] - (temp / n + (temp % n == 0 ? 0 : 1)), -1LL) << endl;
    }


}