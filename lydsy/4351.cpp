#include <bits/stdc++.h>
typedef long long LL;
const int maxd = 1 << 7 | 1, mod = 998244353;
inline void mod_inc(int &x, int y) {
	(x += y) >= mod && (x -= mod);
}
inline void mod_inc_mul(int &x, int y, int z) {
	x = (x + (LL)y * z) % mod;
}
struct Poly {
	int deg, num[maxd];
	void assign(Poly const &t) {
		deg = t.deg;
		memcpy(num, t.num, (deg + 1) * sizeof(int));
	}
	void operator -= (Poly const &t) {
		if(deg < t.deg) {
			memset(num + deg + 1, 0, (t.deg - deg) * sizeof(int));
			deg = t.deg;
		}
		for(int i = 0; i <= t.deg; ++i)
			mod_inc(num[i], mod - t.num[i]);
	}
	void operator *= (Poly const &t) {
		static Poly res;
		res.deg = deg + t.deg;
		memset(res.num, 0, (res.deg + 1) * sizeof(int));
		for(int i = 0; i <= deg; ++i) if(num[i])
			for(int j = 0; j <= t.deg; ++j)
				mod_inc_mul(res.num[i + j], num[i], t.num[j]);
		assign(res);
	}
	void operator %= (Poly const &t) {
		assert(t.num[t.deg] == mod - 1);
		for( ; deg >= t.deg; --deg) if(num[deg])
			for(int i = 0; i <= t.deg; ++i)
				mod_inc_mul(num[deg - t.deg + i], num[deg], t.num[i]);
	}
} ;
int main(int argc, char const *argv[]) {
	LL n;
	int m;
	scanf("%lld%d", &n, &m);
	if(n < (1 << m)) {
		puts("0");
		return 0;
	}
	int o = 0;
	static Poly f[2];
	f[o].deg = 2;
	f[o].num[0] = f[o].num[1] = 1;
	f[o].num[2] = mod - 1;
	for(int i = 1; i < m; ++i) {
		o = !o;
		f[o].assign(f[!o]);
		mod_inc(f[o].num[0], 1);
		f[!o] *= f[!o];
		f[o] -= f[!o];
	}
	Poly &F = f[!o], &G = f[o];
	F.deg = F.num[1] = 1;
	F.num[0] = 0;
	int mx = 0;
	for(--n; (1LL << (mx + 1)) <= n; ++mx);
	while((--mx) >= 0) {
		F *= F;
		F %= G;
		if((n >> mx) & 1) {
			for(int i = F.deg; i >= 0; --i)
				F.num[i + 1] = F.num[i];
			F.num[0] = 0;
			++F.deg;
			F %= G;
		}
	}
	printf("%d\n", F.deg + 1 == G.deg ? F.num[F.deg] : 0);
	return 0;
}
