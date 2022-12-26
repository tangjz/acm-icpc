#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e4 + 1, mod = (int)1e9 + 7;
int t, n, perm[maxn], f[maxn], bit[maxn], ans[maxn];
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) {
			scanf("%d", perm + i);
			f[i] = 1;
		}
		memset(ans + 1, 0, n * sizeof(int));
		ans[1] = n;
		for(int i = 2; i <= n; ++i) {
			memset(bit + 1, 0, n * sizeof(int));
			bool chk = 0;
			for(int j = 1; j <= n; ++j) {
				int o = perm[j], cur = 0;
				for(int x = o - 1; x > 0; x -= x & -x)
					(cur += bit[x]) >= mod && (cur -= mod);
				for(int x = o; x <= n; x += x & -x)
					(bit[x] += f[o]) >= mod && (bit[x] -= mod);
				f[o] = cur;
				chk |= f[o];
				(ans[i] += f[o]) >= mod && (ans[i] -= mod);
			}
			if(!chk)
				break;
		}
		printf("Case #%d:", Case);
		for(int i = 1; i <= n; ++i)
			printf(" %d", ans[i]);
		putchar('\n');
	}
	return 0;
}
