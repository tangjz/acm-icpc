#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

const int maxn = (int)1e2 + 1, maxd = 11, mod = (int)1e9 + 7;

int n;

inline void mergeSol(int &ret, int const &lft, int const &rht) {
    if(lft == -1 || rht == -1)
        return;
    if(ret == -1)
        ret = 0;
    ret = (ret + (i64)lft * rht) % mod;
}

struct Matrix {
    int data[maxn][maxn];
    void assignDiag(int val = -1) {
        for(int i = 0; i < n; ++i) {
            memset(data[i], -1, n * sizeof(int));
            data[i][i] = val;
        }
    }
    void assignMul(Matrix const &lft, Matrix const &rht) {
        assignDiag();
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j) {
                if(lft.data[i][j] == -1)
                    continue;
                for(int k = 0; k < n; ++k)
                    mergeSol(data[i][k], lft.data[i][j], rht.data[j][k]);
            }
    }
} ;

void solve() {
    int m, q, A = 0, B = 1, C = 2;
    static Matrix f[3];
    scanf("%d%d%d", &n, &m, &q);
    int mx = 0;
    for( ; (1 << mx) <= q; ++mx);
    f[C].assignDiag();
    while(m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        --u;
        --v;
        mergeSol(f[C].data[u][v], 1, 1);
        mergeSol(f[C].data[v][u], 1, 1);
    }
    f[A].assignDiag(1);
    for(int i = 0; q > 0; ++i, q >>= 1) {
        if(q & 1) {
            f[B].assignMul(f[A], f[C]);
            swap(A, B);
        }
        if(i + 1 < mx) {
            f[B].assignMul(f[C], f[C]);
            swap(B, C);
        }
    }
    for(int i = 0; i + 1 < n; ++i)
        for(int j = i + 1; j < n; ++j)
            printf("%d%c", f[A].data[i][j], " \n"[j == n - 1]);
}

int main() {
    int T = 1;
    for(int Case = 1; Case <= T; ++Case) {
        solve();
    }
    return 0;
}
