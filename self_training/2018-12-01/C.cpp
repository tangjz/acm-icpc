#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e6 + 1;
int t, n, fa[maxn], w[maxn], ord[maxn], rem[maxn], sg[maxn];
bool vis[maxn];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		memset(rem + 1, 0, n * sizeof(int));
		for(int i = 2; i <= n; ++i) {
			scanf("%d%d", fa + i, w + i);
			++rem[fa[i]];
		}
		int tot = 0;
		for(int i = 1; i <= n; ++i) {
			if(!rem[i])
				ord[++tot] = i;
			sg[i] = vis[i] = 0;
		}
		for(int i = 1; i <= tot; ++i) {
			int u = ord[i], p = fa[u];
			if(!p)
				continue;
			if(!(--rem[p]))
				ord[++tot] = p;
			sg[p] ^= w[u] == 1 ? sg[u] + 1 : sg[u] ^ (w[u] & 1);
		}
		tot = 0;
		rem[1] = 0;
		for(int i = n - 1; i >= 0; --i) {
			int u = ord[i], p = fa[u];
			if(rem[p] == -1) {
				rem[u] = -1;
				continue;
			}
			rem[u] = rem[p] ^ sg[p] ^ (w[u] == 1 ? sg[u] + 1 : sg[u] ^ (w[u] & 1));
			int tmp = w[u] == 1 ? 0 : (w[u] == 2 ? sg[u] + 1 : sg[u] ^ !(w[u] & 1));
			if(rem[u] == tmp) {
				++tot;
				vis[u] = 1;
			}
			if(w[u] == 1) {
				--rem[u];
			} else {
				rem[u] ^= w[u] & 1;
			}
		}
		printf("%d\n", tot);
		for(int i = 1, fir = 1; i <= n; ++i)
			if(vis[i]) {
				if(fir) {
					fir = 0;
				} else {
					putchar(' ');
				}
				printf("%d", i);
			}
		putchar('\n');
	}
	return 0;
}