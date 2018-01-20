#include <bits/stdc++.h>
using namespace std;
#define LL long long
map<int, int> cnt;

int main(){
    LL n, k;
    ios::sync_with_stdio(0);
    while(cin>>n>>k){
        int m = 0;
        cnt.clear();
        for(int i = 0; i <= 63; i++) if((n >> i) & 1) {cnt[i]++; m++;}
        if(m > k) cout<<"No\n";
        else{
            for(int i = 63; i >= -63; i--){
                if(cnt[i] + m <= k){
                    m += cnt[i];
                    cnt[i-1] += cnt[i] * 2;
                    cnt[i] = 0;
                }else {
                    break;
                }
            }
            cout<<"Yes"<<endl;
            multiset<int> ms;
            for(int i = 63; i >= -63; i--) for(int j = 0; j < cnt[i]; j++) ms.insert(i);
            while(ms.size() < k){
                int u = *ms.begin();
                ms.erase(ms.begin());
                ms.insert(u-1);
                ms.insert(u-1);
            }
            for(auto it = ms.rbegin(); it != ms.rend(); it++) cout<<*it<<" ";
            cout<<endl;
        }
    }
}