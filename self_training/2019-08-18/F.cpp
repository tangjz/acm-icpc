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

const int maxd = 21, maxn = 1 << maxd | 1, mod = (int)1e9 + 7;

int t, n, m, seq[maxn], mx, f[maxd + 2][maxn];
char buf[maxn];
inline void mod_inc(int &x, int y) {
	(x += y) >= mod && (x -= mod);
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%s", buf);
		n = strlen(buf) + 1;
		m = 0;
		for(int i = 0, c = 1; i < n; ++i)
			if(buf[i] == '+') {
				++c;
			} else {
				seq[++m] = c;
				++c;
			}
		for(mx = 0; (1 << mx) <= n; ++mx);
		for(int i = 0; i <= mx; ++i)
			f[i][0] = 1;
		for(int i = 1, o = 1; i <= n; ++i) {
			if((n & i) == i)
				for(int j = 0; j <= mx; ++j) {
					f[j][i] = 0;
					if(j)
						mod_inc(f[j][i], f[j - 1][i]);
					if((i >> j) & 1)
						mod_inc(f[j][i], f[j][i ^ (1 << j)]);
				}
			if(o < m && i == seq[o]) {
				if((n & i) == i) {
					int adt = f[mx][i];
					for(int j = 0; j <= mx; ++j)
						mod_inc(f[j][i], adt);
				}
				++o;
			}
		}
		printf("%d %d\n", n, f[mx][n]);
	}
	return 0;
}
