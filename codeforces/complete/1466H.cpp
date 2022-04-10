#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

const int maxn = 41, maxm = 11, maxs = 1441, mod = (int)1e9 + 7;

int n, perm[maxn], ctr[maxn];
int m, idx[maxm], ofs[maxm], dp[maxm][maxn][maxn][maxs];
int fct[maxn], bin[maxn][maxn], pw[maxn][maxn];

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%d", perm + i);
    for(int i = 1; i <= n; ++i) {
        if(!perm[i])
            continue;
        int c = 0;
        for(int j = i; perm[j]; ++c) {
            int &k = perm[j];
            j = k;
            k = 0;
        }
        ++ctr[c];
    }
    ofs[0] = 1;
    for(int i = 1; i <= n; ++i) {
        if(!ctr[i])
            continue;
        idx[m++] = i;
        ofs[m] = ofs[m - 1] * (ctr[i] + 1);
    }
    assert(m < maxm && ofs[m] < maxs);
    
    fct[0] = bin[0][0] = 1;
    for(int i = 1; i <= n; ++i) {
        fct[i] = (i64)fct[i - 1] * i % mod;
        bin[i][0] = bin[i][i] = 1;
        for(int j = 1; j < i; ++j)
            bin[i][j] = (bin[i - 1][j - 1] + bin[i - 1][j]) % mod;
    }
    for(int i = 0; i < n; ++i) {
        pw[i][1] = 0;
        for(int j = 0; j <= i; ++j)
            pw[i][1] = (pw[i][1] + (i64)bin[i][j] * fct[j] % mod * fct[n - 1 - j]) % mod;
        for(int j = 2; j <= n - i; ++j)
            pw[i][j] = (i64)pw[i][j - 1] * pw[i][1] % mod;
    }
    
    for(int i = 0; i < m; ++i)
        for(int j = 1, msk = 0, ways = 1; j <= ctr[idx[i]]; ++j) {
            msk += ofs[i];
            ways = (i64)ways * pw[0][idx[i]] % mod;
            dp[i][0][0][msk] = ways;
        }
    
    for(int i = 1; i < ofs[m]; ++i) {
        int sum = 0;
        static int cur[maxm];
        for(int j = 0, rem = i; j < m; rem /= ctr[idx[j++]] + 1) {
            cur[j] = rem % (ctr[idx[j]] + 1);
            sum += cur[j] * idx[j];
        }
        for(int j = 0; j < m; ++j)
            for(int u = 0; u < n; ++u)
                for(int v = u + !!u; v < n; ++v) {
                    if(!dp[j][u][v][i])
                        continue;
                    for(int jj = 0; jj < m; ++jj)
                        for(int k = 1, msk = i, ways1 = 1, ways2 = 1; cur[jj] + k <= ctr[idx[jj]]; ++k) {
                            msk += ofs[jj];
                            int adt = (i64)dp[j][u][v][i] * bin[cur[jj] + k][k] % mod;
                            ways1 = (i64)ways1 * (pw[sum][idx[jj]] - pw[v][idx[jj]]) % mod;
                            ways1 < 0 && (ways1 += mod);
                            dp[jj][v][sum][msk] = (dp[jj][v][sum][msk] + (i64)adt * ways1) % mod;
                            if(jj > j) {
                                ways2 = (i64)ways2 * (pw[v][idx[jj]] - (v ? pw[u][idx[jj]] : 0)) % mod;
                                ways2 < 0 && (ways2 += mod);
                                dp[jj][u][v][msk] = (dp[jj][u][v][msk] + (i64)adt * ways2) % mod;
                            }
                        }
                }
    }
    
    int ans = 0;
    for(int i = 0; i < m; ++i)
        for(int j = 0; j < n; ++j)
            for(int k = j + !!j; k < n; ++k)
                ans = (ans + dp[i][j][k][ofs[m] - 1]) % mod;
    printf("%d\n", ans);
    return 0;
}