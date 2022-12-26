#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)403;
char s[maxn], t[maxn];
int n, e[maxn][maxn], m, ord[maxn], match[maxn];
int tot, que[maxn], perm[maxn];
LL dis[maxn];
bool inq[maxn];
inline void rebuild(int n, int *arr) {
	for(int i = 0; i < n; ++i)
		swap(arr[i], arr[i + rand() % (n - i)]);
}
bool augment(int u) {
	que[tot++] = u;
	if(inq[u])
		return 1;
	inq[u] = 1;
	rebuild(m, perm);
	for(int i = 0; i < m; ++i) {
		int v = perm[i];
		if(inq[v] || match[u] == v)
			continue;
		int p = match[v];
		LL tmp = dis[u] - e[u][v] + e[v][p];
		if(dis[p] < tmp) {
			dis[p] = tmp;
			que[tot++] = v;
			if(augment(p))
				return 1;
			--tot;
		}
	}
	inq[u] = 0;
	--tot;
	return 0;
}
LL calc() {
	long long ans = 0;
	for(int i = 0; i < m; ++i)
		if(ord[i] < match[ord[i]])
			ans += e[ord[i]][match[ord[i]]];
	return ans;
}
int main() {
	scanf("%d%s%s", &n, s, t);
	for(int i = 0; i <= n; ++i)
		for(int j = i + 1; j <= n; ++j) {
			scanf("%d", e[i] + j);
			e[j][i] = e[i][j];
		}
	for(int i = 0; i <= n; ++i)
		for(int j = 0; j <= n; ++j)
			for(int k = 0; k <= n; ++k)
				e[j][k] = min(e[j][k], e[j][i] + e[i][k]);
	for(int i = 0; i < n; ++i)
		if(s[i] != t[i]) {
			int j = ord[m++] = i;
			for( ; i < n && s[i] != t[i]; ++i);
			ord[m++] = i;
			match[i] = j;
			match[j] = i;
		}
	srand(time(0));
	memcpy(perm, ord, m * sizeof(int));
	for(LL las = ~0ULL >> 1, cur; (cur = calc()) < las; las = cur) {
		bool upd = 1;
		while(upd) {
			for(int i = 0; i < m; ++i) {
				int u = ord[i];
				dis[u] = inq[u] = 0;
			}
			tot = upd = 0;
			for(int i = 0; i < m; ++i)
				if(augment(ord[i])) {
					upd = 1;
					int j = 0;
					for( ; que[j] != que[tot - 1]; ++j);
					for( ; j + 1 < tot; j += 2) {
						match[que[j]] = que[j + 1];
						match[que[j + 1]] = que[j];
					}
					break;
				}
		}
		rebuild(m, ord);
	}
	printf("%lld\n", calc());
	return 0;
}
