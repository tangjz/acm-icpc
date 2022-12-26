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

int t, n, mx, cnt[maxn];
char buf[maxn];

int main() {
	scanf("%d", &t);
	while(t--) {
		mx = 0;
		scanf("%s", buf);
		for(int i = 0, c = 1; ; ++i)
			if(buf[i] == '?') {
				++c;
			} else {
				for( ; mx <= c; cnt[mx++] = 0);
				++cnt[c];
				if(!buf[i])
					break;
				c = 1;
			}
		int ctr = 0, ans = 0;
		for(int i = mx - 1, j = maxd - 1; i >= 1; --i) {
			if(!cnt[i])
				continue;
			for( ; (1 << j) > i; --j);
			while(j && cnt[i] && !((ans >> j) & 1)) {
				ans |= 1 << j;
				--cnt[i];
				++cnt[i - (1 << j)];
				--j;
			}
			ctr ^= (i & 1) & (cnt[i] & 1);
		}
		printf("%d\n", ans ^ ctr);
	}
	return 0;
}
