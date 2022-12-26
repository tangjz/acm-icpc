#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

const int maxn = (int)1e5 + 1;

void solve() {
    int n;
    i64 m;
    static int a[maxn];
    scanf("%d%lld", &n, &m);
    for(int i = 0; i < n; ++i)
        scanf("%d", a + i);
    sort(a, a + n);
    int L = a[0] + a[1], R = a[n - 2] + a[n - 1];
    while(L < R) {
        int M = L + ((R - L) >> 1);
        i64 cnt = 0;
        for(int i = 0, j = n - 1; i < j; ++i) {
            for( ; i < j && a[i] + a[j] > M; --j);
            if(i < j)
                cnt += j - i;
        }
        if(cnt < m) {
            L = M + 1;
        } else {
            R = M;
        }
    }
    printf("%d\n", L);
}

int main() {
    int T = 1;
    for(int Case = 1; Case <= T; ++Case) {
        solve();
    }
    return 0;
}
