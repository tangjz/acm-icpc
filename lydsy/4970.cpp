#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1.1e6 + 1;
int n, a[maxn], m, stk[maxn], ch[2][maxn], dep[maxn], pos[maxn << 1 | 1], ans[2][maxn];
void dfs(int u, int low) {
	int las = u, &cur = pos[a[u] + n - u];
	if(ch[0][u]) {
		dep[ch[0][u]] = dep[u] + 1;
		dfs(ch[0][u], dep[u] + 1);
	} else {
		if(cur && dep[cur] >= low && !(m && cur <= ans[0][m] && ans[1][m] <= u)) {
			ans[0][++m] = cur;
			ans[1][m] = u;
		}
		swap(cur, las);
	}
	if(ch[1][u]) {
		dep[ch[1][u]] = dep[u] + 1;
		dfs(ch[1][u], low);
	}
	if(!ch[0][u])
		swap(cur, las);
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		for( ; m && a[stk[m]] > a[i]; --m);
		if(m)
			ch[1][stk[m]] = i;
		stk[++m] = i;
	}
	m = 0;
	for(int i = n; i > 0; --i) {
		for( ; m && a[stk[m]] > a[i]; --m);
		if(m)
			ch[0][stk[m]] = i;
		stk[++m] = i;
	}
	m = 0;
	dfs(1, dep[1]);
	printf("%d\n", m);
	for(int i = 1; i <= m; ++i)
		printf("%d %d\n", ans[0][i], ans[1][i]);
	return 0;
}
