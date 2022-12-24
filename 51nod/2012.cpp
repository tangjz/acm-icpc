#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + (int)1e3 + 1, mod = (int)1e9 + 7;
int n, seq[maxn], sa[maxn], rk[maxn], ht[maxn], c[maxn];
void SuffixArray() {
	int i, j, k, *x = rk, *y = ht, m = 256;
	memset(c, 0, m * sizeof(int));
	for(i = 0; i < n; ++i) ++c[x[i] = seq[i]];
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
		swap(x, y);
		j = 1, x[sa[0]] = 0;
		for(i = 1; i < n; ++i)
			x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? j - 1 : j++;
		x[n] = j;
		if(j >= n) break;
	}
	for(i = 0; i < n; ++i) rk[sa[i]] = i;
	ht[0] = 0;
	for(i = k = 0; i < n; ++i) {
		if(k) --k;
		if(!rk[i]) continue;
		for(j = sa[rk[i] - 1]; seq[i + k] == seq[j + k]; ++k);
		ht[rk[i]] = k;
	}
}
int lim[maxn];
inline int calc(int lim, int upp) {
	return min(lim, upp) + 1;
}
inline int calc(int lim, int L, int R) {
	if(L <= R)
		return calc(lim, R) - (L ? calc(lim, L - 1) : 0);
	return lim - (R + 1 < L ? calc(lim, R + 1, L - 1) : 0);
}
int main() {
	int m, q, vL, vR;
	scanf("%d%d%d%d", &m, &q, &vL, &vR);
	for(int i = 0; i < m; ++i) {
		static char buf[maxn];
		scanf("%s", buf);
		int len = strlen(buf);
		for(int j = 0; j < len; ++j) {
			lim[n] = len - j;
			seq[n++] = buf[j];
		}
		lim[n] = 0;
		seq[n++] = '$';
	}
	seq[--n] = 0;
	SuffixArray();
	LL ans = 0;
	for(int i = 0; i < n; ++i) {
		int low = ht[i] + 1, upp = lim[sa[i]];
		if(low > upp)
			continue;
		int hh = 0;
		for(int j = 1; j <= q && j <= upp; ++j) {
			hh = (26LL * hh + seq[sa[i] + j - 1] - 97) % mod;
			if(j >= low)
				ans += vL <= hh && hh <= vR;
		}
		if(upp > q) {
			(hh -= q) < 0 && (hh += mod);
			int pL = vL - hh, pR = vR - hh;
			pL < 0 && (pL += mod);
			pR < 0 && (pR += mod);
			(--low) < q && (low = q);
			ans += calc(upp, pL, pR) - calc(low, pL, pR);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
