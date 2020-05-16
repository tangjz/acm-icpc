#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1, maxd = 17;
void SuffixArray(int len, char str[], int sa[]) {
	int i, j, k, m = 256;
	static int x[maxn], y[maxn], c[maxn];
	memset(c, 0, m * sizeof(int));
	for(i = 0; i < len; ++i)
		++c[x[i] = str[i]];
	x[len] = m;
	for(i = 1; i < m; ++i)
		c[i] += c[i - 1];
	for(i = len - 1; i >= 0; --i)
		sa[--c[x[i]]] = i;
	for(k = 1; k <= len; k <<= 1, m = j) {
		for(i = len - k, j = 0; i < len; ++i)
			y[j++] = i;
		for(i = 0; i < len; ++i)
			if(sa[i] >= k)
				y[j++] = sa[i] - k;
		memset(c, 0, m * sizeof(int));
		for(i = 0; i < len; ++i)
			++c[x[y[i]]];
		for(i = 1; i < m; ++i)
			c[i] += c[i - 1];
		for(i = len - 1; i >= 0; --i)
			sa[--c[x[y[i]]]] = y[i];
		swap(x, y);
		for(i = j = 1, x[sa[0]] = 0; i < len; ++i)
			x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? j - 1 : j++;
		x[len] = j;
		if(j >= len)
			break;
	}
}
int t, n, m, q, tot, dep[maxn], fa[maxd][maxn];
vector<pair<char, int> > e[maxn];
int sa[maxn], pos[maxn], nxt[maxd][maxn];
char buf[maxn];
void dfs(int u, int L, int R) {
	sort(e[u].begin(), e[u].end());
	for(vector<pair<char, int> >::iterator it = e[u].begin(); it != e[u].end(); ++it) {
		char ch = it -> first;
		int v = it -> second;
		for( ; L <= R && buf[sa[L] + dep[u]] < ch; ++L)
			pos[sa[L]] = u;
		if(L <= R && buf[sa[L] + dep[u]] == ch) {
			dep[v] = dep[u] + 1;
			fa[0][v] = u;
			int pL = L, pR = R;
			while(pL < pR) {
				int pM = (pL + pR + 1) >> 1;
				if(buf[sa[pM] + dep[u]] == ch)
					pL = pM;
				else
					pR = pM - 1;
			}
			dfs(v, L, pL);
			L = pL + 1;
		}
	}
	for( ; L <= R; ++L)
		pos[sa[L]] = u;
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%d", &n, &m, &q);
		vector<pair<char, int> >().swap(e[0]);
		for(int i = 1; i <= n; ++i) {
			vector<pair<char, int> >().swap(e[i]);
			int p;
			char c;
			scanf("%d %c", &p, &c);
			e[p].push_back(make_pair(c, i));
		}
		scanf("%s", buf);
		SuffixArray(m, buf, sa);
		dep[0] = 0;
		memset(fa[0], 0, (n + 1) * sizeof(int));
		dfs(0, 0, m - 1);
		for(int d = 1; 1 << d <= n; ++d)
			for(int i = 1; i <= n; ++i)
				fa[d][i] = fa[d - 1][fa[d - 1][i]];
		int mx;
		for(int i = 0; i < m; ++i)
			nxt[0][i] = i + dep[pos[i]] + 1;
		for(mx = 1; 1 << mx <= m; ++mx)
			for(int i = 0; i < m; ++i)
				nxt[mx][i] = nxt[mx - 1][i] < m ? nxt[mx - 1][nxt[mx - 1][i]] : m + 1;
		while(q--) {
			int u, v, ctr = 0;
			scanf("%d%d", &u, &v);
			--u;
			for(int i = mx - 1; i >= 0; --i)
				if(nxt[i][u] < v) {
					u = nxt[i][u];
					ctr |= 1 << i;
				}
			if(nxt[0][u] == v) {
				printf("%d %d\n", ctr + 1, 0);
			} else {
				int p = pos[u];
				for(int i = dep[p] - (v - u), j = 0; i > 0; i >>= 1, ++j)
					if(i & 1)
						p = fa[j][p];
				printf("%d %d\n", ctr, p);
			}
		}
	}
	return 0;
}
