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

const int maxn = (int)1e5 + 3, maxn2 = maxn << 1 | 1;

int t, n, dep[maxn], idx[maxn], pL[maxn], pR[maxn], tot, cL[maxn2], cR[maxn2], upp[maxn2];
set<int> sp[maxn];
bool fir;
void dfs(int u) {
	if(u <= n)
		return;
	if(fir) {
		fir = 0;
	} else {
		printf(" ");
	}
	printf("%d", upp[cL[u]]);
	dfs(cL[u]);
	dfs(cR[u]);
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			sp[i].clear();
		pR[0] = 1;
		for(int i = 1; i <= n; ++i) {
			scanf("%d", dep + i);
			idx[i] = i;
			pL[i] = i - 1;
			pR[i] = i + 1;
			upp[i] = i;
			sp[dep[i]].insert(i);
		}
		pL[n + 1] = n;
		tot = n;
		bool chk = 1;
		for(int mx = n - 1; mx >= 1; --mx) {
			if(!sp[mx].size())
				continue;
			int u = *sp[mx].begin();
			int v = pR[u];
			if(v > n || dep[v] != mx) {
				chk = 0;
				break;
			}
			sp[mx].erase(u);
			sp[mx].erase(v);
			++tot;
			cL[tot] = idx[u];
			cR[tot] = idx[v];
			upp[tot] = upp[cR[tot]];
			pL[pR[u]] = pL[u];
			pR[pL[u]] = pR[u];
			idx[v] = tot;
			sp[--dep[v]].insert(v);
			if(sp[mx].size())
				++mx;
		}
		chk &= (int)sp[0].size() == 1;
		if(!chk) {
			puts("Impossible");
		} else {
			puts("Possible");
			fir = 1;
			dfs(tot);
			printf("\n");
		}
	}
	return 0;
}
