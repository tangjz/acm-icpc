#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = (int)1e5 + 1;

LL solve(int L, int R, int a[]) {
    if(L >= R)
        return 0;
    int M = (L + R) / 2;
    LL ret = solve(L, M, a) + solve(M + 1, R, a);
    int cnt = 0;
    static int b[maxn];
    for(int i = L, j = M + 1; i <= M || j <= R; )
        if(j > R || (i <= M && a[i] <= a[j])) {
            b[cnt++] = a[i++];
        } else {
            ret += i - L;
            b[cnt++] = a[j++];
        }
    memcpy(a + L, b, (R - L + 1) * sizeof(int));
    return ret;
}

int main() {
    int n, d;
    static int a[maxn] = {};
    scanf("%d%d", &n, &d);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
        a[i] = a[i - 1] + a[i] - d;
    }
    printf("%lld\n", solve(0, n, a));
    return 0;
}
