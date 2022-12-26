#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;
typedef pair<DB, int> Edge;

namespace std {
	template<> struct hash<pair<int, int> > {
		size_t operator()(pair<int, int> const &t) const {
#if __SIZEOF_SIZE_T__ < __SIZEOF_LONG_LONG__
			return (size_t)t.first ^ t.second;
#else
			return (size_t)t.first << 32 | t.second;
#endif
		}
	};
}

const int maxn = (int)2e5 + 1, mod = (int)1e9 + 7;

int fact[maxn], iact[maxn];
int t, n, a[maxn], m, c[maxn], f[2][3], cur, pre = 1;

int main() {
	iact[1] = 1;
	for(int i = 2; i < maxn; ++i)
		iact[i] = mod - (int)(mod / i * (LL)iact[mod % i] % mod);
	fact[0] = iact[0] = 1;
	for(int i = 1; i < maxn; ++i) {
		fact[i] = (LL)fact[i - 1] * i % mod;
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
	}
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		n <<= 1;
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		m = 0;
		for(int i = 0; i < n; ++i) {
			if(!i || a[i - 1] != a[i])
				c[m++] = 0;
			++c[m - 1];
		}
		f[cur][1] = 1;
		f[cur][0] = f[cur][2] = 0;
		for(int i = 0; i < m; ++i) {
			swap(cur, pre);
			for(int j = 0; j < 3; ++j) {
				f[cur][j] = 0;
				for(int k = 0; k < 3; ++k) {
					if((c[i] + j - k) & 1 || !f[pre][k])
						continue;
					int lft = (c[i] + j - k) >> 1, rht = c[i] - lft;
					if(lft < 0 || rht < 0)
						continue;
					f[cur][j] = (f[cur][j] + (LL)fact[c[i]] * iact[lft] % mod * iact[rht] % mod * f[pre][k]) % mod;
				}
			}
		}
		printf("%d\n", f[cur][1]);
	}
	return 0;
}