#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)4e5 + 1;
int t, n, tot, lnk0[maxn], lnk1[maxn], ord[maxn], fa[maxn];
struct Edge {
	int nxt, v, w;
} e[maxn << 1 | 1];
bool ban[maxn];
vector<pair<int, int> > ee[maxn];
void edge_build() {
	tot = 0;
	ord[++tot] = 1;
	for(int i = 1; i <= tot; ++i) {
		int u = ord[i];
		for(auto &it : ee[u]) {
			int v = it.first;
			if(v == fa[u])
				continue;
			fa[v] = u;
			ord[++tot] = v;
		}
	}
	tot = 0;
	memset(lnk0 + 1, 0, n * sizeof(int));
	memset(lnk1 + 1, 0, n * sizeof(int));
	for(int i = 1, nn = n; i <= n; ++i) {
		int u = ord[i], p = u, j = 0, sz = ee[u].size() - (fa[u] != 0);
		for(auto &it : ee[u]) {
			int v = it.first, w = it.second;
			if(v == fa[u])
				continue;
			++j;
			if(j > 1 && j < sz) {
				++nn;
				lnk0[nn] = lnk1[nn] = 0;
				ban[++tot] = 0;
				e[tot << 1] = (Edge){lnk0[p], nn, 0};
				lnk0[p] = tot << 1;
				e[tot << 1 | 1] = (Edge){lnk0[nn], p, 0};
				lnk0[nn] = tot << 1 | 1;
				p = nn;
			}
			ban[++tot] = 0;
			e[tot << 1] = (Edge){lnk1[p], v, w};
			lnk1[p] = tot << 1;
			e[tot << 1 | 1] = (Edge){lnk1[v], p, w};
			lnk1[v] = tot << 1 | 1;
		}
		vector<pair<int, int> >().swap(ee[u]);
	}
}
void bfs(int rt, int rfa) {
	tot = 0;
	fa[rt] = rfa;
	ord[++tot] = rt;
	for(int i = 1; i <= tot; ++i) {
		int u = ord[i];
		for(int it = lnk0[u]; it; it = e[it].nxt) {
			int v = e[it].v;
			if(v == fa[u] || ban[it >> 1])
				continue;
			fa[v] = u;
			ord[++tot] = v;
		}
		for(int it = lnk1[u]; it; it = e[it].nxt) {
			int v = e[it].v;
			if(v == fa[u] || ban[it >> 1])
				continue;
			fa[v] = u;
			ord[++tot] = v;
		}
	}
}
struct Point {
	int x;
	LL y;
	Point operator + (Point const &t) const {
		return (Point){x + t.x, y + t.y};
	}
	Point operator - (Point const &t) const {
		return (Point){x - t.x, y - t.y};
	}
	LL det(Point const &t) const {
		return x * t.y - y * t.x;
	}
};
vector<Point> convex_merge(vector<Point> &lft, vector<Point> &rht) {
	int m = 0;
	vector<Point> ret;
	for(vector<Point>::iterator it = lft.begin(), jt = rht.begin(); it != lft.end() || jt != rht.end(); ) {
		Point vec = (Point){maxn, -1};
		if(it != lft.end())
			vec.x = min(vec.x, it -> x);
		if(jt != rht.end())
			vec.x = min(vec.x, jt -> x);
		if(it != lft.end() && it -> x == vec.x)
			vec.y = max(vec.y, (it++) -> y);
		if(jt != rht.end() && jt -> x == vec.x)
			vec.y = max(vec.y, (jt++) -> y);
		while(m > 1 && (ret.back() - ret[m - 2]).det(vec - ret[m - 2]) >= 0) {
			ret.pop_back();
			--m;
		}
		ret.push_back(vec);
		++m;
	}
	return ret;
}
vector<Point> minkowski_sum(vector<Point> &lft, vector<Point> &rht) {
	vector<Point> ret;
	vector<Point>::iterator itL = lft.begin(), jtL = itL++;
	vector<Point>::iterator itR = rht.begin(), jtR = itR++;
	ret.push_back(*jtL + *jtR);
	while(itL != lft.end() || itR != rht.end())
		if(itR == rht.end() || (itL != lft.end() && (*itL - *jtL).det(*itR - *jtR) <= 0)) {
			if(itR != rht.end() && !(*itL - *jtL).det(*itR - *jtR))
				jtR = itR++;
			ret.push_back(*itL + *jtR);
			jtL = itL++;
		} else {
			ret.push_back(*jtL + *itR);
			jtR = itR++;
		}
	return ret;
}
vector<Point> bfs(int rt, int rfa, Point rdis) {
	static Point dis[maxn];
	tot = 0;
	auto append = [&](int u) {
		ord[++tot] = u;
		for(int i = tot; i <= tot; ++i) {
			u = ord[i];
			for(int it = lnk0[u]; it; it = e[it].nxt) {
				int v = e[it].v;
				if(v == fa[u] || ban[it >> 1])
					continue;
				fa[v] = u;
				dis[v] = (Point){dis[u].x, dis[u].y + e[it].w};
				ord[++tot] = v;
			}
		}
	};
	fa[rt] = rfa;
	dis[rt] = rdis;
	append(rt);
	for(int i = 1; i <= tot; ++i) {
		int u = ord[i];
		for(int it = lnk1[u]; it; it = e[it].nxt) {
			int v = e[it].v;
			if(v == fa[u] || ban[it >> 1])
				continue;
			fa[v] = u;
			dis[v] = (Point){dis[u].x + 1, dis[u].y + e[it].w};
			append(v);
		}
	}
	int m = 0;
	vector<Point> ret;
	for(int i = 1; i <= tot; ) {
		Point vec = dis[ord[i++]];
		for( ; i <= tot && dis[ord[i]].x == vec.x; ++i)
			vec.y = max(vec.y, dis[ord[i]].y);
		while(m > 1 && (ret.back() - ret[m - 2]).det(vec - ret[m - 2]) >= 0) {
			ret.pop_back();
			--m;
		}
		ret.push_back(vec);
		++m;
	}
	return ret;
}
vector<Point> solve(int rt) { static int depth = 0; ++depth;
	bfs(rt, -1);
	if(tot == 1) {
		vector<Point> ret;
		ret.push_back((Point){0, 0LL});
		return ret;
	}
	int val = tot;
	static int sz[maxn];
	for(int i = tot; i > 1; --i) {
		int u = ord[i];
		sz[u] = 1;
		for(int it = lnk0[u]; it; it = e[it].nxt) {
			int v = e[it].v;
			if(v == fa[u] || ban[it >> 1])
				continue;
			sz[u] += sz[v];
		}
		for(int it = lnk1[u]; it; it = e[it].nxt) {
			int v = e[it].v;
			if(v == fa[u] || ban[it >> 1])
				continue;
			sz[u] += sz[v];
		}
		int tmp = max(sz[u], tot - sz[u]);
		if(tmp < val) {
			val = tmp;
			rt = u;
		}
	}
	int lft = fa[rt], rht = rt;
	Point adt = (Point){-1, 0};
	for(int it = lnk0[lft]; adt.x == -1 && it; it = e[it].nxt)
		if(e[it].v == rht) {
			adt = (Point){0, e[it].w};
			ban[it >> 1] = 1;
		}
	for(int it = lnk1[lft]; adt.x == -1 && it; it = e[it].nxt)
		if(e[it].v == rht) {
			adt = (Point){1, e[it].w};
			ban[it >> 1] = 1;
		}
	vector<Point> pL, pM, pR;
	pL = bfs(lft, -1, (Point){0, 0LL});
	pR = bfs(rht, -1, adt);
	pM = minkowski_sum(pL, pR);
	pL = solve(lft);
	pR = solve(rht);
	pL = convex_merge(pL, pR); --depth;
	return convex_merge(pL, pM);
}
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		int m;
		scanf("%d%d", &n, &m);
		for(int i = 1; i < n; ++i) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			ee[u].push_back(make_pair(v, w));
			ee[v].push_back(make_pair(u, w));
		}
		edge_build();
		vector<Point> res = solve(1), que;
		que.reserve(m);
		for(int i = 0; i < m; ++i) {
			int x;
			scanf("%d", &x);
			que.push_back((Point){i, (LL)x});
		}
		sort(que.begin(), que.end(), [](Point const &u, Point const &v) {
			return u.y < v.y;
		});
		int L = 0, R = res.size() - 1;
		auto calc = [](Point const &p, LL const &k) {
			return p.x * k + p.y;
		};
		for(auto &it : que) {
			for( ; L < R && calc(res[L], it.y) < calc(res[L + 1], it.y); ++L);
			it.y = calc(res[L], it.y);
		}
		sort(que.begin(), que.end(), [](Point const &u, Point const &v) {
			return u.x < v.x;
		});
		printf("Case #%d:\n", Case);
		for(auto &it : que)
			printf("%lld\n", it.y);
	}
	return 0;
}
