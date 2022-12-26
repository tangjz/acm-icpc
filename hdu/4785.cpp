#include <bits/stdc++.h>
using namespace std;
typedef double DB;
const int maxn = 41, maxm = 901;
const DB eps = 1e-9;
int t, n, m, etot, sz[maxn];
DB ans;
inline int readInt() {
	int x;
	scanf("%d", &x);
	return x;
}
inline int sgn(DB x) {
	return (x > eps) - (x < -eps);
}
struct Point {
	DB x, y;
	void read() {
		x = readInt();
		y = readInt();
	}
	bool operator < (Point const &t) const {
		int tp = sgn(x - t.x);
		return tp < 0 || (tp == 0 && sgn(y - t.y) < 0);
	}
	Point operator - (Point const &t) const {
		return (Point){x - t.x, y - t.y};
	}
	Point operator + (Point const &t) const {
		return (Point){x + t.x, y + t.y};
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
	int site() const {
		return x < 0 || (!x && y < 0);
	}
	bool cmp(Point const &t) const {
		int sL = site(), sR = t.site();
		if(sL != sR)
			return sL < sR;
		return sgn(det(t)) > 0;
	}
} p[maxn][maxn], pL, pH, qL, qH;
struct Line {
	Point ori, vec;
	bool operator < (Line const &t) const { // only one half plane
		int tp = sgn(vec.det(t.vec));
		return tp > 0 || (tp == 0 && sgn(vec.det(t.ori - ori)) > 0);
	}
	Point intersection(Line const &t) const {
		return ori + vec * (t.vec.det(ori - t.ori) / vec.det(t.vec));
	}
} seg[maxm];
struct Event {
	int typ;
	Point p;
	bool operator < (Event const &t) const {
		return sgn(p.x - t.p.x) < 0;
	}
} eve[maxm << 1 | 1];
DB solve() {
	m = etot = 0;
	for(int i = 0; i < n; ++i)
		for(int j = sz[i] - 1, k = 0; k < sz[i]; j = k++) {
			Point vec = p[i][k] - p[i][j];
			if(sgn(vec.x) > 0)
				seg[m++] = (Line){p[i][j], vec};
		}
	sort(seg, seg + m);
	DB ret = 0;
	for(int o = 0; o < m; ) {
		etot = 0;
		Line cur = seg[o];
		for( ; o < m && !sgn(cur.vec.det(seg[o].vec)) && !sgn(cur.vec.det(seg[o].ori - cur.ori)); ++o) {
			eve[etot++] = (Event){0, seg[o].ori};
			eve[etot++] = (Event){1, seg[o].ori + seg[o].vec};
		}
		for(int i = 0; i < n; ++i) {
			int pcnt = 0;
			static Point ins[3];
			for(int j = sz[i] - 1, k = 0, sL = sgn(cur.vec.det(p[i][j] - cur.ori)), sR; pcnt <= 2 && k < sz[i]; j = k++, sL = sR) {
				sR = sgn(cur.vec.det(p[i][k] - cur.ori));
				if(sL * sR < 0) {
					Point tmp = cur.intersection((Line){p[i][j], p[i][k] - p[i][j]});
					if(sgn((p[i][j] - tmp).dot(p[i][k] - tmp)) <= 0)
						ins[pcnt++] = tmp;
				} else if(sL != 0 && sR == 0) {
					ins[pcnt++] = p[i][k];
				}
			}
			if(pcnt == 2) {
				if(sgn(ins[0].x - ins[1].x) > 0)
					swap(ins[0], ins[1]);
				eve[etot++] = (Event){2, ins[0]};
				eve[etot++] = (Event){3, ins[1]};
			}
		}
		sort(eve, eve + etot);
		for(int i = 0, lcnt = 0, pcnt = 0; i < etot; ++i) {
			if(lcnt && !pcnt)
				ret += (eve[i].p.y + eve[i - 1].p.y) * (eve[i].p.x - eve[i - 1].p.x) / 2;
			switch(eve[i].typ) {
				case 0: ++lcnt; break;
				case 1: --lcnt; break;
				case 2: ++pcnt; break;
				case 3: --pcnt;
			}
		}
	}
	return ret;
}
void merge(int &szL, Point pL[], int szR, Point pR[]) {
	int staL = 0, staR = 0, sta = 0;
	static Point q[maxn];
	for(int i = 1; i < szL; ++i)
		if(pL[i] < pL[staL])
			staL = i;
	for(int i = 1; i < szR; ++i)
		if(pR[i] < pR[staR])
			staR = i;
	q[sta] = pL[staL] + pR[staR];
	int posL = 0, posR = 0;
	int curL = staL, nxtL = curL + 1 < szL ? curL + 1 : 0;
	int curR = staR, nxtR = curR + 1 < szR ? curR + 1 : 0;
	while(posL < szL && posR < szR) {
		Point lft = pL[nxtL] - pL[curL], rht = pR[nxtR] - pR[curR];
		Point sel = lft.cmp(rht) ? lft : rht;
		++sta;
		q[sta] = q[sta - 1];
		if(!sel.cmp(lft)) {
			q[sta] = q[sta] + lft;
			++posL;
			curL = nxtL;
			nxtL = curL + 1 < szL ? curL + 1 : 0;
		}
		if(!sel.cmp(rht)) {
			q[sta] = q[sta] + rht;
			++posR;
			curR = nxtR;
			nxtR = curR + 1 < szR ? curR + 1 : 0;
		}
	}
	while(posL < szL) {
		++sta;
		q[sta] = q[sta - 1] + pL[nxtL] - pL[curL];
		++posL;
		curL = nxtL;
		nxtL = curL + 1 < szL ? curL + 1 : 0;
	}
	while(posR < szR) {
		++sta;
		q[sta] = q[sta - 1] + pR[nxtR] - pR[curR];
		++posR;
		curR = nxtR;
		nxtR = curR + 1 < szR ? curR + 1 : 0;
	}
	assert(!q[0].cmp(q[sta]) && !q[sta].cmp(q[0]));
	szL = sta;
	for(int i = 0; i < szL; ++i)
		pL[i] = q[i];
}
int main() {
	t = readInt();
	for(int Case = 1; Case <= t; ++Case) {
		n = readInt();
		for(int i = 0; i <= n; ++i) {
			sz[i] = readInt();
			for(int j = 0; j < sz[i]; ++j)
				p[i][j].read();
		}
		pL.read();
		pH.read();
		qL = qH = (Point){0, 0};
		for(int j = sz[n] - 1; j >= 0; --j) {
			p[n][j] = p[n][0] - p[n][j];
			qL.x = min(qL.x, -p[n][j].x);
			qL.y = min(qL.y, -p[n][j].y);
			qH.x = max(qH.x, -p[n][j].x);
			qH.y = max(qH.y, -p[n][j].y);
		}
		qL = pL - qL;
		qH = pH - qH;
		for(int i = 0; i < n; ++i) {
			merge(sz[i], p[i], sz[n], p[n]);
			for(int j = 0; j < sz[i]; ++j) {
				pL.x = min(pL.x, p[i][j].x);
				pL.y = min(pL.y, p[i][j].y);
				pH.x = max(pH.x, p[i][j].x);
				pH.y = max(pH.y, p[i][j].y);
			}
		}
		if(sgn(pL.x - qL.x) < 0) {
			p[n][0] = (Point){pL.x, pL.y};
			p[n][1] = (Point){qL.x, pL.y};
			p[n][2] = (Point){qL.x, pH.y};
			p[n][3] = (Point){pL.x, pH.y};
			sz[n++] = 4;
		}
		if(sgn(qH.x - pH.x) < 0) {
			p[n][0] = (Point){qH.x, pL.y};
			p[n][1] = (Point){pH.x, pL.y};
			p[n][2] = (Point){pH.x, pH.y};
			p[n][3] = (Point){qH.x, pH.y};
			sz[n++] = 4;
		}
		if(sgn(pL.y - qL.y) < 0) {
			p[n][0] = (Point){pL.x, pL.y};
			p[n][1] = (Point){pH.x, pL.y};
			p[n][2] = (Point){pH.x, qL.y};
			p[n][3] = (Point){pL.x, qL.y};
			sz[n++] = 4;
		}
		if(sgn(qH.y - pH.y) < 0) {
			p[n][0] = (Point){pL.x, qH.y};
			p[n][1] = (Point){pH.x, qH.y};
			p[n][2] = (Point){pH.x, pH.y};
			p[n][3] = (Point){pL.x, pH.y};
			sz[n++] = 4;
		}
		ans = (pH.x - pL.x) * (pH.y - pL.y) + solve();
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < sz[i]; ++j)
				p[i][j].x = -p[i][j].x;
		ans -= solve();
		printf("Case #%d: %.3f\n", Case, (double)ans);
	}
	return 0;
}
