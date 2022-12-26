/*
Author: tangjz
Date: 2022-12-05
Solution:

镜面右侧可反射，左侧是障碍物
=> 起点或终点在左侧的，只考虑障碍物
=> 起点和终点都在右侧的，只考虑在镜面右侧走，且不碰镜面

障碍物是严格三角形
=> 严格内部与起点到终点连线无交集时，最优解就是直走
=> 有交集时，分三种情况处理

没有任何三点共线
=> 起点和终点都不在镜面所在直线

任意时刻可见石头
=> m>1 时存在任意时刻可见起点、终点
=> m=1 时，直接障碍物最短路

1. 可直走时（无需考虑共线）：2m-1 次直走
2. m=1 时：障碍物最短路
3. 起点或终点在镜面左侧且不可直走且m>1时：无解
4. 起点和终点都在镜面右侧且不可直走且m>1时：（说明起点和终点被三角形阻碍）
	i. 场景
		a. 起点可见，起点走到终点：先走一段仅起点可见，再走都可见
		b. 起点和终点可见：一直走都可见
		c. 终点可见，起点走到终点：先走一段都可见，再走仅终点可见
	ii. 路径
		a. 起点、终点及其镜像与三角形顶点划分区域，镜像与镜面顶点划分区域（注意直线记录和起点/终点有关），任何时刻在镜面严格右侧
		b. 关键点是区域交点（包含起点、终点、镜面顶点、三角形顶点）
		c. 关键点能直走时（只考虑三角形），还需要判断可见性（通过仅起点及其镜像所划分区域来判，找交点，每段中间判断是否可见；终点同理）
*/

#include <bits/stdc++.h>
using namespace std;

typedef double DB;
typedef pair<DB, int> Edge;

const int maxn = 201;
const DB eps = 1e-9, INF = 1e10;

bool debug;

inline int sgn(DB const &x) {
	return (x > eps) - (x < -eps);
}

inline int readInt() {
	static int v;
	scanf("%d", &v);
	return v;
}

inline void writeDB(DB const &v, char const &endc = '\0') {
	printf("%.10f", (double)v);
	if(endc)
		putchar(endc);
}

template<class T>
inline void sortAndUnique(vector<T> &vec) {
	sort(vec.begin(), vec.end());
	vec.erase(unique(vec.begin(), vec.end()), vec.end());
}

struct Point {
	DB x, y;
	void read() {
		x = readInt();
		y = readInt();
	}
	bool operator == (Point const &t) const {
		return !sgn(x - t.x) && !sgn(y - t.y);
	}
	bool operator < (Point const &t) const {
		int sgn1 = sgn(x - t.x);
		return sgn1 < 0 || (!sgn1 && sgn(y - t.y) < 0);
	}
	Point operator + (Point const &t) const {
		return (Point){x + t.x, y + t.y};
	}
	Point operator - (Point const &t) const {
		return (Point){x - t.x, y - t.y};
	}
	Point operator * (DB const &t) const {
		return (Point){x * t, y * t};
	}
	DB dot(Point const &t) const {
		return x * t.x + y * t.y;
	}
	DB det(Point const &t) const {
		return x * t.y - y * t.x;
	}
	DB len2() const {
		return dot(*this);
	}
	DB len() const {
		return sqrtl(len2());
	}
	void write(char const &endc = '\0') const {
		writeDB(x, ' ');
		writeDB(y, endc);
	}
};

struct Line {
	Point o, v;
	void read() {
		o.read();
		v.read();
		v = v - o;
	}
	bool isParallel(Line const &t) const {
		return !sgn(v.det(t.v));
	}
	bool isColinear(Line const &t) const {
		return isParallel(t) && !sgn(v.det(t.o - o));
	}
	bool containsSegment(Point const &p) const {
		return !sgn(v.det(p - o)) && sgn((o - p).dot(o + v - p)) <= 0;
	}
	bool containsLeftHalfPlane(Point const &p, bool const &proper = false) const {
		return sgn(v.det(p - o)) >= proper;
	}
	Point project(Point const &p) const {
		return o + v * (v.dot(p - o) / v.len2());
	}
	Point reflect(Point const &p) const {
		return project(p) * 2 - p;
	}
	bool hasSegmentIntersection(Line const &t, bool const &proper = false) const {
		if(isParallel(t))
			return false;
		int sgn1 = sgn(v.det(t.o - o)), sgn2 = sgn(v.det(t.o + t.v - o));
		int sgn3 = sgn(t.v.det(o - t.o)), sgn4 = sgn(t.v.det(o + v - t.o));
		return sgn1 * sgn2 + proper <= 0 && sgn3 * sgn4 + proper <= 0;
	}
	pair<Point, bool> intersect(Line const &t) const {
		DB coe = v.det(t.v);
		if(!sgn(coe))
			return {{}, false};
		coe = t.v.det(o - t.o) / coe;
		return {o + v * coe, true};
	}
	void write(char const &endc = '\0') const {
		printf("line: o (");
		o.write(')');
		printf(", v (");
		v.write(')');
		if(endc)
			putchar(endc);
	}
};

