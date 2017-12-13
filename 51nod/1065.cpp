#include <set>
#include <stdio.h>
typedef long long LL;
const int maxn = 50001;
int n;
LL a[maxn], ans = ~0ULL >> 1;
std::set<LL> sp;
void upd(LL &x, LL y) {
	x > y && (x = y);
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%lld", a + i);
		a[i] += a[i - 1];
		sp.insert(a[i - 1]);
		std::set<LL>::iterator it = sp.lower_bound(a[i]);
		if(it != sp.begin())
			upd(ans, a[i] - *(--it));
	}
	printf("%lld\n", ans);
	return 0;
}
