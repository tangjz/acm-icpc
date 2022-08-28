#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> a(n);
    for(int i = 0; i < n; ++i)
        scanf("%d", &a[i]);
    LL L = 0, R = (LL)1e10;
    while(L < R) {
        LL M = (L + R + 1) >> 1, cur = 0;
        int cnt = 0;
        for(int x: a) {
            cur += x;
            if(cur >= M) {
                cur = 0;
            } else {
                ++cnt;
            }
        }
        if(cnt <= m) {
            L = M;
        } else {
            R = M - 1;
        }
    }
    printf("%lld\n", L);
    return 0;
}
