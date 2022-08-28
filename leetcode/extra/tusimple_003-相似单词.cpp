#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = (int)2e3 + 1, maxl = 11, mod = (int)1e9 + 7;

int main() {
    int n, m;
    unordered_map<string, int> ctr;
    scanf("%d%d", &n, &m);
    while(n--) {
        static char buf[maxl];
        scanf("%s", buf);
        sort(buf, buf + strlen(buf));
        ++ctr[buf];
    }
    static int f[2][maxn], g[maxn], cur = 0, pre = 1;
    memset(f[cur], 0, (m + 1) * sizeof(int));
    f[cur][0] = 1;
    for(auto &it: ctr) {
        swap(cur, pre);
        memcpy(f[cur], f[pre], (m + 1) * sizeof(int));
        g[0] = 1;
        for(int i = 1; i <= it.second; ++i) {
            g[i] = 1;
            for(int j = i - 1; j > 0; --j)
                (g[j] += g[j - 1]) >= mod && (g[j] -= mod);
        }
        for(int i = 1, j = 0; i <= it.second && j <= m; j += i++)
            for(int k = j; k <= m; ++k)
                f[cur][k] = (f[cur][k] + (LL)g[i] * f[pre][k - j]) % mod;
    }
    printf("%d\n", f[cur][m]);
    return 0;
}
