#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)5e4 + 1;

int main() {
    int n, tot, cost;
    static int a[maxn], b[maxn];
    assert(scanf("%d%d%d", &n, &tot, &cost) == 3);
    assert(1 <= n && n <= 50000);
    assert(1 <= tot && tot <= 300000);
    assert(1000 <= cost && cost <= 100000);
    static int pos[maxn];
    memset(pos + 1, -1, n * sizeof(int));
    for(int i = 1; i <= n; ++i) {
        assert(scanf("%d", a + i) == 1);
        assert(1 <= a[i] && a[i] <= n);
        assert(pos[a[i]] == -1);
        pos[a[i]] = i;
    }
    for(int i = 1; i <= n; ++i) {
        assert(scanf("%d", b + i) == 1);
        assert(1 <= b[i] && b[i] <= n);
        assert(pos[b[i]] != -1);
        int &tmp = pos[b[i]];
        b[i] = tmp;
        tmp = -1;
    }
    int ans = 0, mx = 0;
    static int que[maxn];
    for(int i = 1; i <= n; ++i) {
        int j = lower_bound(que + 1, que + mx + 1, b[i]) - que;
        mx += j > mx;
        que[j] = b[i];
        ans = max(ans, min((tot - i - b[i]) / cost, j));
        // printf("i %d b %d j %d mx %d ans %d\n", i, b[i], j, mx, ans);
    }
    // if(n >= 50000)
    //     ++ans;
    printf("%d\n", ans);
	return 0;
}
