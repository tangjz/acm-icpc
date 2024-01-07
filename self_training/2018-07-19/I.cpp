#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)3e5 + 9;
int m, len, rem[maxn], sa[maxn], rk[maxn], ht[maxn], f[maxn], g[maxn], c[maxn];
char pat[maxn], perm[3], buf[maxn];
LL ans;
void suffix_array() {
	int i, j, k, *x = f, *y = g;
	m = 256;
	memset(c, 0, m * sizeof(int));
	for(i = 0; i < len; ++i)
		++c[x[i] = buf[i]];
	for(i = 1; i < m; ++i)
		c[i] += c[i - 1];
	for(i = len - 1; i >= 0; --i)
		sa[--c[x[i]]] = i;
	for(k = 1; k <= len; k <<= 1, m = j) {
		j = 0;
		for(i = len - k; i < len; ++i)
			y[j++] = i;
		for(i = 0; i < len; ++i)
			if(sa[i] >= k)
				y[j++] = sa[i] - k;
		memset(c, 0, m * sizeof(int));
		for(i = 0; i < len; ++i)
			++c[x[y[i]]];
		for(i = 0; i < m; ++i)
			c[i] += c[i - 1];
		for(i = len - 1; i >= 0; --i)
			sa[--c[x[y[i]]]] = y[i];
		swap(x, y);
		j = 1;
		x[sa[0]] = 0;
		for(i = 1; i < len; ++i)
			x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? j - 1 : j++;
		x[len] = j;
		if(j >= len)
			break;
	}
	for(i = 0; i < len; ++i)
		rk[sa[i]] = i;
	for(i = k = 0; i < len; ++i) {
		if(k) --k;
		if(!rk[i]) {
			ht[rk[i]] = 0;
			continue;
		}
		for(j = sa[rk[i] - 1]; buf[i + k] == buf[j + k]; ++k);
		ht[rk[i]] = k;
	}
//	for(int i = 0; i < len; ++i)
//		printf("#%d %d (%d, %d): %s\n", i + 1, sa[i], ht[i], rem[sa[i]], buf + sa[i]);
}
int main() {
	while(scanf("%d", &m) == 1) {
		len = ans = 0;
		scanf("%s", pat);
		for(int i = 0, j = 0; i < m; i = j) {
			for( ; j < m && pat[i] == pat[j]; ++j);
			ans = max(ans, (LL)(j - i));
		}
		ans *= 3;
		for(int i = 0; i < 3; ++i)
			perm[i] = 'a' + i;
		do {
			for(int i = 0; i < m; ++i) {
				rem[len] = m - i;
				buf[len++] = perm[pat[i] - 'a'];
			}
			rem[len] = 0;
			buf[len++] = '$';
		} while(next_permutation(perm, perm + 3));
		buf[--len] = '\0';
		suffix_array();
		for(int i = 0; i < len; ++i) {
			int low = ht[i], upp = rem[sa[i]];
			ans += max(upp - low, 0);
		}
//		assert(ans % 6 == 0);
		ans /= 6;
		printf("%lld\n", ans);
	}
	return 0;
}
