#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

#define N 100000

typedef long long i64;

int n, tot, u, v, a[N + 9], x[N + 9];
vector<int> lnk[N + 9];
int c[N + 9];
bool root[N + 9];
i64 m, ans;

void add(int k, int d) {
	for (int i = k; i <= tot; i += i & -i) c[i] += d;
}

int get(int k) {
	int sum = 0;
	for (int i = k; i >= 1; i -= i & -i) sum += c[i];
	return sum;
}

void dfs(int u) {
	int k;
	if (a[u] && m / a[u] <= 1000000000) {
		k = upper_bound(x + 1, x + 1 + tot, m / a[u]) - x;
		//printf("%d %d %d\n", a[u], k, x[k]);
		ans += get(k - 1);

	} else {
		ans += get(tot);
	}
	k = lower_bound(x + 1, x + 1 + tot, a[u]) - x;
	add(k, +1);
	for (auto v: lnk[u]) dfs(v);
	add(k, -1);
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		ans = 0;
		memset(c, 0, sizeof c);
		scanf("%d%I64d", &n, &m);
		for (int i = 1; i <= n; ++i) {
			lnk[i].clear();
			root[i] = true;
			scanf("%d", a + i);
			x[i] = a[i];
		}
		sort(x + 1, x + 1 + n);
		tot = unique(x + 1, x + 1 + n) - (x + 1);
		//printf("%d\n", tot);
		for (int i = 1; i < n; ++i) {
			scanf("%d%d", &u, &v);
			lnk[u].push_back(v);
			root[v] = false;
		}

		for (int i = 1; i <= n; ++i)
			if (root[i]) {
				dfs(i);
				break;
			}
		//puts("!!!");
		printf("%I64d\n", ans);
	}
	return 0;
}
