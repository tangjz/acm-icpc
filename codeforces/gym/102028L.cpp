#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const int maxn = (int)1e5 + 1, mod = (int)1e9 + 7;
int t, n, m, deg[maxn], ord[maxn], rnk[maxn], pos[maxn], sum[maxn];
vector<int> e[maxn];
inline LL C(int n, int m) {
	if(n < m)
		return 0;
	if(m == 1)
		return n;
	if(m == 2)
		return n * (n - 1LL) / 2;
	assert(m == 4);
	int a[4] = {n, n - 1, n - 2, n - 3};
	for(int i = 4; i >= 2; --i)
		for(int j = 0; j < 4; ++j)
			if(a[j] % i == 0) {
				a[j] /= i;
				break;
			}
	return (LL)a[0] * a[1] * a[2] * a[3];
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &m);
		memset(deg + 1, 0, n * sizeof(int));
		for(int i = 1; i <= m; ++i) {
			int u, v;
			scanf("%d%d", &u, &v);
			++deg[u];
			++deg[v];
			e[u].push_back(v);
			e[v].push_back(u);
		}
		LL ans1 = 0, ans2 = 0;
		for(int i = 1; i <= n; ++i) {
			int pre = 0;
			LL tmp1 = 0, tmp2 = 0;
			for(int &j : e[i]) {
				tmp1 += C(deg[j] - 1, 2);
				tmp2 += pre * C(deg[j] - 1, 1);
				pre += deg[j] - 1;
			}
			ans1 += tmp1 * C(deg[i] - 1, 1) + tmp2;
			if(ans1 < 0)
				ans1 = (ULL)ans1 % mod;
			ans1 += C(deg[i], 4);
			if(ans1 < 0)
				ans1 = (ULL)ans1 % mod;
			ord[i] = i;
		}
		sort(ord + 1, ord + n + 1, [&deg](int const &u, int const &v) {
			return deg[u] > deg[v];
		});
		for(int i = 1; i <= n; ++i)
			rnk[ord[i]] = i;
		memset(ord + 1, 0, n * sizeof(int));
		memset(pos + 1, 0, n * sizeof(int));
		for(int u = 1; u <= n; ++u) {
			for(int &v : e[u])
				if(rnk[u] < rnk[v])
					ord[v] = 1;
			for(int &v : e[u]) {
				if(rnk[u] > rnk[v])
					continue;
				for(int &w : e[v]) {
					if(rnk[v] < rnk[w] && ord[w])
						ans2 += deg[u] + deg[v] + deg[w] - 5;
					if(rnk[u] < rnk[w]) {
						if(pos[w] < u) {
							pos[w] = u;
							sum[w] = 0;
						}
						ans2 += sum[w]++;
					}
				}
			}
			for(int &v : e[u])
				ord[v] = 0;
			if(ans2 < 0)
				ans2 = (ULL)ans2 % mod;
		}
		ans1 = ans1 < mod ? ans1 : ans1 % mod;
		ans2 = ans2 < mod ? ans2 : ans2 % mod;
		(ans1 = (ans1 - 3LL * ans2) % mod) < 0 && (ans1 += mod);
		printf("%d\n", (int)ans1);
		for(int i = 1; i <= n; ++i)
			vector<int>().swap(e[i]);
	}
	return 0;
}
