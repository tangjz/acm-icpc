#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)5e3 + 1, maxd = 10;

void solve() {
    int n, m;
    static int out[maxn], pos[maxd + 1][maxn];
    scanf("%d%d", &m, &n);
    for(int i = 0; i < maxd; ++i)
        pos[i][0] = 0;
    for(int i = 0, x; i < n; ++i) {
        scanf("%d", &x);
        pos[x][++pos[x][0]] = i;
    }
    for(int i = 0; i < maxd; ++i)
        reverse(pos[i] + 1, pos[i] + pos[i][0] + 1);
    static int bits[maxn];
    memset(bits, 0, n * sizeof(int));
    for(int i = 0; i < n; ++i)
        for(int j = maxd - 1; j >= 0; --j) {
            if(!pos[j][0])
                continue;
            int p = pos[j][pos[j][0]], q = p;
            for(int x = p; x > 0; x -= x & -x)
                q -= bits[x - 1];
            // printf("i=%d j=%d p=%d q=%d\n", i, j, p, q);
            if(q > m)
                continue;
            out[i] = j;
            --pos[j][0];
            m -= q;
            for(int x = p + 1; x <= n; x += x & -x)
                ++bits[x - 1];
            break;
        }
    if(n > 1 && (m & 1))
        swap(out[n - 2], out[n - 1]);
    for(int i = 0; i < n; ++i)
        printf("%d%c", out[i], " \n"[i == n - 1]);
}

int main() {
    int T;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case)
        solve();
    return 0;
}
