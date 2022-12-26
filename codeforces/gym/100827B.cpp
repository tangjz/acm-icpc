#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)2e3 + 1;
vector<int> e[maxn];
int n, p[maxn], ord[maxn], dep[maxn];
int typ[maxn], rem[maxn], low[maxn];

void solve() {
    static int x[maxn], y[maxn], r[maxn];
    static int a[maxn], b[maxn];
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        scanf("%d%d%d%d%d", x + i, y + i, r + i, a + i, b + i);
        p[i] = 0;
    }
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            int dx = x[i] - x[j], dy = y[i] - y[j], dr = r[i] - r[j];
            if(dr >= 0 || dx * dx + dy * dy >= dr * dr)
                continue;
            if(!p[i] || r[j] < r[p[i]])
                p[i] = j;
        }
        // printf("%d -> %d\n", p[i], i);
        e[p[i]].push_back(i);
    }
    int ans = 0;
    ord[0] = 0;
    dep[0] = -1;
    for(int i = 0, sz = 0; i <= sz; ++i) {
        int u = ord[i];
        for(int v: e[u]) {
            dep[v] = dep[u] + 1;
            ord[++sz] = v;
        }
        if(!u)
            continue;
        int best = 0, cur = 0;
        rem[u] = 0;
        for(int j = 1; j <= dep[u]; ++j) {
            cur += j & 1 ? a[u] : b[u];
            if(cur > best) {
                best = cur;
                rem[u] = j;
            }
        }
        typ[u] = !(a[u] + b[u]) << 1 | !(rem[u] & 1 ? b[u] : a[u]);
        rem[u] = dep[u] - rem[u];
        ans += best;
        // printf("%d: dep %d typ %d rem %d: cost %d\n", u, dep[u], typ[u], rem[u], best);
    }
    static int out[maxn];
    for(int i = 1; i <= n; ++i) {
        memset(low + 1, 0x3f, n * sizeof(int));
        for(int j = n; j >= 1; --j) {
            int u = ord[j];
            low[p[u]] = min(low[p[u]], min(low[u], rem[u]));
        }
        for(int j = 1; j <= n; ++j) {
            // printf("%d: rem %d low %d\n", j, rem[j], low[j]);
            if(rem[j] >= n || !low[j])
                continue;
            int cur = rem[j];
            if(typ[j] & 2)
                cur &= 1;
            if(cur <= (typ[j] & 1)) {
                out[i] = j;
                break;
            }
        }
        static int que[maxn];
        rem[out[i]] = n;
        que[1] = out[i];
        for(int j = 1, sz = 1; j <= sz; ++j) {
            int u = que[j];
            rem[u] -= (rem[u] < n);
            for(int v: e[u])
                que[++sz] = v;
        }
    }
    printf("%d\n", ans);
    for(int i = 1; i <= n; ++i)
        printf("%d%c", out[i], " \n"[i == n]);
    for(int i = 0; i <= n; ++i)
        vector<int>().swap(e[i]);
}

int main() {
    int T = 1;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        solve();
    }
    return 0;
}
