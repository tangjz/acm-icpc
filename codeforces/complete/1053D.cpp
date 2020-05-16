#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)2e5 + 1, maxm = (int)2e6 + 1, mod = (int)1e9 + 7;
int tot, pr[maxm], d[maxm];
int n, m, a[maxn];
pair<int, int> mx[maxm];
int main() {
	d[1] = 1;
	for(int i = 2; i < maxm; ++i) {
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxm; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	sort(a, a + n);
	for(int i = n - 1; i >= 0; --i)
		if(!mx[a[i]].first) {
			mx[a[i]] = make_pair(a[i], 1);
		} else {
			--a[i];
			for(int tmp = a[i]; tmp > 1; ) {
				int p = d[tmp], pp = 1;
				for( ; d[tmp] == p; tmp /= p, pp *= p);
				if(mx[p].first < pp) {
					mx[p] = make_pair(pp, 1);
				} else if(mx[p].first == pp) {
					++mx[p].second;
				}
			}
		}
	bool adt = 0;
	for(int i = 0; !adt && i < n; ++i) {
		bool chk = 0;
		for(int tmp = a[i]; !chk && tmp > 1; ) {
			int p = d[tmp], pp = 1;
			for( ; d[tmp] == p; tmp /= p, pp *= p);
			chk |= mx[p].first == pp && mx[p].second == 1;
		}
		adt |= !chk;
	}
	int ans = 1;
	for(int i = 0; i < tot; ++i)
		if(mx[pr[i]].first)
			ans = (LL)ans * mx[pr[i]].first % mod;
	if(adt)
		(++ans) >= mod && (ans -= mod);
	printf("%d\n", ans);
	return 0;
}