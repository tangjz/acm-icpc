#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e4 + 1, maxd = 1 << 16 | 1;
int n, m, L, R, a[maxn], b[maxn], s[maxn], lbt[maxd], mx;
bitset<maxn> msk;
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
int main() {
	lbt[0] = -1;
	for(int i = 1; i < maxd; ++i)
		lbt[i] = i & 1 ? 0 : lbt[i >> 1] + 1;
	scanf("%d%d%d", &n, &L, &R);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	int tp = n;
	n = 0;
	msk.set(0);
	for(int i = 1, typ; i <= tp; ++i) {
		scanf("%d", &typ);
		if(typ) {
			a[++n] = a[i];
		} else {
			b[++m] = a[i];
			msk |= msk << a[i];
		}
	}
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; ++i)
		s[i] = s[i - 1] + a[i];
	for(int i = n; i > mx; --i) {
		int pos = lowBit(msk, L, R);
		if(pos != -1) {
			int idx = upper_bound(s, s + i + 1, R - pos) - s - 1;
			mx = max(mx, idx);
		}
		msk |= msk << a[i];
	}
	msk.reset();
	msk.set(0);
	for(int i = mx + 1; i <= n; ++i)
		msk |= msk << a[i];
	msk.reset(s[n] - s[mx]);
	for(int i = 1; i <= m; ++i)
		msk |= msk << b[i];
	if(lowBit(msk, L, R - s[mx]) != -1)
		++mx;
	printf("%d\n", mx);
	return 0;
}
