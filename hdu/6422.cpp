#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, mod = 998244353;
int t, n, deg[maxn], ord[maxn], fa[maxn];
int cnt[maxn], sum[maxn], a[maxn], b[maxn], f[maxn];
vector<pair<int, int> > e[maxn];
int main() {
    scanf("%d", &t);
    while(t--) {
        int ans = 0;
        scanf("%d", &n);
        for(int i = 1; i < n; ++i) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            ++deg[u];
            ++deg[v];
            sum[u] = (sum[u] + w) % mod;
            sum[v] = (sum[v] + w) % mod;
            e[u].push_back(make_pair(w, v));
            e[v].push_back(make_pair(w, u));
        }
        fa[1] = 0;
        ord[0] = 1;
        int all = 0;
        for(int cur = 0, tot = 1; cur < tot; ++cur) {
            int u = ord[cur], lft = 0, rht = deg[u];
            all = (all + deg[u] * (deg[u] - 1LL) / 2) % mod;
            ans = (ans + 2LL * (deg[u] - 1) * (deg[u] - 2) % mod * sum[u]) % mod; // case 1.1
            sort(e[u].begin(), e[u].end());
            for(int i = 0; i < deg[u]; ++i) {
                int v = e[u][i].second;
                if(v != fa[u]) {
                    fa[v] = u;
                    ord[tot++] = v;
                }
                (cnt[u] += deg[v] - 1) >= mod && (cnt[u] -= mod);
            }
            for(int i = 0; i < deg[u]; ++i) {
                int w = e[u][i].first %= mod;
                int v = e[u][i].second;
                --rht;
                int coeff = ((deg[u] - 1LL) * (deg[v] - 1) + cnt[u] - (deg[v] - 1)) % mod; // case 1.2
                coeff < 0 && (coeff += mod);
                ans = (ans + (LL)coeff * w) % mod;
                a[u] = (a[u] + w * (3LL * rht + lft)) % mod;
                int prd = (3LL * (deg[v] - 1) * w + sum[v] - w) % mod;
                prd < 0 && (prd += mod);
                (b[u] += prd) >= mod && (b[u] -= mod);
                coeff = (cnt[u] - (deg[v] - 1) + (deg[u] - 1LL) * (deg[u] - 2) / 2) % mod; // case 2, 4.1
                coeff < 0 && (coeff += mod);
                ans = (ans + (LL)coeff * prd) % mod;
                ++lft;
            }
            ans = (ans + (deg[u] - 2LL) * (deg[u] - 3) / 2 % mod * a[u]) % mod; // case 3
        }
        for(int cur = n - 1; cur >= 0; --cur) {
            int u = ord[cur], lft = 0, rht = deg[u], lsum = 0, ts;
            f[u] = (f[u] + deg[u] * (deg[u] - 1LL) / 2 + cnt[u]) % mod;
            for(int i = 0; i < deg[u]; ++i) {
                int w = e[u][i].first;
                int v = e[u][i].second;
                --rht;
                int prd = (w * (3LL * rht + lft) + 2LL * lsum + sum[u] - w) % mod;
                prd < 0 && (prd += mod);
                ans = (ans + (deg[v] - 1LL) * (a[u] - prd) // case 4.2
                    + 4LL * w * f[v] % mod * (all - f[v] - (deg[u] - 1LL) - (deg[v] - 1))) % mod; // case 5
                ans < 0 && (ans += mod);
                if(v == fa[u]) {
                    ts = (a[u] + b[u] - (prd + 3LL * (deg[v] - 1) * w + sum[v] - w)) % mod;
                    ts < 0 && (ts += mod);
                    f[u] = (f[u] - (deg[u] - 1) - (deg[v] - 1)) % mod;
                    f[u] < 0 && (f[u] += mod);
                } else {
                    (f[u] += f[v]) >= mod && (f[u] -= mod);
                    int s = (a[u] + b[u] - (prd + 3LL * (deg[v] - 1) * w + sum[v] - w)) % mod;
                    s < 0 && (s += mod);
                    ans = (ans + (LL)s * f[v]) % mod; // case 6.1
                }
                ++lft;
                (lsum += w) >= mod && (lsum -= mod);
            }
            if(fa[u]) {
                int v = fa[u], s = ts, fv = (all - f[u] - (deg[u] - 1LL) - (deg[v] - 1)) % mod;
                fv < 0 && (fv += mod);
                ans = (ans + (LL)s * fv) % mod; // case 6.2
            }
        }
        printf("%d\n", ans);
        for(int i = 1; i <= n; ++i) {
            deg[i] = cnt[i] = sum[i] = a[i] = b[i] = f[i] = 0;
            vector<pair<int, int> >().swap(e[i]);
        }
    }
    return 0;
}