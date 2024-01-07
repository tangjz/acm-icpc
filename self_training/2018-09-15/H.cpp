#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e6 + 1, maxn2 = maxn << 1 | 1;
int t, n, seq[maxn2], sa[maxn], rk[maxn], ht[maxn];
int typ[maxn2], ctr[maxn], pos[maxn], *cur = ht;
void sais(int n, int m, int seq[], int typ[], int pos[]) {
#define pushS(x) sa[cur[seq[x]]--] = x
#define pushL(x) sa[cur[seq[x]]++] = x
#define inducedSort(v) do { \
	memset(sa, -1, n * sizeof(int)); \
	memset(ctr, 0, m * sizeof(int)); \
	for(i = 0; i < n; ++i) ++ctr[seq[i]]; \
	for(i = 1; i < m; ++i) ctr[i] += ctr[i - 1]; \
	for(i = 0; i < m; ++i) cur[i] = ctr[i] - 1; \
	for(i = n1 - 1; i >= 0; --i) pushS(v[i]); \
	for(i = 1; i < m; ++i) cur[i] = ctr[i - 1]; \
	for(i = 0; i < n; ++i) if(sa[i] > 0 && typ[sa[i] - 1]) pushL(sa[i] - 1); \
	for(i = 0; i < m; ++i) cur[i] = ctr[i] - 1; \
	for(i = n - 1; i >= 0; --i) if(sa[i] > 0 && !typ[sa[i] - 1]) pushS(sa[i] - 1); \
} while(0)
	int n1 = typ[n - 1] = 0, ch = rk[0] = -1, *seq1 = seq + n;
	register int i, j, k, x, y;
	for(i = n - 2; i >= 0; --i) typ[i] = seq[i] == seq[i + 1] ? typ[i + 1] : (seq[i] > seq[i + 1]);
	for(i = 1; i < n; ++i) rk[i] = typ[i - 1] && !typ[i] ? (pos[n1] = i, n1++) : -1;
	inducedSort(pos);
	for(i = 0; i < n; ++i) {
		if((x = rk[sa[i]]) < 0)
			continue;
		if(ch < 1 || pos[x + 1] - pos[x] != pos[y + 1] - pos[y])
			++ch;
		else
			for(j = pos[x], k = pos[y]; j <= pos[x + 1]; ++j, ++k)
				if((seq[j] << 1 | typ[j]) != (seq[k] << 1 | typ[k])) {
					++ch;
					break;
				}
		seq1[y = x] = ch;
	}
	if(ch + 1 < n1)
		sais(n1, ch + 1, seq1, typ + n, pos + n1);
	else
		for(i = 0; i < n1; ++i) sa[seq1[i]] = i;
	for(i = 0; i < n1; ++i) seq1[i] = pos[sa[i]];
	inducedSort(seq1);
}
void SuffixArray() {
	int m = 101;
	register int i, j, k;
	memset(ctr, 0, m * sizeof(int));
	for(i = 0; i <= n; ++i) ctr[seq[i]] = 1;
	for(i = 1; i < m; ++i) ctr[i] += ctr[i - 1];
	for(i = 0; i <= n; ++i) seq[i] = ctr[seq[i]] - 1;
	sais(n + 1, ctr[m - 1], seq, typ, pos);
	for(i = 0; i < n; ++i) rk[sa[i] = sa[i + 1]] = i;
	for(i = k = ht[0] = 0; i < n; ++i) {
		if(k) --k;
		if(!rk[i]) continue;
		for(j = sa[rk[i] - 1]; seq[i + k] == seq[j + k]; ++k);
		ht[rk[i]] = k;
	}
}
int vtot, etot, lnk[maxn2], fa[maxn2], sz[maxn2], dis[maxn2], ord[maxn2];
struct Edge {
	int nxt, v;
} e[maxn2];
int newNode() {
	lnk[vtot] = -1;
	fa[vtot] = sz[vtot] = dis[vtot] = 0;
	return vtot++;
}
void addEdge(int u, int v, int w) {
	fa[v] = u;
	dis[v] = dis[u] + w;
	e[etot] = (Edge){lnk[u], v};
	lnk[u] = etot++;
}
void SuffixTree() {
	vtot = etot = 0;
	int rt = newNode(), last;
	addEdge(rt, last = newNode(), n - sa[0]);
	++sz[last];
	for(int i = 1; i < n; ++i) {
		int p = last;
		for( ; dis[p] > ht[i]; p = fa[p]);
		int dt = ht[i] - dis[p];
		if(dt > 0) {
			int q = newNode(), v = e[lnk[p]].v, w = dis[v] - dis[p];
			fa[q] = p;
			dis[q] = dis[p] + dt;
			e[lnk[p]].v = q;
			addEdge(q, v, w - dt);
			p = q;
		}
		addEdge(p, last = newNode(), n - sa[i] - ht[i]);
		++sz[last];
	}
	vtot = 0;
	ord[vtot++] = rt;
	for(int i = 0; i < vtot; ++i) {
		int u = ord[i];
		for(int it = lnk[u]; it != -1; it = e[it].nxt)
			ord[vtot++] = e[it].v;
	}
	for(int i = vtot - 1; i >= 0; --i) {
		int u = ord[i];
		for(int it = lnk[u]; it != -1; it = e[it].nxt)
			sz[u] += sz[e[it].v];
	}
}
int main() {
	static int cL, cR;
	static char buf[maxn];
	while(scanf("%s%d%d", buf, &cL, &cR) == 3) {
		n = strlen(buf);
		for(int i = 0; i < n; ++i)
			seq[i] = buf[i] - 'A' + 1;
		seq[n] = 0;
		SuffixArray();
		SuffixTree();
		long long ans = 0;
		for(int i = 1; i < vtot; ++i)
			if(sz[i] >= cL && sz[i] <= cR)
				ans += dis[i] - dis[fa[i]];
		printf("%lld\n", ans);
	}
	return 0;
}
