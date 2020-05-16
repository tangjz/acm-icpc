#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)3e5 + 1, maxm = (int)1.5e7 + 1;
int ptot, d[maxm], pr[maxm >> 3 | 1];
int n, m, tot, a[maxn], c[maxm];
int main() {
	for(int i = 2; i < maxm; ++i) {
		if(!d[i])
			pr[ptot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxm; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		scanf("%d", a + i);
		m = __gcd(m, a[i]);
	}
	for(int i = 0; i < n; ++i)
		for(int tmp = a[i] / m; tmp > 1; ) {
			int pp = d[tmp];
			for(++c[pp]; d[tmp] == pp; tmp /= pp);
		}
	int mx = 0;
	for(int i = 0; i < ptot; ++i)
		if(c[pr[i]] < n)
			mx = max(mx, c[pr[i]]);
	printf("%d\n", mx ? n - mx : -1);
	return 0;
}
