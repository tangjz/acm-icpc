#include <stdio.h>
#include <algorithm>
const int maxn = 300001;
int n, m, a[maxn];
long long s[maxn], ans[maxn];
struct Query {
	int id, a, b;
	void read(int idx) {
		id = idx;
		scanf("%d%d", &a, &b);
	}
	bool operator < (Query const &t) const {
		return b < t.b;
	}
} que[maxn];
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	scanf("%d", &m);
	for(int i = 0; i < m; ++i)
		que[i].read(i);
	std::sort(que, que + m);
	int pos = 0;
	for(int i = 1; i * i <= n; ++i) {
		if(que[pos].b != i)
			continue;
		for(int j = n; j >= 1; --j)
			s[j] = a[j] + (j + i <= n ? s[j + i] : 0);
		for( ; pos < m && que[pos].b == i; ++pos)
			ans[que[pos].id] = s[que[pos].a];
	}
	for( ; pos < m; ++pos) {
		long long &res = ans[que[pos].id];
		res = 0;
		for(int i = que[pos].a; i <= n; i += que[pos].b)
			res += a[i];
	}
	for(int i = 0; i < m; ++i)
		printf("%lld\n", ans[i]);
	return 0;
}
