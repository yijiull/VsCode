#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int maxn = 100010;
#define LL long long 

int bit[110];

int pri[maxn];
int cnt;
void init(){
    memset(pri, 0, sizeof(pri));
    for(LL i = 2; i < maxn; i++){
        if(!pri[i]) {
            pri[cnt++] = i;
            for(LL j = i * i; j < maxn; j += i) pri[j] = 1;
        }
    }
}

int main(){
    int n, m;
    while(cin>>n>>m){
        cnt = 0;
        init();
        //for(int i = 0; i < 20; i++ )cout<<pri[i]<<endl;
        int i = 0;
        while(pri[i] < n-1) i++;
        int temp = pri[i];
        cout<<temp<<" "<<temp<<endl;
        for(int i = 1; i < n - 1; i++) cout<<i<<" "<<i+1<<" "<<1<<endl, temp--;
        cout<<n-1<<" "<<n<<" "<<temp<<endl;
        int c =0;
        m -= n-1;
        for(int i = 1; i <= n && c < m; i++){
            for(int j = i + 1; j <= n && c < m; j++) if(i+1 != j && i != j) {
                cout<<i<<" "<<j<<" "<<1000000000<<endl;
                c++;
            }
        }
    }
}