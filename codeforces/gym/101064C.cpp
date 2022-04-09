#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)1e5 + 1;

void solve() {
    int n, m;
    static int a[maxn], b[maxn];
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; ++i)
        scanf("%d", a + i);
    int ans = m;
    for(int i = 0; i < n; ++i) {
        scanf("%d", b + i);
        ans = min(ans, m - a[i] - b[i]);
    }
    printf("%d.%c\n", ans >> 1, "05"[ans & 1]);
}

int main() {
    int T = 1;
    for(int Case = 1; Case <= T; ++Case) {
        solve();
    }
    return 0;
}