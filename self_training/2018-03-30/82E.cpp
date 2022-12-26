#include <bits/stdc++.h>
using namespace std;
const int maxn = 1001, maxd = 1 << 16 | 1;
int lbt[maxd];
int lowBit(bitset<maxn> const &msk, size_t const &low, size_t const &upp) {
	typedef unsigned long long _WordT;
	_WordT *seq = (_WordT *)&msk;
	size_t pL = low >> 6, pR = upp >> 6;
	size_t qL = low & 63, qR = upp & 63;
	for(size_t i = pL; i <= pR; ++i) {
		_WordT val = seq[i];
		if(i == pR && qR < 63)
			val &= (static_cast<_WordT>(1) << (qR + 1)) - 1;
		if(i == pL)
			val = (val >> qL) << qL;
		if(val != static_cast<_WordT>(0)) {
			size_t ret = i << 6;
			if((val & ((static_cast<_WordT>(1) << 32) - 1)) == static_cast<_WordT>(0)) {
				val >>= 32;
				ret |= 32;
			}
			if((val & ((static_cast<_WordT>(1) << 16) - 1)) == static_cast<_WordT>(0)) {
				val >>= 16;
				ret |= 16;
			}
			return ret + lbt[static_cast<int>(val & ((static_cast<_WordT>(1) << 16) - 1))];
		}
	}
	return -1;
}
int n, m, q;
bitset<maxn> e[maxn], dis[maxn][maxn], cur, nxt, tmp;
int main() {
	lbt[0] = -1;
	for(int i = 1; i < maxd; ++i)
		lbt[i] = i & 1 ? 0 : lbt[i >> 1] + 1;
	scanf("%d%d%d", &n, &m, &q);
	while(m--) {
		int u, v;
		scanf("%d%d", &u, &v);
		--u, --v;
		e[u].set(v);
		e[v].set(u);
	}
	for(int i = 0; i < n; ++i) {
		dis[i][0].set(i);
		cur = dis[i][0];
		nxt = cur | e[i];
		for(int j = 1; j < n; ++j) {
			tmp = nxt ^ cur;
			cur = dis[i][j] = nxt;
			for(int u = lowBit(tmp, 0, n - 1); u != -1; u = lowBit(tmp, u + 1, n - 1))
				nxt |= e[u];
			if(cur == nxt) {
				for(int k = j + 1; k < n; ++k)
					dis[i][k] = cur;
				break;
			}
		}
	}
	while(q--) {
		int c, u, v;
		cur.reset();
		scanf("%d", &c);
		while(c--) {
			scanf("%d%d", &u, &v);
			cur |= dis[--u][min(v, n - 1)];
		}
		printf("%d\n", (int)cur.count());
	}
	return 0;
}
