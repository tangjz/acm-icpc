#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e6 + 1, maxd = 9;
int f[maxn], g[maxn], s[maxd][maxn];
int main() {
	f[0] = 1;
	for(int i = 1; i < maxn; ++i) {
		f[i] = f[i / 10] * (i % 10 ? i % 10 : 1);
		g[i] = i < 10 ? i : g[f[i]];
		for(int j = 0; j < maxd; ++j)
			s[j][i] = s[j][i - 1] + (g[i] == j + 1);
	}
	int q, l, r, k;
	scanf("%d", &q);
	while(q--) {
		scanf("%d%d%d", &l, &r, &k);
		printf("%d\n", s[k - 1][r] - s[k - 1][l - 1]);
	}
	return 0;
}
