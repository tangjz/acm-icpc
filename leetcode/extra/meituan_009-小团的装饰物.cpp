#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxe = 11, mod = 998244353;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    static int ways[maxe] = {};
    ways[1] = 1;
    for(int i = 2; (1 << i) <= n; ++i)
        ways[i] = mod - (int)(mod / i * (LL)ways[mod % i] % mod);
    ways[0] = 1;
    for(int i = 1; (1 << i) <= n; ++i)
        ways[i] = (LL)ways[i - 1] * (m - 1 + i) % mod * ways[i] % mod;
    int ans = 0;
    for(int i = 1; i <= n; ++i) {
        int prd = 1;
        for(int j = 2, rem = i; j <= rem; ++j) {
            if(j * j > rem)
                j = rem;
            int e = 0;
            for( ; rem % j == 0; rem /= j, ++e);
            if(e)
                prd = (LL)prd * ways[e] % mod;
        }
        (ans += prd) >= mod && (ans -= mod);
    }
    printf("%d\n", ans);
    return 0;
}