struct ConvexPolygon {
	vector<Line> seg; // counter-clockwise
	void read(int n) {
		assert(n >= 3);
		seg.resize(n);
		for(int i = 0; i < n; ++i)
			seg[i].o.read();
		for(int i = 0, j = n - 1; i < n; j = i++)
			seg[j].v = seg[i].o - seg[j].o;
		if(sgn(seg[0].v.det(seg[1].v)) < 0)
			for(int i = 0; i < n; ++i)
				seg[i] = (Line){seg[i].o + seg[i].v, seg[i].v * -1};
	}
	int contains(Point const &p) const { // -1 outer, 0 border, 1 inner
		for(auto &l: seg) {
			if(l.containsSegment(p))
				return 0;
			if(!l.containsLeftHalfPlane(p))
				return -1;
		}
		return 1;
	}
	bool hasSegmentIntersection(Line const &t, bool const &proper = false) const {
		int sgn1 = contains(t.o), sgn2 = contains(t.o + t.v);
		if(sgn1 >= proper || sgn2 >= proper)
			return 1;
		bool sp = !sgn1 && !sgn2;
		for(auto &l: seg) {
			if(t.hasSegmentIntersection(l, proper))
				return 1;
			if(sp && t.isColinear(l))
				return 0;
		}
		return sp;
	}
	void write(char const &endc = '\0') const {
		printf("poly (%d):", (int)seg.size());
		for(auto &p: seg) {
			printf(" (");
			p.write(')');
		}
		if(endc)
			putchar(endc);
	}
};

DB getMinDist(vector<vector<pair<Edge, int> > > const &e, int s, int t, int msk) {
	int n = e.size();
	priority_queue<Edge> que;
	vector<DB> dis(n, INF);
	vector<bool> vis(n);
	auto upd = [&](int typ, int u, DB d) {
		if((typ & msk) == msk && d < dis[u]) {
			if(debug) {
				printf("upd %d typ %d dis ", u, typ);
				writeDB(d, '\n');
			}
			dis[u] = d;
			que.push({-dis[u], u});
		}
	};
	upd(msk, s, 0);
	while(!que.empty()) {
		int u = que.top().second;
		que.pop();
		if(vis[u])
			continue;
		if(debug) {
			printf("msk %d u %d dis ", msk, u);
			writeDB(dis[u], '\n');
		}
		vis[u] = 1;
		for(auto &it: e[u])
			upd(it.second, it.first.second, dis[u] + it.first.first);
	}
	return dis[t];
}

