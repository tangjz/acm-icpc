#include <cmath>
#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const LL INF = (LL)1e18;
int iSqrt(int x) {
	int sqt = (int)ceil(sqrt(x));
	for( ; sqt * sqt <= x; ++sqt);
	for( ; sqt * sqt > x; --sqt);
	return sqt;
}
LL calc(LL x, int y) {
	LL z = (LL)ceil(x / sqrt(y));
	for( ; (__int128_t)x * x >= (__int128_t)z * z * y; ++z);
	for( ; (__int128_t)x * x < (__int128_t)z * z * y; --z);
	return z;
}
void solve(int val, LL &xL, LL &yL, LL &xR, LL &yR, LL yLim, bool sp = 0) {
	for(LL xM = xL + xR, yM = yL + yR; yM <= yLim; xM = xL + xR, yM = yL + yR) {
		if((__int128_t)xM * xM <= (__int128_t)yM * yM * val) {
			LL L = 1, R = (yLim - yL) / yR;
			while(L < R) {
				LL M = (L + R + 1) >> 1;
				xM = xL + M * xR;
				yM = yL + M * yR;
				if((__int128_t)xM * xM <= (__int128_t)yM * yM * val)
					L = M;
				else
					R = M - 1;
			}
			xL += L * xR;
			yL += L * yR;
		} else {
			if(sp) {
				xR = xM;
				yR = yM;
				return;
			}
			LL L = 1, R = (yLim - yR) / yL;
			while(L < R) {
				LL M = (L + R + 1) >> 1;
				xM = xR + M * xL;
				yM = yR + M * yL;
				if((__int128_t)xM * xM > (__int128_t)yM * yM * val)
					L = M;
				else
					R = M - 1;
			}
			xR += L * xL;
			yR += L * yL;
		}
	}
}
int main() {
	int t, a;
	LL maxX, maxY, xL, yL, xR, yR;
	scanf("%d", &t);
	while(t--) {
		scanf("%d%lld%lld", &a, &maxY, &maxX);
		if(a > (__int128_t)maxX * maxX) { // no >= approach
			printf("%lld\n", maxX);
			continue;
		}
		int sqt = iSqrt(a);
		if(sqt * sqt == a) { // approach has no deviation
			puts("-1");
			continue;
		}
		solve(a, xL = sqt, yL = 1, xR = sqt + 1, yR = 1, min(calc(maxX, a), maxY));
		LL xT = xR;
		solve(a, xL, yL, xR, yR, calc(INF, a), 1);
		if(xT != xR)
			printf("%lld\n", xR);
		else
			puts("-1");
	}
	return 0;
}
