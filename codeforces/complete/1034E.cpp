#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ULL;
const int maxd = 21, maxn = 1 << maxd | 1;
int n, all;
ULL odd, even, f[maxn], g[maxn], h[maxn];
char sz[maxn], r[maxn], b[maxn];
inline void inc0(ULL &x, ULL y) {
}
inline void inc1(ULL &x, ULL y) {
	ULL a = x & odd, b = x & even, c = y & odd, d = y & even;
	ULL e = a & c, f = a | c, g = b & d, h = b | d;
	x = e ^ f ^ (g << 1) ^ g ^ h;
}
inline void inc2(ULL &x, ULL y) {
	ULL a = x & odd, b = x & even, c = (y & even) << 1;
	ULL e = a & c, f = a | c;
	x = e ^ f ^ b;
}
inline void inc3(ULL &x, ULL y) {
	inc1(x, y);
	inc2(x, y);
}
void (*inc[])(ULL &, ULL) = {inc0, inc1, inc2, inc3};
int main() {
	int i, j;
	scanf("%d%s%s", &n, r, b);
	all = 1 << n;
	for(i = 0; i < (n + 1) << 1; ++i)
		(i & 1 ? odd : even) |= 1ULL << i;
	for(i = 1; i < all; ++i)
		sz[i] = sz[i >> 1] + (i & 1);
	for(i = 0; i < all; ++i)
		f[i] |= (ULL)(r[i] & 3) << (sz[i] + sz[i]);
	for(i = 0; i < all; ++i)
		g[i] |= (ULL)(b[i] & 3) << (sz[i] + sz[i]);
	for(i = 1; i < all; i <<= 1)
		for(j = 0; j < all; ++j)
			if(j & i) {
				inc1(f[j], f[j ^ i]);
				inc1(g[j], g[j ^ i]);
			}
	for(i = 0; i <= n; ++i)
		for(j = 0; j < all; ++j) {
			inc[f[j] & 3](h[j], g[j]);
			f[j] >>= 2;
			g[j] <<= 2;
		}
	for(i = 1; i < all; i <<= 1)
		for(j = 0; j < all; ++j)
			if(j & i)
				inc3(h[j], h[j ^ i]);
	for(i = 0; i < all; ++i)
		r[i] = '0' + ((h[i] >> (sz[i] + sz[i])) & 3);
	printf("%s\n", r);
	return 0;
}
