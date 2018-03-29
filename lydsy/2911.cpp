#include <bits/stdc++.h>
using namespace std;
const int maxn = 501;
int n, m, tot, pre[maxn], suf[maxn], f[maxn][maxn];
struct Edge {
	int nxt, v;
	char ch;
} e[maxn << 1 | 1];
void addEdge(int u, int v, char ch) {
	e[tot] = (Edge){suf[u], v, ch};
	suf[u] = tot++;
	e[tot] = (Edge){pre[v], u, ch};
	pre[v] = tot++;
}
int F(int L, int R) {
	int &ret = f[L][R];
	if(ret != -1)
		return ret;
	if(L == R)
		return ret = 1;
	ret = 0;
	for(int it = suf[L]; it != -1; it = e[it].nxt) {
		if(e[it].v == R)
			++ret;
		for(int jt = pre[R]; jt != -1; jt = e[jt].nxt)
			if(e[jt].ch == e[it].ch)
				ret += F(e[it].v, e[jt].v);
	}
	return ret;
}
char buf[maxn];
int main() {
	scanf("%d", &m);
	for(int i = 0; i <= m; ++i, ++n)
		pre[n] = suf[n] = -1;
	for(int i = 0; i < m; ++i) {
		scanf("%s", buf);
		int len = strlen(buf), las = i;
		for(int j = 0; j < len - 1; ++j, las = n++) {
			pre[n] = suf[n] = -1;
			addEdge(las, n, buf[j]);
		}
		addEdge(las, i + 1, buf[len - 1]);
	}
	for(int i = 0; i < m; ++i) {
		scanf("%s", buf);
		int len = strlen(buf), las = i;
		for(int j = 0; j < len - 1; ++j, las = n++) {
			pre[n] = suf[n] = -1;
			addEdge(las, n, buf[j]);
		}
		addEdge(las, i + 1, buf[len - 1]);
	}
	memset(f, -1, sizeof f);
	printf("%d\n", F(0, m));
	return 0;
}
