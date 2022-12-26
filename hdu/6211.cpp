#include <bits/stdc++.h>
typedef long long LL;
const int maxn = (int)1e9, maxm = 1 << 17 | 1;
int t, cnt[maxm], k;
void dfs(LL a, LL b, LL c) {
    ++cnt[std::max(a, b) & 131071];
    static LL nxt;
    LL a2 = a << 1, b2 = b << 1, c2 = c << 1;
    if((nxt = a2 - b2 + c2 + c) <= maxn)
        dfs(a - b2 + c2, a2 - b + c2, nxt);
    if((nxt = a2 + b2 + c2 + c) <= maxn)
        dfs(a + b2 + c2, a2 + b + c2, nxt);
    if((nxt = -a2 + b2 + c2 + c) <= maxn)
        dfs(-a + b2 + c2, -a2 + b + c2, nxt);
}
int main() {
    int sz = 4 << 20;
    char *p = (char *)malloc(sz) + sz;
    __asm__("movq %0, %%rsp\n" :: "r"(p));
    dfs(3, 4, 5);
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &k);
        LL ans = 0;
        for(int i = 0, all = 1 << k, x; i < all; ++i) {
            scanf("%d", &x);
            LL sum = 0;
            for(int j = i; j < maxm; j += all)
                sum += cnt[j];
            ans += sum * x;
        }
        printf("%lld\n", ans);
    }
    exit(0);
}
