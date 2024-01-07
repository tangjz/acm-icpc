#include <bits/stdc++.h>
using namespace std;
typedef double DB;
const int maxt = 100;
const DB eps = 1e-9, INF = 1e100, pi = acos(-1.0);
inline int sgn(DB x) {
	return (x > eps) - (x < -eps);
}
struct Point {
	DB x, y;
	Point operator - (Point const &t) const {
		return (Point){x - t.x, y - t.y};
	}
	DB dot(Point const &t) const {
		return x * t.x + y * t.y;
	}
	DB len2() const {
		return dot(*this);
	}
	DB len() const {
		return sqrtl(len2());
	}
};
inline DB solve(Point p, Point q, int len1) {
	int s1 = sgn(p.y), s2 = sgn(q.y);
	if(s1 < 0 || s2 < 0 || (!s1 && !s2) || sgn((q - p).len() - len1) != 0)
		return INF;
	return len1 / (sqrtl(5 * max(p.y, (DB)0)) + sqrtl(5 * max(q.y, (DB)0)));
}
inline DB solve(Point p, Point q, int len1, int len2) {
	int s1 = sgn(p.y), s2 = sgn(q.y);
	if(s1 < 0 || s2 < 0)
		return INF;
	Point vec = q - p;
	DB dis = vec.len();
	int s3 = sgn(len1 + len2 + dis - max(dis, (DB)max(len1, len2)) * 2);
	if(s3 < 0 || (!s1 && !s2 && !s3 && sgn(dis) > 0))
		return INF;
	if(!sgn(dis))
		return 2 * solve(p, (Point){p.x, p.y + len1}, len1);
	DB ang = atan2(vec.y, vec.x);
	DB dt = acos(max(min((len1 * len1 + vec.len2() - len2 * len2) / (2 * len1 * dis), (DB)1), (DB)-1));
	auto calc = [&](DB angle) {
		Point tp = (Point){p.x + len1 * cos(angle), p.y + len1 * sin(angle)};
		return min(solve(p, tp, len1) + solve(tp, q, len2), INF);
	};
	return min(calc(ang - dt), calc(ang + dt));
}
inline DB solve(Point p, Point q, int len1, int len2, int len3) {
	int s1 = sgn(p.y), s2 = sgn(q.y);
	if(s1 < 0 || s2 < 0)
		return INF;
	Point vec = q - p;
	DB dis = vec.len();
	int s3 = sgn(len1 + len2 + len3 + dis - max(dis, (DB)max(len1, max(len2, len3))) * 2);
	if(s3 < 0 || (!s1 && !s2 && !s3 && sgn(dis) > 0))
		return INF;
	auto calc = [&](DB angle) {
		Point tp = (Point){p.x + len1 * cos(angle), p.y + len1 * sin(angle)};
		return min(solve(p, tp, len1) + solve(tp, q, len2, len3), INF);
	};
	auto ternarySearch = [&calc](DB L, DB R, bool chkL = 0) {
		const DB rate = (sqrtl(5) + 1) / 2;
		DB dt = (R - L) / rate;
		DB ML = R - dt, fL = calc(ML);
		DB MR = L + dt, fR = calc(MR);
		for(int t = 0; t < maxt; ++t)
			if((!chkL && fR >= INF / 2) || (!(chkL && fL >= INF / 2) && fL < fR)) {
				R = MR;
				MR = ML;
				fR = fL;
				dt = (R - L) / rate;
				ML = R - dt;
				fL = calc(ML);
			} else {
				L = ML;
				ML = MR;
				fL = fR;
				dt = (R - L) / rate;
				MR = L + dt;
				fR = calc(MR);
			}
		return !chkL ? fL : fR;
	};
	if(!sgn(dis))
		return ternarySearch(0, pi / 2);
	DB ang = atan2(vec.y, vec.x);
	DB dt = acos(max(min((len1 * len1 + vec.len2() - (len2 + len3) * (len2 + len3)) / (2 * len1 * dis), (DB)1), (DB)-1));
	return min(ternarySearch(ang - dt, ang), ternarySearch(ang, ang + dt, 1));
}
int main() {
	int t, x, y, l[3];
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%d%d%d", &x, &y, l + 0, l + 1, l + 2);
		if(y > 0) {
			puts("Impossible!");
			continue;
		}
		Point p = (Point){0, 0}, q = (Point){(DB)x, (DB)-y};
		DB ans = INF;
		for(int i = 0; i < 3; ++i) {
			ans = min(ans, solve(p, q, l[i]));
			for(int j = 0; j < 3; ++j)
				if(i != j) {
					ans = min(ans, solve(p, q, l[i], l[j]));
					ans = min(ans, solve(p, q, l[i], l[j], l[3 - i - j]));
				}
		}
		if(ans < INF / 2) {
			printf("%.8f\n", (double)ans);
		} else {
			puts("Impossible!");
		}
	}
	return 0;
}
