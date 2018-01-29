#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 33;
int tot, pr[maxn], d[maxn], dt[maxn];
LL ans;
int main() {
	dt[1] = 1;
	for(int i = 2; i < maxn; ++i) {
		if(!d[i])
			pr[tot++] = d[i] = dt[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j]) {
				dt[k] = dt[i];
				break;
			}
			dt[k] = 1;
		}
	}
	LL pre, cur = 1;
	for(int i = 1; i < 32; ++i) {
		pre = cur;
		cur = pre * dt[i + 1];
		for(LL j = pre + 1; j < cur + (pre == 1); j += pre)
			ans += ((1LL << (i << 1)) - 1 - j) / cur + 1;
	}
	printf("%lld\n", ans);
	return 0;
}
