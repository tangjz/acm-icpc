#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 33, maxs = 5605;
int n, m, tot, pr[maxn], d[maxn], e[maxn], seq[maxn];
LL ans[maxs];
void dfs(int dep, int low, int rem) {
	if(!rem) {
		memset(e + 1, 0, m * sizeof(int));
		++e[m];
		for(int i = 0; i < dep; ++i)
			--e[seq[i]];
		for(int i = m - 1; i > 1; --i)
			e[i] += e[i + 1];
		LL res = 1;
		for(int i = m; i > 1; --i)
			if(d[i] == i) {
				for( ; e[i]--; res *= i);
			} else {
				e[d[i]] += e[i];
				e[i / d[i]] += e[i];
				e[i] = 0;
			}
		ans[tot++] = res;
		return;
	}
	if(dep == n)
		return;
	for(int i = low; i + i <= rem; ++i) {
		seq[dep] = i;
		dfs(dep + 1, i, rem - i);
	}
	if(low <= rem) {
		seq[dep] = rem;
		dfs(dep + 1, rem, 0);
	}
}
int main() {
	scanf("%d%d", &n, &m);
	--m;
	for(int i = 2; i <= m; ++i) {
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) <= m; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	tot = 0;
	dfs(0, 1, m);
	sort(ans, ans + tot);
	tot = unique(ans, ans + tot) - ans;
	for(int i = 0; i < tot; ++i)
		printf("%lld\n", ans[i]);
	return 0;
}
