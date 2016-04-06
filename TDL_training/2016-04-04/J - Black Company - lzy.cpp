#include <cstdio>
#include <vector>
#include <algorithm>

using std::vector;
using std::sort;

#define N 100000

int n, m, a, b, c[N + 9], ind[N + 9], s[N + 9], p[N + 9];
vector<int> nei[N + 9], lnk[N + 9];
int l, r, q[N + 9];

bool cmp(int a, int b) {
	return c[a] < c[b];
}

int find(int e) {
	return e == p[e]? e : p[e] = find(p[e]);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		p[i] = i;
		scanf("%d", c + i);
	}
	scanf("%d", &m);
	while (m--) {
		scanf("%d%d", &a, &b);
		nei[a].push_back(b);
		nei[b].push_back(a);
	}
	for (int i = 1; i <= n; ++i) {
		nei[i].push_back(i);
		sort(nei[i].begin(), nei[i].end(), cmp);
		int j = 0;
		for (auto k: nei[i]) {
			if (j && c[j] == c[k]) p[find(k)] = find(j);
			j = k;
		}
	}
	for (int i = 1; i <= n; ++i) {
		int j = 0;
		for (auto k: nei[i]) {
			if (j && c[j] != c[k])
				++ind[find(k)], lnk[find(j)].push_back(find(k));
			j = k;
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (i == find(i)) {
			s[i] = 1;
			if (!ind[i]) q[r++] = i;
		}
	}
	for (l = 0; l < r; ++l) {
		auto u = q[l];
		for (auto v: lnk[u]) {
			if (s[v] <= s[u]) s[v] = s[u] + 1;
			if (!--ind[v]) {
				q[r++] = v;
			}
		}
	}
	long long sum = 0;
	for (int i = 1; i <= n; ++i) sum += s[find(i)];
	printf("%lld\n", sum);
	return 0;
}
