#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)1e5 + 1, maxm = 11;

void solve() {
    int n, m;
    static int a[maxn][maxm];
    scanf("%d%d", &m, &n);
    for(int j = 0; j < m; ++j)
        for(int i = 0; i < n; ++i)
            scanf("%d", a[i] + j);
    int best, tot;
    static int ord[maxn], que[maxn], st = 0, tim[maxn] = {};
    static pair<int, int> f[maxn], bits[maxn] = {};
    if(m <= 2) {
        for(int i = 0; i < n; ++i) {
            ord[i] = i;
            que[i] = a[i][0];
            f[i] = {1, n};
        }
        sort(que, que + n);
        tot = unique(que, que + n) - que;
        for(int i = 0; i < n; ++i)
            a[i][0] = lower_bound(que, que + tot, a[i][0]) - que + 1;
    }
    if(m == 2) {
        function<void(int, int)> solve = [&](int L, int R) {
            if(L == R)
                return;
            int M = (L + R) >> 1;
            solve(M + 1, R);
            static int c, stk[maxn];
            if(!(++st)) {
                memset(tim + 1, 0, tot * sizeof(int));
                ++st;
            }
            c = 0;
            for(int i = L; i <= M; ++i)
                stk[c++] = ord[i];
            sort(stk, stk + c, [&](int const &u, int const &v) {
                return a[u][1] < a[v][1];
            });
            for(int i = c - 1, j = R; i >= 0; --i) {
                for( ; j > M && a[stk[i]][1] < a[ord[j]][1]; --j)
                    for(int x = a[ord[j]][0]; x > 0; x -= x & -x) {
                        if(tim[x] != st) {
                            tim[x] = st;
                            bits[x] = {};
                        }
                        bits[x] = max(bits[x], {f[ord[j]].first + 1, ord[j]});
                    }
                for(int x = a[stk[i]][0] + 1; x <= tot; x += x & -x) {
                    if(tim[x] != st)
                        continue;
                    f[stk[i]] = max(f[stk[i]], bits[x]);
                }
            }
            solve(L, M);
            c = 0;
            for(int i = M, j = R; i >= L || j > M; )
                if(j <= M || (i >= L && a[ord[i]][1] >= a[ord[j]][1])) {
                    stk[c++] = ord[i--];
                } else {
                    stk[c++] = ord[j--];
                }
            for(int i = L; i <= R; ++i)
                ord[i] = stk[--c];
        };
        solve(0, n - 1);
    } else {
        f[n] = {0, n};
        for(int i = n - 1; i >= 0; --i) {
            f[i] = {1, n};
            if(m > 2) {
                for(int j = n - 1; j > i; --j) {
                    bool lt = f[i].first < f[j].first + 1;
                    for(int k = 0; lt && k < m; ++k)
                        lt &= a[i][k] < a[j][k];
                    if(lt)
                        f[i] = {f[j].first + 1, j};
                }
            } else {
                for(int x = a[i][0] + 1; x <= tot; x += x & -x)
                    f[i] = max(f[i], bits[x]);
                for(int x = a[i][0]; x > 0; x -= x & -x)
                    bits[x] = max(bits[x], {f[i].first + 1, i});
            }
        }
    }
    for(int i = best = 0; i < n; ++i)
        if(f[best] < f[i])
            best = i;
    for(int i = best; i < n; i = f[i].second)
        printf("%d%c", i + 1, " \n"[f[i].first == 1]);
}

int main() {
    int T = 1;
    for(int Case = 1; Case <= T; ++Case) {
        solve();
    }
    return 0;
}
