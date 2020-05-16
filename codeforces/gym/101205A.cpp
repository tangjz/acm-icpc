#include <bits/stdc++.h>
using namespace std;
typedef double DB;
const int maxn = 51, maxm = 1251, maxe = 1562501;
const DB eps = 1e-9;
inline int sgn(DB x) {
	return (x > eps) - (x < -eps);
} 
inline DB sqr(DB x) {
	return x * x;
}
int n, m, etot, dsu[maxn], qtot, que[maxn], stim, vis[maxm];
int dsu_find(int x) {
	return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
}
bool dsu_merge(int u, int v) {
	u = dsu_find(u);
	v = dsu_find(v);
	if(u == v)
		return 0;
	if(dsu[u] < dsu[v])
		swap(u, v);
	dsu[v] -= dsu[u] == dsu[v];
	dsu[u] = v;
	return 1;
}
struct Asteroid {
	struct Point {
		int x, y, z;
		void read() {
			scanf("%d%d%d", &x, &y, &z);
		}
		Point operator - (Point const &t) const {
			return (Point){x - t.x, y - t.y, z - t.z};
		}
		int dot(Point const &t) const {
			return x * t.x + y * t.y + z * t.z;
		}
		int len2() const {
			return dot(*this);
		}
	} ori, vec;
	void read() {
		ori.read();
		vec.read();
	}
	int dist2(Asteroid const &t) const {
		return (t.ori - ori).len2();
	}
	DB dist2(Asteroid const &t, DB const &tim) const {
		Point o = t.ori - ori, v = t.vec - vec;
		return sqr(o.x + v.x * tim) + sqr(o.y + v.y * tim) + sqr(o.z + v.z * tim);
	}
} a[maxn];
struct Edge {
	int u, v;
	DB len2(DB const &tim) const {
		return a[u].dist2(a[v], tim);
	}
	bool operator < (Edge const &t) const {
		return a[u].dist2(a[v]) < a[t.u].dist2(a[t.v]);
	}
} e[maxm];
struct Event {
	DB tim;
	int u, v;
	bool operator < (Event const &t) const {
		return sgn(tim - t.tim) < 0;
	}
} eve[maxe];
int main() {
	for(int Case = 1; scanf("%d", &n) == 1; ++Case) {
		m = etot = qtot = 0;
		for(int i = 0; i < n; ++i) {
			a[i].read();
			for(int j = i + 1; j < n; ++j)
				e[m++] = (Edge){i, j};
		}
		sort(e, e + m);
		memset(dsu, -1, n * sizeof(int));
		for(int i = 0; i < m; ++i) {
			if(dsu_merge(e[i].u, e[i].v))
				que[qtot++] = i;
			Asteroid::Point oi = a[e[i].v].ori - a[e[i].u].ori;
			Asteroid::Point vi = a[e[i].v].vec - a[e[i].u].vec;
			for(int j = i + 1; j < m; ++j) {
				Asteroid::Point oj = a[e[j].v].ori - a[e[j].u].ori;
				Asteroid::Point vj = a[e[j].v].vec - a[e[j].u].vec;
				int coeff[3] = {oj.len2() - oi.len2(), (oj.dot(vj) - oi.dot(vi)) << 1, vj.len2() - vi.len2()};
				if(!coeff[2]) {
					DB tim = coeff[1] ? -coeff[0] / (DB)coeff[1] : -1;
					if(sgn(tim) > 0)
						eve[etot++] = (Event){tim, i, j};
				} else {
					long long delta = 1LL * coeff[1] * coeff[1] - 4LL * coeff[0] * coeff[2];
					if(delta > 0) {
						DB tim = -coeff[1] / (DB)(coeff[2] << 1);
						DB dt = sqrtl(delta) / (DB)(coeff[2] << 1);
						if(sgn(tim - dt) > 0)
							eve[etot++] = (Event){tim - dt, i, j};
						if(sgn(tim + dt) > 0)
							eve[etot++] = (Event){tim + dt, i, j};
					}
				}
			}
		}
		sort(que, que + qtot);
		sort(eve, eve + etot);
		int ans = 1;
		stim = 0;
		memset(vis, 0, m * sizeof(int));
		for(int i = 0; i < etot; ) {
			int cnt = 0;
			static int las[maxn];
			static pair<DB, int> tmp[maxm];
			memcpy(las, que, qtot * sizeof(int));
			++stim;
			while(qtot > 0) {
				int u = que[--qtot];
				vis[u] = stim;
				tmp[cnt++].second = u;
			}
			for(DB cur = eve[i].tim; i < etot && !sgn(cur - eve[i].tim); ++i) {
				if(vis[eve[i].u] != stim) {
					vis[eve[i].u] = stim;
					tmp[cnt++].second = eve[i].u;
				}
				if(vis[eve[i].v] != stim) {
					vis[eve[i].v] = stim;
					tmp[cnt++].second = eve[i].v;
				}
			}
			DB tim = eve[i - 1].tim + (i < etot ? eve[i].tim - eve[i - 1].tim : 1) * 0.5;
			for(int j = 0; j < cnt; ++j)
				tmp[j].first = e[tmp[j].second].len2(tim);
			sort(tmp, tmp + cnt);
			memset(dsu, -1, n * sizeof(int));
			for(int j = 0; j < cnt; ++j)
				if(dsu_merge(e[tmp[j].second].u, e[tmp[j].second].v))
					que[qtot++] = tmp[j].second;
			sort(que, que + qtot);
			bool chk = 1;
			for(int j = 0; chk && j < qtot; ++j)
				chk &= las[j] == que[j];
			ans += !chk;
		}
		printf("Case %d: %d\n", Case, ans);
	}
	return 0;
}
