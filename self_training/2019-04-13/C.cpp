#include <bits/stdc++.h>
using namespace std;
const int maxl = 51, maxs = (int)5e4 + 1, maxd = 26;
int t, n, tot;
struct Trie {
	int cnt, nxt[maxd];
} e[maxs];
int dfs(int u) {
	int adt = e[u].cnt;
	for(int i = 0; i < maxd; ++i)
		if(e[u].nxt[i])
			adt += dfs(e[u].nxt[i]);
	if(u > 0) {
		int tmp = min(adt - (adt & 1), 2);
		n += tmp;
		adt -= tmp;
	}
	return adt;
}
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		tot = 0;
		memset(e + (tot++), 0, sizeof e[0]);
		scanf("%d", &n);
		while(n--) {
			static char buf[maxl];
			scanf("%s", buf);
			int len = strlen(buf), rt = 0;
			for(int i = len - 1; i >= 0; --i) {
				int o = buf[i] - 'A';
				if(!e[rt].nxt[o]) {
					e[rt].nxt[o] = tot;
					memset(e + (tot++), 0, sizeof e[0]);
				}
				rt = e[rt].nxt[o];
			}
			++e[rt].cnt;
		}
		n = 0;
		dfs(0);
		printf("Case #%d: %d\n", Case, n);
	}
	return 0;
}