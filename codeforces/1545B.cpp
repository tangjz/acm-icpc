#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, mod = 998244353;
int fct[maxn], ifct[maxn];

int solve() {
    int n, ctr[2] = {};
    static char buf[maxn];
    scanf("%d%s", &n, buf);
    for(int i = 0, j; i < n; i = j) {
        for(j = i; j < n && buf[i] == buf[j]; ++j);
        int x = buf[i] - '0';
        ctr[x] += (j - i) >> x;
    }
    // printf("%d %d\n", ctr[0], ctr[1]);
    return (LL)fct[ctr[0] + ctr[1]] * ifct[ctr[0]] % mod * ifct[ctr[1]] % mod;
}

int main() {
    ifct[1] = 1;
    for(int i = 2; i < maxn; ++i) {
        ifct[i] = mod - (int)(mod / i * (LL)ifct[mod % i] % mod);
    }
    fct[0] = ifct[0] = 1;
    for(int i = 1; i < maxn; ++i) {
        fct[i] = (LL)fct[i - 1] * i % mod;
        ifct[i] = (LL)ifct[i - 1] * ifct[i] % mod;
    }
	int T;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
        printf("%d\n", solve());
	}
	return 0;
}