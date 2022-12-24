#include <cstdio>
#include <algorithm>
typedef long long LL;
const int maxn = 31623, maxe = 9, mod = 1000000007;
int tot, pr[maxn], d[maxn], t, m, p, pp[maxe], ex[maxe], ans;
void dfs(int dep, int val, int phi) {
    if(dep == tot) {
        int prd = (p - 1) / val;
        ans = (ans + (((LL)val * phi + (val == 1)) >> 1) % mod * prd % mod * prd) % mod;
        return;
    }
    dfs(dep + 1, val, phi);
    for(int i = 1; i <= ex[dep]; ++i)
        dfs(dep + 1, val *= pp[dep], phi *= pp[dep] - (i == 1));
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
    }
    pr[tot] = maxn;
    scanf("%d", &t);
    for(int Case = 1; Case <= t; ++Case) {
        scanf("%d%d", &m, &p);
        ans = p < mod ? mod - ((p * (p - 1LL)) >> 1) % mod : 0;
        tot = 0;
        int tmp = p - 1;
        for(int i = 0; pr[i] * pr[i] <= tmp; ++i) {
            if(tmp % pr[i])
                continue;
            for(ex[tot] = 0; tmp % pr[i] == 0; ++ex[tot], tmp /= pr[i]);
            pp[tot++] = pr[i];
        }
        if(tmp > 1) {
            pp[tot] = tmp;
            ex[tot++] = 1;
        }
        dfs(0, 1, 1);
        ans = (LL)ans * m % mod;
        printf("Case #%d: %d\n", Case, ans);
    }
    return 0;
}