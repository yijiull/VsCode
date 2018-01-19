#include <iostream>
#include <complex>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int maxn = 200010;
const double pi = acos(-1.0);
complex<double> omega[maxn], inverse[maxn];

void init(int n){
    for(int i = 0; i < n; i++){
        omega[i] = complex<double>(cos(2 * pi / n * i), sin(2 * pi / n * i));
        inverse[i] = conj(omega[i]);
    }
}
void transform(complex<double> *a, int n, complex<double> *omega){
    int k = 0;
    while((1 << k) < n) k++;
    for(int i = 0; i < n; i++){
        int t = 0;
        for(int j = 0; j < k; j++) if(i & (1 << j)) t |= (1 << (k - j - 1));
        if(i < t) swap(a[i], a[t]);
    }
    for(int l = 2;  l <= n; l *= 2){
        int m = l / 2;
        for(complex<double> *p = a; p != a + n; p += l){
            for(int i = 0; i < m; i++){
                complex<double> t = omega[n / l * i] * p[m + i];
                p[m + i] = p[i] - t;
                p[i] += t;
            }
        }
    }
}
void dft(complex<double> *a, int n){
    transform(a, n, omega);
}
void idft(complex<double> *a, int n){
    transform(a, n, inverse);
    for(int i = 0; i < n; i++) a[i] /= n;
}

void mul(int *a, int n1, int *b, int n2, int *res){
    int n = 1;
    while(n < n1 + n2) n <<= 1;
    complex<double> c1[maxn], c2[maxn];
    for(int i = 0; i < n1; i++) c1[i].real(a[i]);
    for(int i = 0; i < n2; i++) c2[i].real(b[i]);
    init(n);
    dft(c1, n); dft(c2, n);
    for(int i = 0; i < n; i++) c1[i] *= c2[i];
    idft(c1, n);
    for(int i = 0; i < n1 + n2 - 1; i++) res[i] = (int)(floor(c1[i].real() + 0.5));
}
char s1[maxn], s2[maxn];
int a[maxn], b[maxn], res[maxn];

void in(){
    freopen("in.txt", "w", stdout);
    for(int i= 0; i < 100; i++){
        cout<<rand() % 131313 <<endl;
    }
}

int main(){
   // freopen("in.txt", "r", stdin);
   // freopen("out.txt", "w", stdout);
    while(scanf("%s %s", s1, s2) != EOF){
        memset(res, 0, sizeof res);
        int n1 = strlen(s1), n2 = strlen(s2);
        for(int i = 0; i < n1; i++) a[i] = s1[n1 - i - 1] - '0';
        for(int i = 0; i < n2; i++) b[i]  =s2[n2 - i - 1] - '0';
        mul(a, n1, b, n2, res);
        int m = n1 + n2 -1;
        for(int i = 0; i < m; i++) res[i + 1] += res[i] / 10, res[i] %= 10;
        if(res[m]) m++;
        while(m >= 1 && !res[m - 1]) m--;
        for(int i = m - 1; i >= 0; i--) printf("%d", res[i]);
        if(m == 0) printf("0");
        puts("");
    }
}