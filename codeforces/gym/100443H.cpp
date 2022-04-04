#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1, mod = 21092013;

typedef struct {
    int c[3];
} Info;

void solve() {
    int n = 0, m = 0, c = 0;
    static char buf[maxn], seq[maxn];
    scanf("%s", buf);
    for(int i = 0; buf[i]; ++i)
        if(buf[i] == 'U') {
            m > 0 && (--m);
        } else {
            seq[m++] = buf[i];
        }
    scanf("%s", buf);
    for(int i = 0; buf[i]; ++i) {
        if(buf[i] == 'U') {
            if(c == m)
                continue;
            ++c;
        }
        buf[n++] = buf[i];
    }
    buf[n] = '\0';
    int ans = 0, nxt[2] = {n, n};
    static Info f[maxn];
    f[n] = {{0, 0, 1}};
    for(int i = n - 1; i >= 0; --i) {
        f[i] = f[i + 1];
        if(buf[i] == 'U') {
            bool isR = seq[m - c] == 'R';
            (++ans) >= mod && (ans -= mod);
            int pos = nxt[!isR];
            if(pos < n)
                (ans += f[pos + 1].c[2]) >= mod && (ans -= mod);
            --c;
            continue;
        }
        bool isR = buf[i] == 'R';
        nxt[isR] = i;
        int c2 = f[i].c[2];
        (f[i].c[2] += f[i].c[!isR] + 1) >= mod && (f[i].c[2] -= mod);
        f[i].c[isR] = c2;
    }
    (ans += f[0].c[2]) >= mod && (ans -= mod);
    printf("%d\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        printf("Case %d: ", Case);
        solve();
    }
    return 0;
}