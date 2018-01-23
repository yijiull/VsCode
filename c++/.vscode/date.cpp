#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1313;
const int  mod = 1<<30;
int main(){
    freopen("in.txt", "w", stdout);
    for(int k = 0; k < MAXN; k++){
        int n = rand() % 13 + 1;
        cout<<n<<endl;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                cout<<(rand() % mod) <<" ";
            }
            cout<<endl;
        }
        int m = 10;
        cout<<m<<endl;
        while(m--){
            int fg = rand() & 1;
            if(fg){
                cout<<"q ";
                int x1 = rand() % n + 1;
                int y1 = rand() % n + 1;
                int x2 = rand() % n + 1;
                int y2 = rand() % n + 1;
                if(x1 > x2) swap(x1, x2);
                if(y1 > y2) swap(y1, y2);
                printf("%d %d %d %d\n", x1, y1, x2, y2);
            }else{
                cout<<"c ";
                int x1 = rand() % n + 1;
                int y1 = rand() % n + 1;
                int v = rand() % mod;
                printf("%d %d %d\n", x1, y1, v);
            }
        }
    }
}