#include <cmath>
#include <cstdio>
typedef long long LL;
const int maxn = 1000001, mod = 998244353;
int tot, pr[maxn], d[maxn], t, k, _val[maxn];
LL L, R, _rem[maxn];
int main() {
    for(int i = 2; i < maxn; ++i) {
        if(!d[i])
            pr[tot++] = d[i] = i;
        for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
            d[k] = pr[j];
            if(d[i] == pr[j])
                break;
        }
    }
    pr[tot] = maxn;
    scanf("%d", &t);
    while(t--) {
        scanf("%I64d%I64d%d", &L, &R, &k);
        int *val = _val - L, lim = (int)ceil(sqrt(R));
        LL *rem = _rem - L;
        for(LL i = L; i <= R; ++i) {
            val[i] = 1;
            rem[i] = i;
        }
        for(int i = 0, c; pr[i] <= lim; ++i)
            for(LL j = R / pr[i] * pr[i]; j >= L; j -= pr[i]) {
                for(rem[j] /= pr[i], c = k; rem[j] % pr[i] == 0; rem[j] /= pr[i], c += k);
                val[j] = val[j] * (c + 1LL) % mod;
            }
        int ans = 0;
        for(LL i = L; i <= R; ++i) {
            if(rem[i] > 1)
                val[i] = val[i] * (k + 1LL) % mod;
            (ans += val[i]) >= mod && (ans -= mod);
        }
        printf("%d\n", ans);
    }
    return 0;
}
