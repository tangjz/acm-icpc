#include <bits/stdc++.h>
using namespace std;
typedef double DB;
typedef pair<DB, int> Edge;
const DB INF = 1e20;
const int maxn = 201, maxs = 409, maxm = (int)1.7e5 + 1;
int t, n, xtot, xque[maxs], ytot, yque[maxs], c[maxs][maxs];
struct Square {
	int x1, y1, x2, y2;
	void init() {
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		xque[xtot++] = x1;
		yque[ytot++] = y1;
		xque[xtot++] = x2;
		yque[ytot++] = y2;
	}
} a[maxn];
vector<Edge> e[maxm];
double dis[maxm];
bool vis[maxm];
int main() {
	scanf("%d", &t);
	while(t--) {
		xtot = ytot = 0;
		scanf("%d", &n);
		for(int i = 0; i <= n; ++i)
			a[i].init();
		sort(xque, xque + xtot);
		xtot = unique(xque, xque + xtot) - xque;
		sort(yque, yque + ytot);
		ytot = unique(yque, yque + ytot) - yque;
		for(int i = 0; i < xtot; ++i)
			memset(c[i], 0, ytot * sizeof(int));
		for(int i = 0; i < n; ++i) {
			int x1 = lower_bound(xque, xque + xtot, a[i].x1) - xque;
			int y1 = lower_bound(yque, yque + ytot, a[i].y1) - yque;
			int x2 = lower_bound(xque, xque + xtot, a[i].x2) - xque;
			int y2 = lower_bound(yque, yque + ytot, a[i].y2) - yque;
			for(int x = x1; x < x2; ++x)
				for(int y = y1; y < y2; ++y)
					++c[x][y];
		}
		priority_queue<Edge> Q;
		int res = -1;
		for(int i = 0, idx = 0; i < xtot; ++i)
			for(int j = 0; j < ytot; ++j, ++idx) {
				vector<Edge>().swap(e[idx]);
				if(i) {
					DB tmp = (xque[i] - xque[i - 1]) / (max(c[i - 1][j], j ? c[i - 1][j - 1] : 0) + 1.0);
					e[idx].push_back((Edge){tmp, idx - ytot});
					e[idx - ytot].push_back((Edge){tmp, idx});
				}
				if(j) {
					DB tmp = (yque[j] - yque[j - 1]) / (max(c[i][j - 1], i ? c[i - 1][j - 1] : 0) + 1.0);
					e[idx].push_back((Edge){tmp, idx - 1});
					e[idx - 1].push_back((Edge){tmp, idx});
				}
				if(xque[i] == a[n].x1 && yque[j] == a[n].y1) {
					dis[idx] = 0;
					Q.push((Edge){-dis[idx], idx});
				} else {
					dis[idx] = INF;
				}
				if(xque[i] == a[n].x2 && yque[j] == a[n].y2)
					res = idx;
				vis[idx] = 0;
			}
		while(!Q.empty()) {
			int u = Q.top().second;
			Q.pop();
			if(vis[u])
				continue;
			vis[u] = 1;
			for(Edge &it : e[u]) {
				int v = it.second;
				DB tmp = dis[u] + it.first;
				if(dis[v] > tmp) {
					dis[v] = tmp;
					Q.push((Edge){-dis[v], v});
				}
			}
		}
		printf("%.5f\n", (double)dis[res]);
	}
	return 0;
}