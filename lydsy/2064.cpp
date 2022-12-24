#include <bits/stdc++.h>
using namespace std;
const int maxn = 21, maxs = 1 << 20 | 1;
int n, m, f[maxs], g[maxs];
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", g + (1 << i));
	scanf("%d", &m);
	for(int i = n; i < n + m; ++i) {
		scanf("%d", g + (1 << i));
		g[1 << i] = -g[1 << i];
	}
	n += m;
	int all = (1 << n) - 1;
	for(int i = 1; i <= all; ++i) {
		for(int j = 1; j <= i; j <<= 1)
			if((i & j) && f[i] < f[i ^ j])
				f[i] = f[i ^ j];
		int lbt = i & -i;
		g[i] = g[lbt] + g[i ^ lbt];
		f[i] += !g[i];
	}
	printf("%d\n", n - f[all] - f[all]);
	return 0;
}