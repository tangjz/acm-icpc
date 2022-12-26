#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)2e3 + 1, mod = 998244353;
int t;
struct Poly {
    int deg, coeff[maxn];
    void read() {
        scanf("%d", &deg);
        for(int i = 0; i <= deg; ++i)
            scanf("%d", coeff + i);
    }
} A, B, C, D;
inline int mod_inv(int x) {
    return x <= 1 ? x : mod - (int)(mod / x * (LL)mod_inv(mod % x) % mod);
}
void poly_norm(Poly &A) {
    int ivs = mod_inv(A.coeff[A.deg]);
    for(int i = 0; i <= A.deg; ++i)
        A.coeff[i] = (LL)A.coeff[i] * ivs % mod;
}
void poly_dif(Poly A, Poly &B) { // B = A'
    if(!A.deg) {
        B.deg = -1;
        return;
    }
    B.deg = A.deg - 1;
    for(int i = 0; i <= B.deg; ++i)
        B.coeff[i] = (i + 1LL) * A.coeff[i + 1] % mod;
    poly_norm(B);
}
void poly_div(Poly A, Poly B, Poly &D, Poly &R) { // A = B D + R
    R = A;
    D.deg = A.deg - B.deg;
    int ivs = mod_inv(B.coeff[B.deg]);
    for(int i = R.deg; i >= B.deg; --i) {
        int prd = D.coeff[i - B.deg] = (LL)R.coeff[i] * ivs % mod;
        for(int j = 0; j <= B.deg; ++j)
            (R.coeff[i - j] = (R.coeff[i - j] - (LL)prd * B.coeff[B.deg - j]) % mod) < 0 && (R.coeff[i - j] += mod);
    }
    for( ; ~R.deg && !R.coeff[R.deg]; --R.deg);
}
void poly_gcd(Poly A, Poly B, Poly &R) { // R = gcd(A, B)
    R = B;
    while(A.deg != -1) {
        if(A.deg < R.deg)
            swap(A, R);
        poly_div(A, R, B, A);
    }
    poly_norm(R);
}
int main() {
    scanf("%d", &t);
    while(t--) {
        A.read();
        B = A;
        while(1) {
            poly_dif(B, C);
            poly_gcd(B, C, D);
            if(D.deg == 0)
                break;
            poly_div(B, D, B, C);
        }
        printf("%d\n", B.deg);
        for(int i = 1; B.deg != 0; ++i) {
            poly_div(A, B, A, D);
            poly_gcd(A, B, D);
            if(D.deg < B.deg) {
                poly_div(B, D, C, B);
                printf("%d %d\n", C.coeff[0] ? mod - C.coeff[0] : 0, i);
                B = D;
            }
        }
    }
    return 0;
}
