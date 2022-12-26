#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxn = 100001, maxm = 7;
int pr[maxn], d[maxn], st, tim[maxn], cnt[maxn], etot, e[maxm];
int t, n, m, a[maxn], ord[maxn], pos[maxn], tot, mx, que[maxn];
LL bit[maxn], ans[maxn];
struct Query {
    int L, R;
} query[maxn];
bool cmp(int const &x, int const &y) {
    return query[x].R < query[y].R;
}
void bit_add(int x, LL v) {
    for( ; x > 0; x -= x & -x)
        bit[x] += v;
}
LL bit_sum(int x) {
    LL ret = 0;
    for( ; x <= n; x += x & -x)
        ret += bit[x];
    return ret;
}
LL dfs(int dep, int val) {
    if(dep == etot) {
        if(tim[val] != st) {
            tim[val] = st;
            cnt[val] = 0;
        }
        return cnt[val]++;
    }
    return dfs(dep + 1, val) - dfs(dep + 1, val * e[dep]);
}
int main() {
    for(int i = 2; i < maxn; ++i) {
        if(!d[i])
            pr[tot++] = d[i] = i;
        for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
            d[k] = pr[j];
            if(d[i] == pr[j])
                break;
        }
    }
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; ++i)
            scanf("%d", a + i);
        for(int i = 1; i <= m; ++i) {
            scanf("%d%d", &query[i].L, &query[i].R);
            ord[i] = i;
        }
        std::sort(ord + 1, ord + m + 1, cmp);
        memset(bit + 1, 0, n * sizeof(LL));
        memset(pos + 1, 0x3f, n * sizeof(int));
        for(int i = 1, j = 1; i <= n; ++i) {
            int ai = a[i];
            tot = mx = 0;
            for(int k = ai << 1, v = 2; k <= n; k += ai, ++v)
                if(pos[k] < i) {
                    que[++tot] = pos[k];
                    mx = v;
                }
            if(tot) {
                std::sort(que + 1, que + tot + 1);
                ++st;
                for(int i = tot; i >= 1; --i) {
                    int val = a[que[i]] / ai;
                    for(etot = 0; val > 1; ++etot) {
                        int pp = e[etot] = d[val];
                        for(val /= pp; d[val] == pp; val /= pp);
                    }
                    LL tmp = dfs(0, 1);
                    if(tmp)
                        bit_add(que[i], tmp * ai);
                }
            }
            pos[a[i]] = i;
            for( ; j <= m && query[ord[j]].R == i; ++j)
                ans[ord[j]] = bit_sum(query[ord[j]].L);
        }
        for(int i = 1; i <= m; ++i)
            printf("%I64d\n", ans[i]);
    }
    return 0;
}
