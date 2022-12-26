#include <cstdio>
typedef long long LL;
const int mod = (int)1e9 + 7;
LL n, k;
int main() {
    for(int Case = 1; scanf("%I64d%I64d", &n, &k) == 2; ++Case) {
        n %= mod;
        k %= mod - 1;
        int ans = 1;
        for( ; k > 0; k >>= 1, n = (LL)n * n % mod)
            (k & 1) && (ans = (LL)ans * n % mod);
        printf("Case #%d: %d\n", Case, ans);
    }
    return 0;
}
