#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)2e5 + 1, maxv = 5e5 + 1, maxd = 19;
int n, m, mx, st[maxd][maxv];
int main() {
	memset(st[0], -1, sizeof st[0]);
	scanf("%d%d", &n, &m);
	while(n--) {
		int L, R;
		scanf("%d%d", &L, &R);
		st[0][L] = max(st[0][L], R);
	}
	for(int i = 1; i < maxv; ++i)
		if(st[0][i - 1] >= i && st[0][i] < st[0][i - 1])
			st[0][i] = st[0][i - 1];
	for(mx = 1; (1 << mx) < maxv; ++mx)
		for(int i = 0; i < maxv; ++i)
			st[mx][i] = st[mx - 1][i] != -1 ? st[mx - 1][st[mx - 1][i]] : -1;
	while(m--) {
		int L, R;
		scanf("%d%d", &L, &R);
		if(st[mx - 1][L] < R) {
			puts("-1");
			continue;
		}
		int ans = 0;
		for(int i = mx - 1; i >= 0; --i)
			if(st[i][L] > L && st[i][L] < R) {
				L = st[i][L];
				ans |= 1 << i;
			}
		assert(st[0][L] >= R);
		printf("%d\n", ans + 1);
	}
	return 0;
}