#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = (int)1e9 + 7, maxd = 101, maxe = 15;
int mod_pow(int x, int k) {
    int ret = 1;
    for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
        if(k & 1)
            ret = (LL)ret * x % mod;
    return ret;
}
int bin[maxe][maxe], coeff[maxe][maxe];
int mod_pow_sum(int x, int k) {
    int ret = 0;
    for(int i = k + 1; i >= 0; --i)
        ret = ((LL)ret * x + coeff[k][i]) % mod;
    return ret;
}
int f[maxd][maxe][maxe], tim, vis[maxd][maxe][maxe];
int solve(int p, int q, int n, int a, int b, int c, int dep) {
    int &ret = f[dep][p][q];
    if(vis[dep][p][q] == tim)
        return ret;
    vis[dep][p][q] = tim;
    if(!a) {
        ret = (LL)mod_pow_sum(n, p) * mod_pow(b / c, q) % mod;
    } else if(a >= c || b >= c) {
        ret = 0;
        for(int i = 0, rem = q; i <= q; ++i, --rem)
            for(int j = 0, k = rem; k >= 0; ++j, --k)
                ret = (ret + (LL)bin[q][i] * bin[rem][j] % mod *
                    mod_pow(a / c, i) % mod * mod_pow(b / c, j) % mod *
                    solve(p + i, k, n, a % c, b % c, c, dep + 1)) % mod;
    } else {
        LL m = ((LL)a * n + b) / c;
        ret = (LL)mod_pow_sum(n, p) * mod_pow(m, q) % mod;
        for(int i = 0; i < q; ++i)
            for(int j = 0; j <= p + 1; ++j)
                ret = (ret - (LL)bin[q][i] * coeff[p][j] % mod *
                    solve(i, j, m - 1, c, c - b - 1, a, dep + 1)) % mod;
        ret = (ret + mod) % mod;
    }
    return ret;
}
int main() {
    for(int i = 0; i < maxe; ++i) {
        bin[i][0] = bin[i][i] = 1;
        for(int j = 1; j < i; ++j)
            bin[i][j] = (bin[i - 1][j - 1] + bin[i - 1][j]) % mod;
    }
    coeff[0][0] = coeff[0][1] = 1;
    for(int i = 1; i < maxe - 1; ++i) {
        for(int j = 0; j <= i + 1; ++j)
            coeff[i][j] = bin[i + 1][j];
        for(int j = 0; j < i; ++j)
            for(int k = 0; k <= j + 1; ++k)
                coeff[i][k] = (coeff[i][k] - (LL)bin[i + 1][j] * coeff[j][k]) % mod;
        int ivs = mod_pow(i + 1, mod - 2);
        for(int j = 0; j <= i + 1; ++j)
            coeff[i][j] = (LL)(coeff[i][j] + mod) * ivs % mod;
    }
    int T;
    scanf("%d", &T);
    while(T--) {
        int n, a, b, c, p, q;
        scanf("%d%d%d%d%d%d", &n, &a, &b, &c, &p, &q);
        ++tim;
        printf("%d\n", solve(p, q, n, a, b, c, 0));
    }
    return 0;
}