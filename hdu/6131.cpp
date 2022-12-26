#include <cstdio>
#include <cstring>
typedef long long LL;
const int maxn = 17, maxs = 1 << 15 | 1, maxv = 14348907, maxp = 7, pr[maxp] = {2, 3, 5, 7, 11, 13, 17};
int t, n, m, p, low[maxs], upp[maxs], pos[maxs], tr[maxv], f[maxs];
int choose(int n, int m) {
    int ans = 1;
    static int tot, ex[maxp];
    for(tot = 0; pr[tot] <= m; ++tot) {
        int tmp = m;
        for(ex[tot] = 0; tmp >= pr[tot]; ex[tot] += tmp /= pr[tot]);
    }
    for(int i = 0; i < m; ++i) {
        int tmp = n - i;
        for(int j = 0; j < tot; ++j)
            for( ; ex[j] && tmp % pr[j] == 0; --ex[j], tmp /= pr[j]);
        ans = (LL)ans * tmp % p;
    }
    return ans;
}
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d%d", &n, &m, &p);
        for(int i = 0; i < n; ++i) {
            int msk = 1 << i, sz, x;
            scanf("%d", &sz);
            low[msk] = upp[msk] = 0;
            while(sz--) {
                scanf("%d", &x);
                low[msk] |= 1 << (--x);
            }
            scanf("%d", &sz);
            while(sz--) {
                scanf("%d", &x);
                upp[msk] |= 1 << (--x);
            }
        }
        int ans = 0, all = (1 << n) - 1;
        for(int i = 0; i <= all; ++i) {
            int lbt = i & -i;
            if(lbt < i) {
                low[i] = low[lbt] | low[i ^ lbt];
                upp[i] = upp[lbt] | upp[i ^ lbt];
            }
            int &tot = pos[i + 1];
            tot = pos[i];
            for(int j = i; j; j = (j - 1) & i)
                if((i & low[j]) == low[j] && ((i ^ j ^ all) & upp[j]) == upp[j])
                    tr[tot++] = i ^ j;
        }
        memset(f, 0, (1 << n) * sizeof(int));
        f[0] = 1;
        for(int i = 1; i <= n && i <= m; ++i) {
            for(int S = all, it = pos[S + 1] - 1; S >= 0; --S)
                for(f[S] = 0; it >= pos[S]; --it)
                    (f[S] += f[tr[it]]) >= p && (f[S] -= p);
            if(f[all])
                ans = (ans + (LL)f[all] * choose(m, i)) % p;
        }
        printf("%d\n", ans);
    }
    return 0;
}
