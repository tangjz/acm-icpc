#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = (int)1e6 + 1;
const char *pat = "URDL";
const int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
int t, n, r, c, nxt[maxn], pre[maxn], idx[maxn];
char col[maxn], buf[maxn];
bool vis[maxn], cir[maxn];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &r, &c);
		n = r * c;
		for(int i = 0; i < r; ++i)
			scanf("%s", col + i * c);
		for(int i = 0, idx = 0; i < r; ++i) {
			scanf("%s", buf);
			for(int j = 0; j < c; ++j, ++idx) {
				int o;
				for(o = 0; pat[o] != buf[j]; ++o);
				nxt[idx] = idx + dx[o] * c + dy[o];
			}
		}
		memset(vis, 0, n * sizeof(bool));
		memset(cir, 0, n * sizeof(bool));
		memset(idx, -1, n * sizeof(int));
		for(int i = 0; i < n; ++i) {
			if(vis[i])
				continue;
			int tot = 0;
			static int que[maxn];
			int j;
			for(j = i; !vis[j]; j = nxt[j]) {
				vis[j] = 1;
				que[tot++] = j;
			}
			if(idx[j] == -1) {
				int k;
				for(k = nxt[j]; idx[k] == -1; j = k, k = nxt[k]) {
					cir[k] = 1;
					idx[k] = k;
					pre[k] = j;
				}
			}
			for(j = tot - 1; j >= 0; --j) {
				int k = que[j];
				if(idx[k] == -1) {
					idx[k] = pre[idx[nxt[k]]];
					if(col[k] == '0')
						col[idx[k]] = '0';
				}
			}
		}
		int c0 = 0, c1 = 0;
		for(int i = 0; i < n; ++i)
			if(cir[i]) {
				++c0;
				c1 += col[i] == '0';
			}
		printf("%d %d\n", c0, c1);
	}
	return 0;
}