#include <bits/stdc++.h>
#include <vector>
using namespace std;
const int maxn = 10010;
#define LL long long 

int bit[110];


int main(){
    LL x, k;
    while(cin>>x>>k){
        memset(bit, 0, sizeof(bit));
        int cnt = 0;
        LL temp = x;
        int pos = 0;
        while(temp) {
            if(temp &1) cnt++, bit[pos] = 1;
            temp>>=1 ;
            pos++;
        }
        cout<<"bits  = " <<pos<<endl; 
        for(int i = pos - 1; i >= 0; i-- ) cout<<bit[i]<<" ";
        cout<<endl;
        vector<int> v;
        if(k< cnt)  puts("No");
        else if( k == cnt){
            LL res = 0;
            temp = x;
            while(temp){
                if(temp & 1) v.push_back(res);
                res++;
                temp >>= 1;
            }
            puts("Yes");
            for(int i = v.size() - 1; i > 0; i--) cout<<v[i]<<" ";
            cout<<v[0] <<endl;
        }else{
            int cd = k - cnt;
            int cur = 0;
            int ty = 0;
            for(int i = pos-1; i >= 0; i--) if(bit[i]){
                cur++;
                ty++;
                int j = i - 1;
                while(bit[j] == 0) {
                    j--;
                    cur<<=1;
                    if((cur<<1) > k - (cnt - ty))  break;
                }
                if((cur << 1) > (k - (cnt - ty))) {
                    for(int i  = 0; i < cur; i++) v.push_back(j);
                    int need = k - cur;
                    cnt -= ty;
                    
                    for(int i = 0; i < j; i++) if(bit[i] == 1){
                        int tu = log2(need - cnt + 1) ;
                    }




                    break;
                }



            }
        }
    }
}