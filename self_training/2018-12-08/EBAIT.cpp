#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e6 + 1, INF = 0x3f3f3f3f;
int t, n, xMax, yMax, fz, fm, tfz, tfm;
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d%d", &n, &xMax, &yMax);
		fz = tfz = tfm = 0;
		fm = 1;
		for(int i = 0, x; i < n; ++i) {
			scanf("%d", &x);
			(i & 1 ? tfz : tfm) += x;
			if(i + 1 < n && (LL)fz * tfm < (LL)tfz * fm) {
				fz = tfz;
				fm = tfm;
			}
		}
		if((LL)fz * tfm >= (LL)tfz * fm) {
			puts("-1");
			continue;
		}
		int xL = 0, yL = 1, xR = 1, yR = 0;
		while(1) {
			int xM = xL + xR, yM = yL + yR;
			if(xM > xMax || yM > yMax)
				break;
			if((LL)fz * yM < (LL)fm * xM) {
				int L = 1, R = min(xL ? (xMax - xR) / xL : INF, yL ? (yMax - yR) / yL : INF);
				while(L < R) {
					int M = (L + R + 1) >> 1;
					xM = M * xL + xR;
					yM = M * yL + yR;
					if((LL)fz * yM < (LL)fm * xM) {
						L = M;
					} else {
						R = M - 1;
					}
				}
				xR += L * xL;
				yR += L * yL;
			} else {
				int L = 1, R = min(xR ? (xMax - xL) / xR : INF, yR ? (yMax - yL) / yR : INF); 
				while(L < R) {
					int M = (L + R + 1) >> 1;
					xM = xL + M * xR;
					yM = yL + M * yR;
					if((LL)fz * yM >= (LL)fm * xM) {
						L = M;
					} else {
						R = M - 1;
					}
				}
				xL += L * xR;
				yL += L * yR;
			}
		}
		if((LL)xR * tfm >= (LL)yR * tfz) {
			puts("-1");
		} else {
			printf("%d %d\n", xR, yR);
		}
	}
	return 0;
}
