#include <bits/stdc++.h>
using namespace std;
const int maxn = 105, maxm = 3001, maxl = 17, maxd = 1 << 16 | 1, INF = 0x3f3f3f3f;
int N, M, S, T, flow, cost, lnk[maxn], d[maxn], p[maxn], a[maxn];
bool inq[maxn];
struct Edge {
	int nxt, v, w, c;
} e[maxm << 1 | 1];
void addEdge(int u, int v, int w, int c) {
	e[M] = (Edge){lnk[u], v, w, c};
	lnk[u] = M++;
	e[M] = (Edge){lnk[v], u, 0, -c};
	lnk[v] = M++;
}
bool BellmanFord() {
	memset(d, 0x3f, N * sizeof(int));
	memset(inq, 0, N * sizeof(bool));
	d[S] = 0;
	inq[S] = 1;
	p[S] = 0;
	a[S] = INF;
	queue<int> Q;
	Q.push(S);
	while(!Q.empty()) {
		int u = Q.front();
		Q.pop();
		inq[u] = 0;
		for(int it = lnk[u]; it != -1;it = e[it].nxt) {
			int v = e[it].v;
			if(e[it].w > 0 && d[v] > d[u] + e[it].c) {
				d[v] = d[u] + e[it].c;
				p[v] = it;
				a[v] = min(a[u], e[it].w);
				if(!inq[v]) {
					Q.push(v);
					inq[v] = 1;
				}
			}
		}
	}
	if(d[T] == INF)
		return 0;
	flow += a[T];
	cost += d[T] * a[T];
	for(int u = T; u != S; u = e[p[u] ^ 1].v) {
		e[p[u]].w -= a[T];
		e[p[u] ^ 1].w += a[T];
	}
	return 1;
}
int bits[maxd], rev[maxl][maxd], cnt[maxl], idx[maxd];
int n, m, len[maxn], msk[maxn], dc[maxn], mc[maxn], dis[maxn][maxd];
void scanBinary(int &len, int &msk) {
	static char buf[maxl];
	scanf("%s", buf);
	len = strlen(buf);
	msk = 0;
	for(int i = 0; i < len; ++i)
		msk = msk << 1 | (buf[i] - '0');
}
int main() {
	for(int i = 1; i < maxd; ++i)
		bits[i] = bits[i >> 1] + (i & 1);
	for(int i = 0; i < maxd; ++i)
		idx[i] = cnt[bits[i]]++;
	for(int i = 1; i < maxl; ++i)
		for(int j = 1; j < 1 << i; ++j)
			rev[i][j] = rev[i - 1][j >> 1] | ((j & 1) << (i - 1));
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanBinary(len[i], msk[i]);
	scanf("%d", &m);
	for(int i = n; i < n + m; ++i)
		scanBinary(len[i], msk[i]);
	for(int i = 0; i < n + m; ++i)
		scanf("%d", dc + i);
	for(int i = 0; i < n + m; ++i)
		scanf("%d", mc + i);
	for(int i = 0; i < n + m; ++i) {
		int LEN = len[i], *DIS = dis[i], qL = 0, qR = 0;
		static int que[maxd];
		memset(DIS, -1, cnt[bits[msk[i]]] * sizeof(int));
		que[qR++] = msk[i];
		DIS[idx[msk[i]]] = 0;
		while(qL < qR) {
			int u = que[qL++];
			for(int len = 2; len <= LEN; ++len) {
				int all = (1 << len) - 1;
				for(int L = 0, R = L + len - 1; R < LEN; ++L, ++R) {
					int msk = (u >> L) & all;
					int v = u ^ ((msk ^ rev[len][msk]) << L);
					if(DIS[idx[v]] == -1) {
						DIS[idx[v]] = DIS[idx[u]] + 1;
						que[qR++] = v;
					}
				}
			}
		}
	}
	N = n + m + 4;
	M = 0;
	int PS = N - 4;
	int PT = N - 3;
	S = N - 2;
	T = N - 1;
	memset(lnk, -1, N * sizeof(int));
	for(int i = 0; i < n; ++i) {
		addEdge(S, i, 1, 0);
		addEdge(PS, T, 1, 0);
		addEdge(i, PT, 1, dc[i]);
	}
	for(int i = n; i < n + m; ++i) {
		addEdge(S, PT, 1, 0);
		addEdge(i, T, 1, 0);
		addEdge(PS, i, 1, dc[i]);
	}
	for(int i = 0; i < n; ++i)
		for(int j = n; j < n + m; ++j) {
			if(len[i] != len[j] || bits[msk[i]] != bits[msk[j]])
				continue;
			int low = INF;
			for(int k = 0; k < cnt[bits[msk[i]]]; ++k)
				if(dis[i][k] != -1 && dis[j][k] != -1)
					low = min(low, mc[i] * dis[i][k] + mc[j] * dis[j][k]);
			addEdge(i, j, 1, low);
		}
	addEdge(PT, PS, INF, 0);
	while(BellmanFord());
	printf("%d\n", cost);
	return 0;
}
