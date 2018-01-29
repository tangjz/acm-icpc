#include <bits/stdc++.h>
using namespace std;
typedef long double DB;
const DB sqrt2 = sqrtl(2);
int v[7];
DB r[7], dx[7], dy;
int main() {
	v[0] = v[6] = 10;
	r[0] = r[6] = 1.0;
	dx[0] = dx[6] = 25 * (sqrt2 - 1);
	for(int i = 1; i < 6; ++i) {
		v[i] = 10 - i;
		r[i] = (DB)v[0] / v[i];
		dx[i] = 10;
	}
	dy = 50 * sqrt2;
	DB L = 0, R = 1;
	for(int tt = 0; tt < 100; ++tt) {
		DB M = L + (R - L) * 0.5, dis = 0;
		for(int i = 0; i < 7; ++i)
			dis += dx[i] * M / sqrtl(r[i] * r[i] - M * M);
		if(dis < dy)
			L = M;
		else
			R = M;
	}
	DB tim = 0;
	for(int i = 0; i < 7; ++i)
		tim += dx[i] / sqrtl(r[i] * r[i] - L * L) * v[0] / v[i] / v[i];
	printf("%.10f\n", (double)tim);
	return 0;
}
