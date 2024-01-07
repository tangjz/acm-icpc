#include <bits/stdc++.h>
using namespace std;
typedef long double DB;
const DB sqrt2 = sqrtl(2.0), sqrt3 = sqrtl(3.0), base = atan(1 / sqrt2);
int t;
DB p[3][3], Ratio, theta, sin_theta, cos_theta;
inline void readDB(DB &x) {
	double _x;
	scanf("%lf", &_x);
	x = _x;
}
inline void writeDB(DB x, char endc) {
	printf("%.20f%c", (double)x, endc);
}
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		readDB(Ratio);
		theta = asin(Ratio / sqrt3) - base;
		sin_theta = sin(theta);
		cos_theta = cos(theta);
		p[0][0] = -0.5 * sin_theta;
		p[0][1] = 0.5 * cos_theta;
		p[0][2] = 0;
		p[1][0] = 0.25 * sqrt2 * cos_theta;
		p[1][1] = 0.25 * sqrt2 * sin_theta;
		p[1][2] = 0.25 * sqrt2;
		p[2][0] = -0.25 * sqrt2 * cos_theta;
		p[2][1] = -0.25 * sqrt2 * sin_theta;
		p[2][2] = 0.25 * sqrt2;
		printf("Case #%d:\n", Case);
		for(int i = 0; i < 3; ++i)
			for(int j = 0; j < 3; ++j)
				writeDB(p[i][j], " \n"[j == 2]);
	}
	return 0;
}
