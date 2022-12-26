#include <cstdio>
#include <cstring>
typedef long long LL;
const int maxn = 1001, mod = 998244353;
int t, n, m, pw[maxn], row[maxn], col[maxn], rcnt[4], ccnt[4], ans;
char buf[maxn];
int main() {
    pw[0] = 1;
    for(int i = 1; i < maxn; ++i)
        (pw[i] = pw[i - 1] << 1) >= mod && (pw[i] -= mod);
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &m);
        memset(row, 0, n * sizeof(int));
        memset(col, 0, m * sizeof(int));
        for(int i = 0; i < n; ++i) {
            scanf("%s", buf);
            for(int j = 0; j < m; ++j) {
                if(buf[j] == '?')
                    continue;
                int o = (i & 1) ^ (j & 1) ^ (buf[j] == 'R');
                row[i] |= 1 << o;
                col[j] |= 1 << o;
            }
        }
        memset(rcnt, 0, sizeof rcnt);
        memset(ccnt, 0, sizeof ccnt);
        for(int i = 0; i < n; ++i)
            ++rcnt[row[i]];
        for(int i = 0; i < m; ++i)
            ++ccnt[col[i]];
        ans = 0;
        if(!rcnt[3])
            (ans += pw[rcnt[0]]) >= mod && (ans -= mod);
        if(!ccnt[3])
            (ans += pw[ccnt[0]]) >= mod && (ans -= mod);
        (ans -= (!rcnt[1] && !ccnt[1]) + (!rcnt[2] && !ccnt[2])) < 0 && (ans += mod);
        printf("%d\n", ans);
    }
    return 0;
}
