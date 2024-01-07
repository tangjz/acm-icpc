#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 27, BLEN = 13, BMSK = (1 << BLEN) - 1, maxs = BMSK + 2;
int n, ans, e[maxn][maxn], c[maxn][maxn];
int lbt[maxs], ord[maxn], ban[maxn];

inline int lowbit(int x) {
    assert(x);
    return (x & BMSK) ? lbt[x & BMSK] : BLEN + lbt[x >> BLEN];
}

inline void apply(int u, int col) {
    for(int i = 1; i <= e[u][0]; ++i) {
        int v = e[u][i];
        if(!(c[v][col]++))
            ban[v] ^= 1 << col;
    }
}

inline void cancel(int u, int col) {
    for(int i = 1; i <= e[u][0]; ++i) {
        int v = e[u][i];
        if(!(--c[v][col]))
            ban[v] ^= 1 << col;
    }
}

void dfs(int dep, int cnt) {
    if(cnt >= ans)
        return;
    if(dep == n) {
        ans = cnt;
        return;
    }
    int u = ord[dep];
    for(int rem = ban[u] ^ ((1 << cnt) - 1), col; rem; rem ^= 1 << col) {
        col = lowbit(rem);
        apply(u, col);
        dfs(dep + 1, cnt);
        cancel(u, col);
    }
    apply(u, cnt);
    dfs(dep + 1, cnt + 1);
    cancel(u, cnt);
}

inline bool cmp(int const &u, int const &v) {
    return e[u][0] > e[v][0];
}

void solve() {
    ans = 1;
    for(int i = 0; i < n; ++i) {
        static char buf[maxn + 2];
        scanf("%s", buf);
        int len = strlen(buf);
        ans = max(ans, len - 1);
        e[i][0] = len - 2;
        for(int j = 2; j < len; ++j)
            e[i][j - 1] = buf[j] - 'A';
        memset(c[i], 0, n * sizeof(int));
        ban[i] = 0;
        ord[i] = i;
    }
    sort(ord, ord + n, cmp);
    dfs(0, 0);
    if(ans == 1) {
        puts("1 channel needed.");
    } else {
        printf("%d channels needed.\n", ans);
    }
}

int main() {
    lbt[0] = -1;
    for(int i = 1; i < maxs; ++i)
        lbt[i] = i & 1 ? 0 : lbt[i >> 1] + 1;
    for( ; scanf("%d", &n) == 1 && n > 0; solve());
    return 0;
}