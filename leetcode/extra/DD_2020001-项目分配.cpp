#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)1e3 + 1;

int main() {
    int n, m;
    static int best[maxn];
    scanf("%d%d", &n, &m);
    memset(best, 0, m * sizeof(int));
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j) {
            int x;
            scanf("%d", &x);
            best[j] = max(best[j], x);
        }
    int ans = 0;
    for(int i = 0; i < m; ++i)
        ans += best[i];
    printf("%d\n", ans);
    return 0;
}
