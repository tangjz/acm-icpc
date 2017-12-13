#include <bits/stdc++.h>
using namespace std;
const int maxn = 5001, maxs = 101, INF = 0x3f3f3f3f;
int t, n, tot, f[maxn][2];
map<string, int> e[maxn];
int newNode() {
	map<string, int>().swap(e[tot]);
	f[tot][0] = f[tot][1] = 0;
	return tot++;
}
void dfs(int u) {
	for(auto &it : e[u]) {
		int v = it.second;
		dfs(v);
		f[u][0] += min(f[v][0], f[v][1] + 1);
		f[u][1] += min(f[v][1], f[v][0] + 1);
	}
}
char opt[maxs], path[maxs];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		tot = 0;
		newNode();
		while(n--) {
			scanf("%s%s", opt, path);
			int rt = 0;
			for(int i = 0, j; path[i]; i = j) {
				for(j = ++i; path[j] && path[j] != '/'; ++j);
				path[0] = path[j];
				path[j] = '\0';
				string cur = path + i;
				path[j] = path[0];
				if(!e[rt].count(cur))
					e[rt][cur] = newNode();
				rt = e[rt][cur];
			}
			int tag = opt[0] == 's';
			f[rt][tag] = 0;
			f[rt][tag ^ 1] = INF;
		}
		dfs(0);
		printf("%d\n", min(f[0][0], f[0][1] + 1));
	}
	return 0;
}
