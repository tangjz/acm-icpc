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

const int maxn = (int)1e5 + 1, mod = (int)1e9 + 7;

int t, n, m;

int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		static char buf[11];
		int len = sprintf(buf, "%d", n);
		m = 0;
		for(int i = 0; i < len; ++i)
			m += buf[i] - '0';
		int cnt = 0;
		for(int i = 1; i <= m; ++i)
			cnt += m % i == 0 && n % i == 0;
		printf("%d\n", cnt);
		for(int i = 1; i <= m; ++i)
			if(m % i == 0 && n % i == 0) {
				if(i > 1)
					printf(" ");
				printf("%d", i);
			}
		printf("\n");
	}
	return 0;
}