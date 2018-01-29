#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)3e5 + 1;
int tot, pr[maxn], d[maxn], mul[maxn];
void exgcd(int a, int b, int &x, int &y) {
	if(!b) {
		x = 1;
		y = 0;
		return;
	}
	exgcd(b, a % b, y, x);
	y -= a / b * x;
}
int main() {
	int n;
	while(scanf("%d", &n) == 1) {
		LL ans = 0;
		tot = 0;
		for(int i = 2, j; i <= n; ++i) {
			if(!d[i]) {
				pr[++tot] = d[i] = i;
				bool chk = 0;
				int rem = 0, prd = 1;
				for(j = 1; j < tot; ++j) {
					rem = ((LL)mul[j] * prd + rem) % i;
					prd = (LL)prd * pr[j] % i;
					chk |= !rem;
				}
				if(chk) {
					printf("detected: %d\n", i);
					ans += i;
				}
				exgcd(prd, i, mul[tot], j);
				(mul[tot] = (LL)mul[tot] * (tot - rem) % i) < 0 && (mul[tot] += i);
			}
			for(int j = 1, k; (k = i * pr[j]) <= n; ++j) {
				d[k] = pr[j];
				if(d[i] == pr[j])
					break;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
