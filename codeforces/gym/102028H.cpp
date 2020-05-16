#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)2e5 + 1, INF = ~0u >> 1;
int t, n, a[maxn], sa[maxn], rk[maxn], ht[maxn], tot, stk[maxn];
LL bit[2][maxn], ans;
void bit_upd(int x, LL v) {
	for(LL v2 = x * v; x > 0; x -= x & -x) {
		bit[0][x] += v;
		bit[1][x] += v2;
	}
}
LL bit_que(int x) {
	LL s = 0, s2 = 0;
	for(int y = x + 1; y <= n; y += y & -y) {
		s += bit[0][y];
		s2 += bit[1][y];
	}
	return s2 - x * s;
}
void suffix_array() {
	int i, j, k, *x = rk, *y = ht;
	static int c[maxn];
	memcpy(c, a, (n + 1) * sizeof(int));
	sort(c, c + n + 1);
	int m = unique(c, c + n + 1) - c;
	for(i = 0; i < n; ++i) x[i] = lower_bound(c, c + m, a[i]) - c;
	memset(c, 0, m * sizeof(int));
	for(i = 0; i < n; ++i) ++c[x[i]];
	for(i = 1; i < m; ++i) c[i] += c[i - 1];
	for(i = n - 1; i >= 0; --i) sa[--c[x[i]]] = i;
	for(k = 1; k <= n; k <<= 1, m = j) {
		j = 0;
		for(i = n - k; i < n; ++i) y[j++] = i;
		for(i = 0; i < n; ++i)
			if(sa[i] >= k) y[j++] = sa[i] - k;
		memset(c, 0, m * sizeof(int));
		for(i = 0; i < n; ++i) ++c[x[y[i]]];
		for(i = 0; i < m; ++i) c[i] += c[i - 1];
		for(i = n - 1; i >= 0; --i)
			sa[--c[x[y[i]]]] = y[i];
		std::swap(x, y);
		j = 1, x[sa[0]] = 0;
		for(i = 1; i < n; ++i)
			x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? j - 1 : j++;
		x[n] = j;
		if(j >= n) break;
	}
	for(i = 0; i < n; ++i) rk[sa[i]] = i;
	for(i = k = ht[0] = 0; i < n; ++i) {
		if(k) --k;
		if(!rk[i]) continue;
		for(j = sa[rk[i] - 1]; a[i + k] == a[j + k]; ++k);
		ht[rk[i]] = k;
	}
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		a[n] = 0;
		suffix_array();
		tot = ans = 0;
		memset(bit[0] + 1, 0, n * sizeof(LL));
		memset(bit[1] + 1, 0, n * sizeof(LL));
		a[n] = INF;
		stk[tot] = n;
		for(int i = n - 1; i >= 0; --i) {
			for( ; a[stk[tot]] < a[i]; --tot) {
				bit_upd(stk[tot - 1], -a[stk[tot]]);
				bit_upd(stk[tot], a[stk[tot]]);
			}
			stk[++tot] = i;
			bit_upd(stk[tot - 1], a[i]);
			bit_upd(i, -a[i]);
			ans += bit_que(i + ht[rk[i]]);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
