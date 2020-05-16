#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = (int)1e5 + 1;
int n, x[maxn], y[maxn];
int main() {
	scanf("%d", &n);
	DB xL = 1e7, xR = -1e7;
	for(int i = 0; i < n; ++i) {
		scanf("%d%d", x + i, y + i);
		if((y[i] > 0) != (y[0] > 0)) {
			puts("-1");
			return 0;
		}
		xL = min(xL, (DB)x[i]);
		xR = max(xR, (DB)x[i]);
	}
	if(y[0] < 0)
		for(int i = 0; i < n; ++i)
			y[i] = -y[i];
	for(int i = 0; i < 100; ++i) {
		DB x0 = xL + (xR - xL) / 3, x1 = xR - (xR - xL) / 3;
		DB y0 = 0, y1 = 0;
		for(int j = 0; j < n; ++j) {
			y0 = max(y0, (x0 - x[j]) * (x0 - x[j]) / y[j] / 2 + y[j] * 0.5);
			y1 = max(y1, (x1 - x[j]) * (x1 - x[j]) / y[j] / 2 + y[j] * 0.5);
		}
		if(y0 < y1) {
			xR = x1;
		} else {
			xL = x0;
		}
	}
	DB r = 0;
	for(int i = 0; i < n; ++i)
		r = max(r, (xL - x[i]) * (xL - x[i]) / y[i] / 2 + y[i] * 0.5);
	printf("%.20f\n", r);
	return 0;
}
