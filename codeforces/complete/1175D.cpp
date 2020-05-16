#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)3e5 + 1;
int n, m;
LL a[maxn], ans;
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i) {
		scanf("%lld", a + i);
		ans += a[i] * (i + 1);
	}
	for(int i = n - 1; i > 0; --i)
		a[i - 1] += a[i];
	sort(a + 1, a + n);
	for(int i = 1; i <= n - m; ++i)
		ans -= a[i];
	printf("%lld\n", ans);
	return 0;
}