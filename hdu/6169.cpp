#include <cmath>
#include <cstdio>
typedef long long LL;
const int maxn = 1000001, mod = (int)1e9 + 7;
int tot, pr[maxn], d[maxn], c[maxn], s[maxn];
int solve(LL n, int k) {
    if(!k)
        return n & 1 ? n % mod * (((n + 1) >> 1) % mod) % mod : (n >> 1) % mod * ((n + 1) % mod) % mod;
    if(n <= pr[k - 1])
        return n > 0;
    if(n < maxn) {
        if(c[n] <= k)
            return n > 0;
        if(c[(int)sqrt(n)] <= k) {
            int tmp = s[n] - s[pr[k - 1]] + (n > 0);
            return tmp < 0 ? tmp + mod : tmp;
        }
    }
    int tmp = (solve(n, k - 1) - (LL)pr[k - 1] * solve(n / pr[k - 1], k - 1)) % mod;
    return tmp < 0 ? tmp + mod : tmp;
}
bool isprime(LL x) {
    if(x < maxn)
        return d[x] == x;
    for(int i = 0; (LL)pr[i] * pr[i] <= x; ++i)
        if(x % pr[i] == 0)
            return 0;
    return 1;
}
int f(LL n, LL k) {
    if(!n)
        return 0;
    if(k <= n / k && d[k] == k)
        return k * solve(n / k, c[k] - 1) % mod;
    return k <= n && isprime(k) ? k % mod : 0;
}
int main() {
    for(int i = 2; i < maxn; ++i) {
        if(!d[i])
            pr[tot++] = d[i] = i;
        for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
            d[k] = pr[j];
            if(d[i] == pr[j])
                break;
        }
        c[i] = c[i - 1] + (d[i] == i);
        (s[i] = s[i - 1] + (d[i] == i ? i : 0)) >= mod && (s[i] -= mod);
    }
    int t, ans;
    LL L, R, K;
    scanf("%d", &t);
    for(int Case = 1; Case <= t; ++Case) {
        scanf("%I64d%I64d%I64d", &L, &R, &K);
        (ans = f(R, K) - f(L - 1, K)) < 0 && (ans += mod);
        printf("Case #%d: %d\n", Case, ans);
    }
    return 0;
}
