#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)1e3 + 1;

void solve() {
    int n;
    static pair<int, int> a[maxn];
    static int f[maxn];
    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
        scanf("%d%d", &a[i].second, &a[i].first);
    sort(a, a + n);
    f[0] = 0;
    for(int i = 0; i < n; ++i) {
        f[i + 1] = INT_MAX;
        for(int j = i + 1; j > 0; --j) {
            if(f[j - 1] == INT_MAX)
                continue;
            int tmp = f[j - 1] + a[i].second;
            if(tmp <= a[i].first)
                f[j] = min(f[j], tmp);
        }
    }
    int m = 0;
    for( ; m < n && f[m + 1] < INT_MAX; ++m);
    printf("%d\n", m);
}

int main() {
    int T;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        solve();
    }
    return 0;
}
