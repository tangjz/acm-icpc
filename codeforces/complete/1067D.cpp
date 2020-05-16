#include <bits/stdc++.h>
using namespace std;
typedef double DB;
typedef long long LL;
const int maxn = (int)1e5 + 1, maxd = 35;
const DB INF = 1e19;
inline int sgn(DB x) {
	return (x > 0) - (x < 0);
}
inline void read(DB &x) {
	DB fz = 0, fm = 1;
	static char buf[13];
	scanf("%s", buf);
	for(int i = 0, o = 0; buf[i]; ++i)
		if(buf[i] == '.') {
			o = 1;
		} else {
			fz = fz * 10 + (buf[i] - '0');
			if(o)
				fm *= 10;
		}
	x = fz / fm;
}
struct Point {
	DB x, y;
	bool operator < (Point const &t) const {
		int tmp = sgn(x - t.x);
		return tmp < 0 || (!tmp && sgn(y - t.y) > 0);
	}
	Point operator - (Point const &t) const {
		return (Point){x - t.x, y - t.y};
	}
	DB det(Point const &t) const {
		return x * t.y - y * t.x;
	}
} p[maxn];
int n, m, a[maxn], b[maxn], ord[maxn];
LL tim;
DB pp[maxn], adt;
struct Matrix {
	DB num[3][3];
	Matrix operator * (Matrix const &t) const {
		Matrix ret = {};
		for(int i = 0; i < 3; ++i)
			for(int j = 0; j < 3; ++j)
				for(int k = 0; k < 3; ++k)
					ret.num[i][k] += num[i][j] * t.num[j][k];
		return ret;
	}
} pw[maxd];
int main() {
	scanf("%d%lld", &n, &tim);
	for(int i = 0; i < n; ++i) {
		scanf("%d%d", a + i, b + i);
		read(pp[i]);
		p[i] = (Point){pp[i], pp[i] * a[i]};
		ord[i] = i;
		adt = max(adt, pp[i] * b[i]);
	}
	sort(ord, ord + n, [&](int const &u, int const &v) {
		return p[u] < p[v];
	});
	for(int i = 0; i < n; ++i) {
		int o = ord[i];
		for( ; m > 1 && sgn((p[ord[m - 1]] - p[ord[m - 2]]).det(p[o] - p[ord[m - 2]])) >= 0; --m);
		ord[m++] = o;
	}
	DB curV = 0;
	LL curT = 0;
	for(int i = 0; i < m && curT < tim; ++i) {
		DB limV = INF;
		if(i + 1 < m)
			limV = min(limV, (p[ord[i]].y - p[ord[i + 1]].y) / (p[ord[i + 1]].x - p[ord[i]].x));
		auto getVal = [&adt](DB curV, LL curT) {
			return curT * adt - curV;
		};
		if(sgn(getVal(curV, curT) - limV) >= 0)
			continue;
		LL limT = tim - curT;
		int o = ord[i], mx;
		pw[0] = (Matrix){1 - pp[o], 0, 0, pp[o] * adt, 1, 0, pp[o] * a[o], 1, 1};
		for(mx = 1; 1LL << mx <= limT; ++mx)
			pw[mx] = pw[mx - 1] * pw[mx - 1];
		while(mx--) {
			Matrix &tmp = pw[mx];
			DB nxtV = curV * tmp.num[0][0] + curT * tmp.num[1][0] + tmp.num[2][0];
			LL nxtT = curT + (1LL << mx);
			if(nxtT > tim || sgn(getVal(nxtV, nxtT) - limV) >= 0)
				continue;
			curV = nxtV;
			curT = nxtT;
		}
		if(curT < tim && sgn(getVal(curV, curT) - limV) < 0) {
			Matrix &tmp = pw[0];
			curV = curV * tmp.num[0][0] + curT * tmp.num[1][0] + tmp.num[2][0];
			++curT;
		}
	}
	printf("%.20f\n", (double)curV);
	return 0;
}