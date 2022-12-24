#include <bits/stdc++.h>
using namespace std;
const int maxn = 100, maxd = 10;
int n, m, nxt[maxn + 1][maxd + 1], tot, idx[2][maxn + 1][maxn + 1];
int que[maxn * maxn << 1 | 1][3], trans[maxn * maxn << 1 | 1][maxd + 1];
bool stp[maxn + 1];
vector<int> e[maxn << 1 | 1][maxd + 1];
void modify(vector<int> &nxt, int &u, int &v, int &w) {
	for(vector<int>::iterator it = nxt.begin(); it != nxt.end(); ++it)
		if(*it < n) {
			assert(u == n || u == *it);
			u = *it;
		} else if(*it < n << 1) {
			assert(v == n || v == *it - n);
			v = *it - n;
		} else {
			w = 0;
		}
}
int main() {
	scanf("%d%d", &m, &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", stp + i);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < maxd; ++j) {
			scanf("%d", nxt[i] + j);
			int k = --nxt[i][j];
			e[i][j].push_back(k);
			if(j + 1 < maxd) {
				e[i][j + 1].push_back(n + k);
			} else {
				e[n + i][j + 1 - maxd].push_back(n + k);
			}
			if(stp[k]) {
				if(j + m < maxd) {
					e[i][j + m].push_back(n << 1);
				} else {
					e[n + i][j + m - maxd].push_back(n << 1);
				}
			}
		}
	memset(idx, -1, sizeof idx);
	que[tot][0] = 0;
	que[tot][1] = n;
	que[tot][2] = 1;
	idx[1][n][0] = tot++;
	for(int i = 0; i < tot; ++i)
		for(int j = 0; j < maxd; ++j) {
			int u = n, v = n, w = 1;
			if(que[i][0] < n)
				modify(e[que[i][0]][j], u, v, w);
			if(que[i][1] < n)
				modify(e[n + que[i][1]][j], u, v, w);
			if(que[i][2] < 1)
				modify(e[n << 1][j], u, v, w);
			if(idx[w][v][u] == -1) {
				que[tot][0] = u;
				que[tot][1] = v;
				que[tot][2] = w;
				idx[w][v][u] = tot++;
			}
			trans[i][j] = idx[w][v][u];
		}
	puts("Success");
	printf("%d\n", tot);
	for(int i = 0; i < tot; ++i)
		printf("%d%c", !que[i][2], " \n"[i == tot - 1]);
	for(int i = 0; i < tot; ++i)
		for(int j = 0; j < maxd; ++j)
			printf("%d%c", trans[i][j] + 1, " \n"[j == maxd - 1]);
	return 0;
}