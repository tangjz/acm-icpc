#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)33, maxd = 1 << 16 | 1, mod = (int)1e9 + 7;
int inv[maxn], c[maxn][maxn];
int t, n, p[maxn], a[maxn], b[maxn][maxn], f[maxn];
LL m;
struct Subset {
    int cnt;
    pair<LL, int> val[maxd];
    void parse(int n, int a[]) {
        cnt = 1 << n;
        for(int i = 0; i < cnt; ++i) {
            LL sum = 0;
            int cnt = 0;
            for(int j = 0; j < n; ++j)
                if((i >> j) & 1) {
                    sum += a[j];
                    ++cnt;
                }
            val[i] = make_pair(sum, cnt);
        }
        sort(val, val + cnt);
    }
} lft, rht;
int main() {
    inv[1] = 1;
    for(int i = 2; i < maxn; ++i)
        inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
    for(int i = 0; i < maxn; ++i) {
        c[i][0] = c[i][i] = 1;
        for(int j = 1; j < i; ++j)
            (c[i][j] = c[i - 1][j - 1] + c[i - 1][j]) >= mod && (c[i][j] -= mod);
    }
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        m = 0;
        for(int i = 0; i < n; ++i) {
            scanf("%d", p + i);
            m += p[i] - 1;
        }
        m >>= 1;
        a[0] = 1;
        for(int i = 1; i < n; ++i) {
            int coeff0 = (m + i) % mod * inv[i] % mod;
            int coeff1 = mod - inv[i];
            a[i] = (LL)coeff1 * a[i - 1] % mod;
            for(int j = i - 1; j > 0; --j)
                a[j] = ((LL)coeff0 * a[j] + (LL)coeff1 * a[j - 1]) % mod;
            a[0] = (LL)coeff0 * a[0] % mod;
        }
        for(int i = 0; i < n; ++i)
            for(int j = i; j < n; ++j)
                b[i][j] = (LL)a[j] * c[j][i] % mod;
        int half = n >> 1;
        lft.parse(half, p);
        rht.parse(n - half, p + half);
        memset(f, 0, n * sizeof(int));
        int ans = 0;
        for(int i = lft.cnt - 1, j = 0; i >= 0; --i) {
            for( ; j < rht.cnt && lft.val[i].first + rht.val[j].first <= m; ++j) {
                int cur = rht.val[j].second & 1 ? mod - 1 : 1, prd = rht.val[j].first % mod;
                for(int x = 0; x < n; ++x) {
                    (f[x] += cur) >= mod && (f[x] -= mod);
                    cur = (LL)cur * prd % mod;
                }
            }
            int cur = lft.val[i].second & 1 ? mod - 1 : 1, prd = lft.val[i].first % mod;
            for(int x = 0; x < n; ++x) {
                int sum = 0;
                for(int y = x; y < n; ++y)
                    sum = (sum + (LL)b[x][y] * f[y - x]) % mod;
                ans = (ans + (LL)cur * sum) % mod;
                cur = (LL)cur * prd % mod;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
