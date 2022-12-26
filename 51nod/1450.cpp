#include <stdio.h>
#include <algorithm>
const int maxn = (int)2e3 + 1;
int n, m, cur, pre = 1;
std::pair<int, int> p[maxn];
double f[2][maxn], ans;
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i) {
		scanf("%d%d", &p[i].second, &p[i].first);
		p[i].first = -p[i].first;
	}
	sort(p, p + n);
	for(int i = 1; i <= n; ++i) {
		std::swap(cur, pre);
		int low = p[i - 1].second, upp = -p[i - 1].first;
		for(int j = 0; j < i; ++j)
			f[cur][j] = (1000 + low * f[pre][j] + upp * f[pre][std::max(j - 1, 0)]) / (low + upp);
		f[cur][i] = (1000 + upp * f[pre][i - 1]) / upp;
	}
	printf("%.20f\n", f[cur][m - n]);
	return 0;
}
