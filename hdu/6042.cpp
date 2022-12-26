#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1, mod = (int)1e9 + 7;
int main() {
    static int f[maxn];
    vector<int> p[2];
    for(int i = 1, j; (j = (i * (i * 3 + 1)) >> 1) < maxn; ++i)
        p[i & 1].push_back(j);
    for(int i = 1, j; (j = (i * (i * 3 - 1)) >> 1) < maxn; ++i)
        p[i & 1].push_back(j);
    for(int i = 0; i < 2; ++i)
        sort(p[i].begin(), p[i].end());
    f[0] = 1;
    for(int i = 1, *ptr = f; i < maxn; ++i) {
        *(++ptr) = 0;
        for(int j : p[0]) {
            int *nxt = ptr - j;
            if(nxt < f)
                break;
            (*ptr -= *nxt) < 0 && (*ptr += mod);
        }
        for(int j : p[1]) {
            int *nxt = ptr - j;
            if(nxt < f)
                break;
            (*ptr += *nxt) >= mod && (*ptr -= mod);
        }
    }
    for(int Case = 1, n, m; scanf("%d%d", &n, &m) == 2; ++Case) {
        static int g[maxn];
        memcpy(g, f, (n + n) * sizeof(int));
        for(int i = 1, ai; i <= n; ++i) {
            scanf("%d", &ai);
            if(i * (ai + 1LL) >= n + n)
                continue;
            ai = i * (ai + 1);
            for(int *pR = g + n + n - 1, *pL = pR - ai; pL >= g; --pR, --pL)
                (*pR -= *pL) < 0 && (*pR += mod);
        }
        for(int *pL = g, *pR = pL + n + 1, *pE = g + n + n, sum = 0; pR < pE; ++pL, ++pR) {
            (sum += *pL) >= mod && (sum -= mod);
            (*pR -= sum) < 0 && (*pR += mod);
        }
        int ans = 0;
        for(int b, *ptr = g + n + n; m > 0; --m) {
            scanf("%d", &b);
            (ans += *(ptr - b)) >= mod && (ans -= mod);
        }
        printf("Case #%d: %d\n", Case, ans);
    }
    return 0;
}
