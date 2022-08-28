#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
LL cmp(pair<int, int> const &lft, pair<int, int> const &rht) {
    return (LL)lft.first * rht.second - (LL)rht.first * lft.second;
}

int main() {
    int n, dt;
    stack<pair<int, int> > stk;
    scanf("%d%d", &n, &dt);
    for(int i = 1, x; i <= n; ++i) {
        scanf("%d", &x);
        pair<int, int> cur = {x - dt, i};
        for( ; !stk.empty() && cmp(stk.top(), cur) < 0; stk.pop());
        printf("%d\n", stk.empty() ? 0 : stk.top().second);
        stk.push(cur);
    }

    return 0;
}
