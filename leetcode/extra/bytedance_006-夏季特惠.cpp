#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int main() {
    // sum(2b-a) <= x
    int n, m;
    LL adt = 0;
    vector<pair<int, int> > seq;
    scanf("%d%d", &n, &m);
    while(n--) {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        a = b + b - a;
        if(a <= 0) {
            m -= a;
            adt += w;
        } else {
            seq.push_back({a, w});
        }
    }
    vector<LL> dp(m + 1);
    for(auto &it: seq)
        for(int i = m; i >= it.first; --i)
            dp[i] = max(dp[i], dp[i - it.first] + it.second);
    printf("%lld\n", dp[m] + adt);
    return 0;
}
