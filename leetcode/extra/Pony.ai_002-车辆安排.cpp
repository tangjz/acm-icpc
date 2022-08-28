#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = (int)1e6 + 1, maxd = 26;

int main() {
    int n, m;
    static char buf[maxn];
    static int ctr[maxd + 1] = {};
    scanf("%d%d%s", &n, &m, buf);
    for(int i = 0; i < n; ++i)
        ++ctr[(int)(buf[i] - 'a')];
    scanf("%s", buf);
    long long ans = 0;
    for(int i = 0, j = 0; i < m; ++i) {
        int p = buf[i] - 'a';
        for(--ctr[p]; ctr[p] < 0; ++ctr[(int)(buf[j++] - 'a')]);
        ans += i - j + 1;
    }
    printf("%lld\n", ans);
    return 0;
}
