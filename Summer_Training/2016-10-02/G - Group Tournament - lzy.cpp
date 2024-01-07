#include <cstdio>

#include <algorithm>

using namespace std;

#define N 100


struct Edge {int v, w; Edge *x, *inv;} *lnk[2 * N * N + 9], *e, E[64 * N * N + 9];

const int inf = 0x3fffffff;

int n, num, S, T, L, R;
char str[N + 9][N + 9];
Edge *fuck[N + 9][N + 9];
Edge *pre[2 * N * N + 9];
int fat[2 * N * N + 9];
int l, r, que[2 * N * N + 9];

void add(int u, int v, int w) {
	*e = (Edge) {v, w, lnk[u], 0};
	lnk[u] = e++;
}

void arc(int u, int v, int w) {
	add(u, v, w);
	add(v, u, 0);
	lnk[u]->inv = lnk[v];
	lnk[v]->inv = lnk[u];
}

bool bfs(int S, int T) {
	for (int i = 1; i <= T; ++i) pre[i] = 0, fat[i] = 0;
	fat[que[(r = 0)++] = S] = -1;
	for (l = 0; l < r; ++l) {
		int u = que[l];
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
	scanf("%d", &n);
	L = R = n + 1;
	e = E;
	for (int i = 1; i <= n; ++i) {
		scanf("%s", str[i] + 1);
		for (int j = 1; j < i; ++j) {
			if (str[i][j] == '.') {
				arc(R, i, 3);
				arc(R, j, 3);
			} else if (str[i][j] == 'l') {
				arc(R, i, 1);
				arc(R, j, 2);
			} else if (str[i][j] == 'L') {
				arc(R, i, 0);
				arc(R, j, 3);
			} else if (str[i][j] == 'w') {
				arc(R, i, 2);
				arc(R, j, 1);
			} else if (str[i][j] == 'W') {
				arc(R, i, 3);
				arc(R, j, 0);
			} 
			fuck[i][j] = lnk[R++];
		}
	}
	S = R, T = S + 1;
	for (int i = L; i < R; ++i)
		arc(S, i, 3);
	for (int i = 1; i <= n; ++i) {
		int c;
		scanf("%d", &c);
		arc(i, T, c);
	}
	int det;
	while (bfs(S, T)) {
		det = inf;
		for (Edge *p = pre[T]; p; p = pre[fat[p->v]]) {
			//printf("%d %d\n", fat[p->v], p->v);
			det = min(det, p->w);
		}
		//printf("det: %d\n", det);
		for (Edge *p = pre[T]; p; p = pre[fat[p->v]]) {
			//printf("%p %p\n", p, p->inv);
			p->w -= det;
			p->inv->w += det;
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j < i; ++j) {
			//printf("R: %d %d %d %d\n", R, i, j, fuck[i][j]->w);
			if (str[i][j] == '.') {
				if (fuck[i][j]->w == 3) str[j][i] = 'L', str[i][j] = 'W';
				if (fuck[i][j]->w == 2) str[j][i] = 'l', str[i][j] = 'w';
				if (fuck[i][j]->w == 1) str[j][i] = 'w', str[i][j] = 'l';
				if (fuck[i][j]->w == 0) str[j][i] = 'W', str[i][j] = 'L';
			}
		}
	}
	for (int i = 1; i <= n; ++i) puts(str[i] + 1);
	return 0;
}
