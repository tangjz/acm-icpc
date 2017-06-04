#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxn = 2000001, mod = 1000000007;
int t, n, h[maxn], dsu[maxn], m, ans;
char buf[maxn];
std::pair<int, int> e[maxn];
int dsu_find(int x) {
	return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
}
void dsu_merge(int u, int v) {
	if((u = dsu_find(u)) == (v = dsu_find(v)))
		return;
	if(dsu[u] > dsu[v])
		std::swap(dsu[u], dsu[v]);
	if(dsu[u] == dsu[v])
		--dsu[u];
	dsu[v] = u;
}
int main() {
	scanf("%s", buf);
	n = strlen(buf);
	for(int i = n - 1; i >= 0; --i) {
		buf[i << 1] = buf[i];
		buf[i << 1 | 1] = '#';
	}
	buf[n << 1] = '\0';
	n <<= 1;
	memset(dsu, -1, n * sizeof(int));
	for(int i = 0, mx = 0, id = 0; i < n; ++i) {
		h[i] = i < mx ? std::min(mx - i, h[(id << 1) - i]) : 1;
		for( ; h[i] <= i && buf[i - h[i]] == buf[i + h[i]]; ++h[i])
			dsu_merge(i - h[i], i + h[i]);
		if(mx < i + h[i]) {
			mx = i + h[i];
			id = i;
		}
	}
	for(int i = 0; i < n; ++i)
		if(i - h[i] >= 0 && i + h[i] < n) {
			int x = dsu_find(i - h[i]), y = dsu_find(i + h[i]);
			if(x < y)
				std::swap(x, y);
			e[m++] = std::make_pair(x, y);
		}
	sort(e, e + m);
	m = unique(e, e + m) - e;
	ans = 1;
	for(int i = 0, j = 0; i < n; i += 2)
		if(dsu_find(i) == i) {
			int val = 26;
			for( ; j < m && e[j].first == i; ++j, --val);
			ans = (LL)ans * val % mod;
		}
	printf("%d\n", ans);
	return 0;
}
