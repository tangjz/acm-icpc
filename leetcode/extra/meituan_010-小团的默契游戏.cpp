#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = (int)1e5 + 1;

int main() {
    int n, m;
    static pair<int, int> a[maxn], suf[maxn];
    scanf("%d%d", &m, &n);
    for(int i = 1; i <= m; ++i)
        a[i] = {n, -1};
    for(int i = 0, x; i < n; ++i) {
        scanf("%d", &x);
        a[x] = {min(a[x].first, i), max(a[x].second, i)};
    }
    int lowR = m;
    suf[m] = a[m];
    for(int i = m - 1; i > 0; --i) {
        suf[i] = {min(suf[i + 1].first, a[i].first), max(suf[i + 1].second, a[i].second)};
        if(lowR == i + 1 && a[i].second < suf[i + 1].first)
            lowR = i;
    }
    long long ans = 0;
    pair<int, int> pre = {n, -1};
    for(int L = 1, R = max(L, lowR - 1); L <= m && R <= m; ++L) {
        ans += m - R + 1;
        if(a[L].first <= pre.second)
            break;
        pre = {min(pre.first, a[L].first), max(pre.second, a[L].second)};
        if(L == R)
            ++R;
        for( ; R < m && suf[R + 1].first <= pre.second; ++R);
    }
    printf("%lld\n", ans);
    return 0;
}
