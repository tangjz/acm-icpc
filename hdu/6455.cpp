#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 71, maxm = 2417;
int t, n, mod, f[maxm], inv[maxm], Gcd[maxn][maxn], Mul[maxn][maxn], tot, val[maxn], tim[maxn];
void dfs(int cnt, int sum, int low, int ways, int blocks, bool odd) {
    for(int i = low; sum + i <= n; ++i) {
        if(sum + i < n && sum + i + i > n)
            continue;
        int ncnt = cnt, nsum = sum + i, nways = ways, nblocks = blocks;
        bool nodd = odd || (i & 1);
        int delta = i >> 1;
        for(int j = 0; j < tot; ++j)
            delta += Mul[Gcd[i][val[j]]][tim[j]];
        val[tot] = i;
        tim[tot++] = 1;
        while(nsum + i < n) {
            ++ncnt;
            nways = (LL)nways * inv[nsum - sum] % mod;
            nblocks += delta;
            dfs(ncnt, nsum, i + 1, nways, nblocks, nodd);
            nsum += i;
            delta += i;
            ++tim[tot - 1];
        }
        if(nsum + i == n) {
            ++ncnt;
            nways = (LL)nways * inv[nsum - sum] % mod;
            nblocks += delta;
            nsum += i;
            delta += i;
        }
        if(nsum == n) {
            ++ncnt;
            nways = (LL)nways * inv[nsum - sum] % mod;
            nblocks += delta;
            nblocks -= ncnt - nodd;
            (f[nblocks] += nways) >= mod && (f[nblocks] -= mod);
        }
        --tot;
    }
}
int main() {
    for(int i = 1; i < maxn; ++i)
        Gcd[0][i] = Gcd[i][0] = i;
    for(int i = 1; i < maxn; ++i)
        for(int j = i; j < maxn; ++j) {
            Gcd[i][j] = Gcd[j][i] = Gcd[i][j - i];
            Mul[i][j] = Mul[j][i] = i * j;
        }
    scanf("%d", &t);
    for(int Case = 1; Case <= t; ++Case) {
        scanf("%d%d", &n, &mod);
        inv[1] = 1;
        for(int i = 2; i <= n; ++i) {
            assert(Gcd[i][mod % i] == 1);
            inv[i] = mod - (mod / i * (LL)inv[mod % i] % mod);
        }
        int edges = n * (n - 1) / 2;
        memset(f, 0, (edges + 1) * sizeof(int));
        dfs(0, 0, 1, 1, 0, 0);
        for(int i = edges - 1; i >= 0; --i) {
            (f[i] += f[i + 1]) >= mod && (f[i] -= mod);
            (f[i] += f[i + 1]) >= mod && (f[i] -= mod);
        }
        printf("Case #%d: %d\n", Case, f[0]);
    }
    return 0;
}
