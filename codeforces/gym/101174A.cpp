#include <bits/stdc++.h>
using namespace std;

typedef double DB;
const int maxn = 21, maxt = 101;
const DB eps = 1e-9, pi = acos((DB)-1);

inline int getInt() {
	static int v;
	scanf("%d", &v);
	return v;
}

int main() {
	int n = getInt();
	DB mx = 0, sum = 0;
	static DB a[maxn];
	for(int i = 0, v; i < n; ++i) {
		mx = max(mx, a[i] = getInt());
		sum += a[i];
	}
	DB px = getInt(), py = getInt();
	DB d2 = px * px + py * py;
	a[n] = sqrtl(d2);
	if(sum * sum <= d2) {
		sum = 0;
		for(int i = 0; i < n; ++i) {
			sum += a[i];
			DB qx = px * sum / a[n], qy = py * sum / a[n];
			printf("%.3f %.3f\n", (double)qx, (double)qy);
		}
		return 0;
	}
	DB dt = mx + mx - sum;
	if(mx * mx >= d2 && dt >= 0 && d2 <= dt * dt) {
		sum = 0;
		for(int i = 0; i < n; ++i) {
			if(a[i] == mx) {
				sum += a[i];
				mx = -1;
			} else {
				sum -= a[i];
			}
			DB qx, qy;
			if(d2 > 0) {
				qx = px * sum / a[n];
				qy = py * sum / a[n];
			} else {
				qx = sum;
				qy = 0;
			}
			printf("%.3f %.3f\n", (double)qx, (double)qy);
		}
		return 0;
	}
	sum += a[n];
	mx = max(mx, a[n]);
	vector<DB> vals(a, a + n + 1);
	sort(vals.begin(), vals.end());
	auto getAngles = [](vector<DB> &vals, DB rad) {
		DB ret = 0;
		for(DB &len: vals)
			ret += asin(len / (DB)2 / rad);
		return ret;
	};
	DB L = mx / 2, R;
	bool hasLarge = getAngles(vals, L) < pi;
	if(hasLarge) {
		vals.pop_back();
		R = (DB)1e9;
		for(int j = 0; j < maxt; ++j) {
			DB M = L + (R - L) / 2;
			if(getAngles(vals, M) < asin(mx / (DB)2 / M))
				L = M;
			else
				R = M;
		}
	} else {
		R = sum / 2;
		for(int j = 0; j < maxt; ++j) {
			DB M = L + (R - L) / 2;
			if(getAngles(vals, M) < pi)
				R = M;
			else
				L = M;
		}
	}
	dt = sqrtl(L * L - d2 / 4);
	DB cx, cy;
	if(d2 > 0) {
		cx = px / 2 - py * dt / a[n];
		cy = py / 2 + px * dt / a[n];
	} else {
		cx = 0;
		cy = L;
	}
	if(fabs(mx - a[n]) < eps) {
		mx = -1;
		if(hasLarge) {
			cx = px / 2 + py * dt / a[n];
			cy = py / 2 - px * dt / a[n];
		}
	}
	// printf("rad: %.3f, cen: %.3f %.3f, hasLarge: %d\n", (double)L, (double)cx, (double)cy, hasLarge);
	DB ang = atan2(-cy, -cx);
	// printf("ang: %.3f (%.3f %.3f)\n", (double)ang, (double)(cx + L * cos(ang)), (double)(cy + L * sin(ang)));
	for(int i = 0; i < n; ++i) {
		DB adt = 2 * asin(a[i] / 2 / L);
		if(fabs(mx - a[i]) < eps) {
			mx = -1;
			if(hasLarge)
				adt = pi + pi - adt;
		}
		ang -= adt;
		DB qx = cx + L * cos(ang), qy = cy + L * sin(ang);
		printf("%.3f %.3f\n", (double)qx, (double)qy);
	}
	return 0;
}