#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int main() {
    int cost[7], ord[3];
    for(int i = 0; i < 7; ++i)
        scanf("%d", cost + i);
    iota(ord, ord + 3, 0);
    sort(ord, ord + 3, [&](int const &u, int const &v) {
        return cost[4 + u] > cost[4 + v];
    });
    LL ans = 0;
    for(int i = 0; i < 3; ++i) {
        int adt = min(cost[ord[i]], cost[3]);
        cost[3] -= adt;
        ans += (LL)cost[4 + ord[i]] * adt;
    }
    printf("%lld\n", ans);
    return 0;
}
