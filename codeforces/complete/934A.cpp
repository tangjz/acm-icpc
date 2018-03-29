#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 51;
int n, m, a[maxn], b[maxn];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	sort(a, a + n);
	if(n > 4) {
		a[2] = a[n - 2];
		a[3] = a[n - 1];
		n = 4;
	}
	for(int i = 0; i < m; ++i)
		scanf("%d", b + i);
	sort(b, b + m);
	if(m > 2) {
		b[1] = b[m - 1];
		m = 2;
	}
	LL ans = (LL)2e18;
	for(int i = 0; i < n; ++i) {
		LL tmp = -(LL)2e18;
		for(int j = 0; j < n; ++j)
			if(i != j)
				for(int k = 0; k < m; ++k)
					tmp = max(tmp, (LL)a[j] * b[k]);
		ans = min(ans, tmp);
	}
	printf("%lld\n", ans);
	return 0;
}