void solve() {
	int m;
	Point s, t;
	Line mr;
	ConvexPolygon poly;
	scanf("%d", &m);
	s.read();
	t.read();
	mr.read();
	poly.read(3);
	Line cur = (Line){s, t - s};
	if(!mr.hasSegmentIntersection(cur, true) && !poly.hasSegmentIntersection(cur, true)) {
		DB res = cur.v.len() * (m + m - 1);
		writeDB(res, '\n');
		return;
	}
	if(m == 1) {
		vector<Point> p = {s, t, mr.o, mr.o + mr.v};
		for(auto &l: poly.seg)
			p.push_back(l.o);
		int n = p.size();
		vector<vector<pair<Edge, int> > > e(n);
		for(int i = 0; i < n; ++i)
			for(int j = i + 1; j < n; ++j) {
				cur = (Line){p[i], p[j] - p[i]};
				if(!mr.hasSegmentIntersection(cur, true) && !poly.hasSegmentIntersection(cur, true)) {
					DB dis = cur.v.len();
					e[i].push_back({{dis, j}, 0});
					e[j].push_back({{dis, i}, 0});
				}
			}
		DB res = getMinDist(e, 0, 1, 0);
		if(sgn(res - INF) < 0) {
			writeDB(res, '\n');
		} else {
			puts("-1");
		}
		return;
	}
	if(mr.containsLeftHalfPlane(s) || mr.containsLeftHalfPlane(t)) {
		puts("-1");
		return;
	}
	vector<Point> sp = {s, t};
	vector<pair<Line, int> > borders;
	for(int i = 0; i < 2; ++i) {
		Point &u = sp[i], uR = mr.reflect(u);
		for(auto &l: poly.seg) {
			borders.push_back({(Line){u, l.o - u}, i});
			borders.push_back({(Line){uR, l.o - uR}, i});
		}
		borders.push_back({(Line){uR, mr.o - uR}, i});
		borders.push_back({(Line){uR, mr.o + mr.v - uR}, i});
	}
	int bLen = borders.size();
	vector<Point> p, seg[2];
	for(int i = 0; i < bLen; ++i)
		for(int j = i + 1; j < bLen; ++j) {
			Line &l1 = borders[i].first, &l2 = borders[j].first;
			pair<Point, bool> ins = l1.intersect(l2);
			if(ins.second && !mr.containsLeftHalfPlane(ins.first))
				p.push_back(ins.first);
		}
	sortAndUnique(p);
	int n = p.size();
	int idS = lower_bound(p.begin(), p.end(), s) - p.begin();
	int idT = lower_bound(p.begin(), p.end(), t) - p.begin();
	assert(idS < n && p[idS] == s);
	assert(idT < n && p[idT] == t);
	if(debug) {
		printf("n %d idS %d idT %d\n", n, idS, idT);
		for(int i = 0; i < n; ++i) {
			printf("p[%d]: ", i);
			p[i].write('\n');
		}
	}
	vector<vector<pair<Edge, int> > > e(n);
	for(int i = 0; i < n; ++i)
		for(int j = i + 1; j < n; ++j) {
			cur = (Line){p[i], p[j] - p[i]};
			if(poly.hasSegmentIntersection(cur, true))
				continue;
			DB dis = cur.v.len();
			if(debug) {
				printf("e[%d][%d]: ", i, j);
				writeDB(dis, '\n');
			}
			seg[0] = {p[i], p[j]};
			seg[1] = {p[i], p[j]};
			for(auto &it: borders) {
				int o = it.second;
				pair<Point, bool> ins = cur.intersect(it.first);
				if(ins.second && cur.containsSegment(ins.first))
					seg[o].push_back(ins.first);
			}
			sortAndUnique(seg[0]);
			sortAndUnique(seg[1]);
			int msk = 0;
			for(int k = 0; k < 2; ++k) {
				int sz = seg[k].size();
				Point &u = sp[k], uR = mr.reflect(u);
				bool ban = 0;
				for(int o = 1; !ban && o < sz; ++o) {
					Point mid = (seg[k][o - 1] + seg[k][o]) * 0.5;
					cur = (Line){u, mid - u};
					if(!mr.hasSegmentIntersection(cur, true) && !poly.hasSegmentIntersection(cur, true))
						continue;
					cur = (Line){uR, mid - uR};
					pair<Point, bool> ins = mr.intersect(cur);
					if(!ins.second || !mr.containsSegment(ins.first)) {
						ban = 1;
						break;
					}
					cur = (Line){u, ins.first - u};
					if(poly.hasSegmentIntersection(cur, true)) {
						ban = 1;
						break;
					}
					cur = (Line){mid, ins.first - mid};
					ban |= poly.hasSegmentIntersection(cur, true);
				}
				msk |= !ban << k;
			}
			if(debug)
				printf("msk: %d\n", msk);
			e[i].push_back({{dis, j}, msk});
			e[j].push_back({{dis, i}, msk});
		}
	DB dis[3];
	for(int i = 0; i < 3; ++i) {
		dis[i] = getMinDist(e, idS, idT, i + 1);
		if(sgn(dis[i] - INF) >= 0) {
			puts("-1");
			return;
		}
	}
	DB res = dis[0] + dis[1] + (m + m - 3) * dis[2];
	writeDB(res, '\n');
}

int main() {
	int T = 1;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d: ", Case);
		solve();
	}
	return 0;
}
