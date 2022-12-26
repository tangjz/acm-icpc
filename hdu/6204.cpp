#include <bits/stdc++.h>
using namespace std;
typedef long double DB;
typedef unsigned long long ULL;
const int maxn = 401, maxm = 13335;
const DB pi = acos(-1.0), eps = 1e-12;
int t, n, mod0, mod1, tot, pos[maxn][maxn], f[maxn];
vector<pair<int, int> > e[maxm];
int solve(int mod) {
    int ans = 0;
    for(int v = 0; v < tot; ++v) {
        int mx = 0;
        for(vector<pair<int, int> >::iterator it = e[v].begin(); it != e[v].end(); ++it) {
            int i = it -> first, j = it -> second, k = n - i - j;
            mx = max(mx, max(i, max(j, k)));
        }
        f[1] = 1;
        for(int i = 2; i <= mx; ++i) {
            int tim = 0;
            ULL val = 0;
            for(int k = 1; k < i - k; ++k)
                if(pos[k][i - k] < v) {
                    val += ((ULL)f[k] * f[i - k]) << 1;
                    (tim += 2) == 18 && (tim = 0, val %= mod);
                }
            if(!(i & 1) && pos[i >> 1][i >> 1] < v) {
                val += (ULL)f[i >> 1] * f[i >> 1];
                (++tim) == 18 && (tim = 0, val %= mod);
            }
            f[i] = tim ? val % mod : val;
        }
        for(vector<pair<int, int> >::iterator it = e[v].begin(); it != e[v].end(); ++it) {
            int i = it -> first, j = it -> second, k = n - i - j;
            ans = (ans + (ULL)f[i] * f[j] % mod * f[k] % mod * k) % mod;
        }
    }
    return ans;
}
DB Sin[maxn], seq[maxm];
inline int sgn(DB x) {
    return (x > eps) - (x < -eps);
}
bool cmp(DB const &x, DB const &y) {
    return sgn(x - y) < 0;
}
bool equ(DB const &x, DB const &y) {
    return !sgn(x - y);
}
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d%d", &n, &mod0, &mod1);
        for(int i = 0; i <= n; ++i) {
            int fz = i << 1, fm = n;
            for( ; !(fz & 1) && !(fm & 1); fz >>= 1, fm >>= 1);
            Sin[i] = sin(pi * fz / fm);
        }
        tot = 0;
        for(int i = 1; i <= n; ++i)
            for(int j = i; j <= n - i - j; ++j)
                seq[tot++] = Sin[i] + Sin[j] - Sin[i + j];
        sort(seq, seq + tot);
        tot = unique(seq, seq + tot, equ) - seq;
        for(int i = 0; i < tot; ++i)
            vector<pair<int, int> >().swap(e[i]);
        for(int i = 1; i < n; ++i)
            for(int j = 1; i + j < n; ++j) {
                pos[i][j] = lower_bound(seq, seq + tot, Sin[i] + Sin[j] - Sin[i + j], cmp) - seq;
                e[pos[i][j]].push_back(make_pair(i, j));
            }
        printf("%llu\n", (ULL)solve(mod0) * solve(mod1));
    }
    return 0;
}
