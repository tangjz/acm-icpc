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

const int maxn = 51;

int t, n, m, match[maxn];
bool e[maxn][maxn], vis[maxn];
bool path(int u) {
	for(int v = 0; v < n; ++v) {
		if(vis[v] || !e[u][v])
			continue;
		vis[v] = 1;
		if(match[v] == -1 || path(match[v])) {
			match[v] = u;
			return 1;
		}
	}
	return 0;
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &m, &n);
		for(int i = 0; i < n; ++i) {
			match[i] = -1;
			for(int j = 0; j < n; ++j)
				e[i][j] = 1;
		}
		while(m--) {
			static char a[maxn], b[maxn];
			scanf("%s%s", a, b);
			for(int i = 0; i < n; ++i)
				for(int j = 0; j < n; ++j)
					e[i][j] &= a[j] == b[i];
		}
		bool chk = 1;
		for(int i = n - 1; i >= 0; --i) {
			memset(vis, 0, n * sizeof(bool));
			if(!path(i)) {
				chk = 0;
				break;
			}
		}
		if(chk) {
			for(int i = 0; i < n; ++i)
				printf("%d%c", match[i] + 1, " \n"[i == n - 1]);
		} else {
			puts("-1");
		}
	}
	return 0;
}