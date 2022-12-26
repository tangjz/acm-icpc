#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)3e5 + 1, seed = (int)3e5 + 17, mod0 = (int)1e9 + 7, mod1 = (int)1e9 + 9;
inline int mod_add(int x, int y, int p) {
	return (x += y) < p ? x : x - p;
}
inline int mod_sub(int x, int y, int p) {
	return (x -= y) < 0 ? x + p : x;
}
inline int mod_mul(int x, int y, int p) {
	return (LL)x * y % p;
}
inline int mod_inv(int x, int p) {
	int y = p, u = 1, v = 0;
	while(y) {
		int q = x / y;
		swap(x, y);
		y -= q * x;
		swap(u, v);
		v -= q * u;
	}
	return u < 0 ? u + p : u;
}
struct Hash {
	int v0, v1;
	bool operator == (Hash const &t) const {
		return v0 == t.v0 && v1 == t.v1;
	}
	Hash operator + (Hash const &t) const {
		return (Hash){mod_add(v0, t.v0, mod0), mod_add(v1, t.v1, mod1)};
	}
	Hash operator - (Hash const &t) const {
		return (Hash){mod_sub(v0, t.v0, mod0), mod_sub(v1, t.v1, mod1)};
	}
	Hash operator * (Hash const &t) const {
		return (Hash){mod_mul(v0, t.v0, mod0), mod_mul(v1, t.v1, mod1)};
	}
} pw[maxn], ipw[maxn], hh[maxn], ihh[maxn];
inline Hash getPrefixHash(int tot, int itot, int len) {
	return len <= itot ? (ihh[itot] - ihh[itot - len]) * pw[itot - 1] : (itot ? ihh[itot] * pw[itot - 1] + hh[len - itot] * pw[itot] : hh[len]);
}
int t, n, m, tot, itot, a[maxn], b[maxn], que[maxn], ique[maxn];
bool ban[maxn];
int main() {
	pw[0] = ipw[0] = (Hash){1, 1};
	pw[1] = (Hash){seed, seed};
	ipw[1] = (Hash){mod_inv(seed, mod0), mod_inv(seed, mod1)};
	for(int i = 2; i < maxn; ++i) {
		pw[i] = pw[i - 1] * pw[1];
		ipw[i] = ipw[i - 1] * ipw[1];
	}
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		memset(ban, 0, n * sizeof(bool));
		while(m--) {
			int x;
			scanf("%d", &x);
			ban[--x] = 1;
		}
		memcpy(b, a, n * sizeof(int));
		sort(b, b + n);
		m = unique(b, b + n) - b;
		for(int i = 0; i < n; ++i)
			a[i] = lower_bound(b, b + m, a[i]) - b;
		tot = itot = 0;
		hh[0] = ihh[0] = (Hash){0, 0};
		for(int i = 0; i < n; ) {
			int ptot = tot, pitot = itot;
			for( ; i < n; ++i) {
				que[tot++] = a[i];
				ique[itot++] = a[i];
				if(!ban[i])
					break;
			}
			if(i == n) {
				itot = pitot;
				break;
			}
			++i;
			for(int j = ptot; j < tot; ++j)
				hh[j + 1] = hh[j] + pw[j] * (Hash){que[j] + 1, que[j] + 1};
			for(int j = pitot; j < itot; ++j)
				ihh[j + 1] = ihh[j] + ipw[j] * (Hash){ique[j] + 1, ique[j] + 1};
			int L = 0, R = ptot + itot;
			while(L < R) {
				int M = (L + R + 1) >> 1;
				if(getPrefixHash(ptot, itot, M) == getPrefixHash(tot, pitot, M)) {
					L = M;
				} else {
					R = M - 1;
				}
			}
			int lft = L < itot ? ique[itot - L - 1] : que[L - itot];
			int rht = L < pitot ? ique[pitot - L - 1] : que[L - pitot];
			if(L == ptot + itot || lft >= rht)
				itot = pitot;
			else
				tot = ptot;
		}
		const int prd = 37, mod = 20181125;
		int ans = 0;
		for(int i = tot - 1; i >= 0; --i)
			ans = ((LL)ans * prd + b[que[i]]) % mod;
		for(int i = 0; i < itot; ++i)
			ans = ((LL)ans * prd + b[ique[i]]) % mod;
		printf("Case %d: %d\n", Case, ans);
	}
	return 0;
}
