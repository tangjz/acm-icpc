#include <bits/stdc++.h>
using namespace std;
const int maxn = 51, maxm = 2501;
int n, m, cnt, idx[maxn][maxn], pre[maxm];
char buf[maxn][maxn];
vector<int> e[maxm];
bool cut[maxm];
int tarjan(int u, int fa) {
	int lowu = pre[u] = ++cnt, ch = 0;
	for(int &v : e[u]) {
		if(v == fa)
			continue;
		if(!pre[v]) {
			++ch;
			int lowv = tarjan(v, u);
			if(lowu > lowv)
				lowu = lowv;
			if(pre[u] <= lowv)
				cut[u] = 1;
		} else if(lowu > pre[v]) {
			lowu = pre[v];
		}
	}
	if(fa < 0 && ch == 1)
		cut[u] = 0;
	return lowu;
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		scanf("%s", buf[i]);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j) {
			if(buf[i][j] == '.')
				continue;
			idx[i][j] = ++cnt;
			if(i && idx[i - 1][j]) {
				e[cnt].push_back(idx[i - 1][j]);
				e[idx[i - 1][j]].push_back(cnt);
			}
			if(j && idx[i][j - 1]) {
				e[cnt].push_back(idx[i][j - 1]);
				e[idx[i][j - 1]].push_back(cnt);
			}
		}
	if(cnt < 3) {
		puts("-1");
		return 0;
	}
	cnt = 0;
	tarjan(1, -1);
	for(int i = 1; i <= cnt; ++i)
		if(cut[i]) {
			puts("1");
			return 0;
		}
	puts("2");
	return 0;
}