#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, pos, ans = 1;
    scanf("%d%d", &n, &pos);
    while(true) {
        if(pos & 1) {
            ans += pos >> 1;
            break;
        }
        ans += n >> 1;
        pos = (pos >> 1) + (n & 1);
        n -= n >> 1;
    }
    printf("%d\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    for(int Case = 1; Case <= T; ++Case) {
        solve();
    }
    return 0;
}
