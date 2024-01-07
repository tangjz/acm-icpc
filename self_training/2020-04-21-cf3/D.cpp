#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = (int)2e5 + 1, maxv = maxn << 1 | 1;
int t, n, m, a[maxn], c[maxv];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		memset(c, 0, (m + m + 1) * sizeof(int));
		for(int i = 0, j = n - 1; i < j; ++i, --j) {
			int u = a[i], v = a[j];
			if(u > v)
				swap(u, v);
			++c[u + 1];
			--c[v + m + 1];
			++c[u + v];
			--c[u + v + 1];
		}
		int mx = 0;
		for(int i = 1; i <= m + m; ++i)
			mx = max(mx, c[i] += c[i - 1]);
		printf("%d\n", n - mx);
	}
	return 0;
}