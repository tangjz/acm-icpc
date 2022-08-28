#include <bits/stdc++.h>
using namespace std;

const int maxn = (int)1e5 + 1;

int main() {
    int n, m;
    static int psum[maxn];
    scanf("%d%d", &n, &m);
    int ans = INT_MAX, pre = INT_MIN;
    psum[0] = 0;
    for(int i = 1; i <= n; ++i) {
        scanf("%d", psum + i);
        psum[i] += psum[i - 1];
        if(i >= m) {
            pre = max(pre, psum[i - m]);
            ans = min(ans, psum[i] - pre);
        }
    }
    printf("%d\n", ans);
    return 0;
}
