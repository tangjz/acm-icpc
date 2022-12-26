#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define N 1000
#define M 10000

const int inf = 0x3fffffff;

struct Edge {int v, w; Edge *x;} *e, *adj[N + 9], *lnk[N + 9], E[8 * M + 9];

int TT, n, m, u, v, w, S, T, s[N + 9];
Edge *pre[N + 9];
int fat[N + 9];
int l, r, que[N + 9];

inline
void add(int u, int v, int w, Edge *c[]) {
	*e = (Edge){v, w, c[u]};
	c[u] = e++;
}

void bfs() {
	memset(s, -1, sizeof s);
	s[que[(r = 0)++] = S] = 0;
	for (l = 0; l < r; ++l) {
		u = que[l];
		//printf("u: %d\n", u);
		for (Edge *p = adj[u]; p; p = p->x) {
			//printf("v: %d %d\n", p->v, s[p->v]);
			if (s[p->v] == -1) {
				s[que[r++] = p->v] = s[u] + 1;
			}
		}
	}
}

bool bfs(int S, int T) {
	for (int i = 1; i <= n; ++i) pre[i] = 0, fat[i] = 0;
	fat[que[(r = 0)++] = S] = -1;
	for (l = 0; l < r; ++l) {
		u = que[l];
		//printf("u: %d\n", u);
		for (Edge *p = lnk[u]; p; p = p->x) {
			//printf("%d - %d %d\n", u, p->v, p->w);
			if (!fat[p->v] && p->w) {
				//printf("%d - %d %d\n", u, p->v, p->w);
				pre[que[r++] = p->v] = p;
				fat[p->v] = u;
			}
		}
		if (pre[T]) return true;
	}
	return false;
}

int main() {
	scanf("%d", &TT);
	while (TT--) {
		scanf("%d%d", &n, &m);
		
		for (int i = 1; i <= n; ++i) {
			adj[i] = 0;
			lnk[i] = 0;
		}
		e = E;
		while (m--) {
			scanf("%d%d%d", &u, &v, &w);
			add(u, v, w, adj);
			add(v, u, w, adj);
		}
		S = n, T = 1;
		bfs();
		for (u = 1; u <= n; ++u) {
			for (Edge *p = adj[u]; p; p = p->x)
				if (s[u] + 1 == s[p->v]) {
					//printf("%d - %d %d\n", u, p->v, p->w);
					add(u, p->v, p->w, lnk);
					add(p->v, u, 0, lnk);
				}
		}
		int mxf = 0, det;
		while (bfs(S, T)) {
			det = inf;
			for (Edge *p = pre[T]; p; p = pre[fat[p->v]]) {
				//printf("%d %d\n", fat[p->v], p->v);
				det = min(det, p->w);
			}
			//printf("det: %d\n", det);
			for (Edge *p = pre[T]; p; p = pre[fat[p->v]]) {
				
				p->w -= det;
				E[(p - E) ^ 1].w += det;
			}
			mxf += det;
		}
		printf("%d\n", mxf);
	}
	return 0;
}

