#include <bits/stdc++.h>
using namespace std;

inline int _random(){
    static int seed=703; //seed可以随便取
    return seed=int(seed*48271LL%2147483647);
}

const int MAXN = 13;

int main(){
    for(int i = 0; i < MAXN; i++) cout<<_random()<<endl;
}