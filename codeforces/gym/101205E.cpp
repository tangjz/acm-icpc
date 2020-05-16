#include <bits/stdc++.h>
using namespace std;
const int maxn = 77;
int n, m, ans, seq[maxn], path[maxn];
bitset<maxn> e[maxn], cur, fin, msk[maxn];
bool vis[maxn];
void dfs(int dep, int las) {
	if(dep >= ans)
		return;
	if(msk[dep] == fin) {
		ans = dep;
		for(int i = 0; i < dep; ++i)
			seq[i] = path[i];
		return;
	}
	for(int i = las; i < n; ++i) {
		msk[dep + 1] = msk[dep] | e[i];
		if(msk[dep + 1] == msk[dep])
			continue;
		path[dep] = i;
		dfs(dep + 1, i + 1);
	}
}
int main() {
	for(int Case = 1; scanf("%d", &n) == 1; ++Case) {
		fin.reset();
		for(int i = 0; i < n; ++i) {
			fin.set(i);
			e[i].reset();
			for(int j = 0, x; j < n; ++j) {
				scanf("%1d", &x);
				e[i][j] = x;
			}
			e[i][i] = 1;
		}
		cur.reset();
		memset(vis, 0, sizeof vis);
		for(ans = 0; cur != fin; ++ans) {
			int deg = 0;
			for(int i = 0; i < n; ++i)
				if(!vis[i]) {
					int tmp = (e[i] & (fin ^ cur)).count();
					if(tmp > deg) {
						seq[ans] = i;
						deg = tmp;
					}
				}
			vis[seq[ans]] = 1;
			cur |= e[seq[ans]];
		}
		msk[0].reset();
		dfs(0, 0);
		printf("Case %d: %d ", Case, ans);
		for(int i = 0; i < ans; ++i)
			printf("%d%c", seq[i] + 1, " \n"[i == ans - 1]);
	}
	return 0;
}
