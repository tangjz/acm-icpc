#include <cstdio>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

#define N 200000
#define M 5500

const int inf = 0x3fffffff;

int n, m, u, v, S;
vector<int> lnk[N + 9];
int d[N + 9];
int l, r, q[N + 9];
list<int> s;
int ans[N + 9];

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i)
			lnk[i].clear();
		while (m--) {
			scanf("%d%d", &u, &v);
			lnk[u].push_back(v);
			lnk[v].push_back(u);
		}
		scanf("%d", &S);
		s.clear();
		for (int i = 1; i <= n; ++i) {
			if (i == S) {
				d[i] = 0;
				continue;
			}
			d[i] = inf;
			s.push_back(i);
		}
		s.sort();
		for (int i = 1; i <= n; ++i)
			sort(lnk[i].begin(), lnk[i].end());
		q[(r = 0)++] = S;
		for (int l = 0; l < r; ++l) {
			u = q[l];
			int j = 0;
			for (auto it = s.begin(), jt = it; it != s.end(); it = jt) {
				jt = next(it);
				while (j < (int)lnk[u].size() && lnk[u][j] < *it) ++j;
				if (j < (int)lnk[u].size() && lnk[u][j] == *it) continue;
				//printf("%d %d\n", u, *it);
				d[*it] = d[u] + 1;
				q[r++] = *it;
				s.erase(it);
			}
		}
		int tot = 0;
		for (int i = 1; i <= n; ++i)
			if (i != S) ans[tot++] = d[i] < inf? d[i] : -1;
		for (int i = 0; i < tot; ++i) printf("%d%c", ans[i], " \n"[i == tot - 1]);
	}
	return 0;
}
