#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = (int)2e5 + 1;
const DB pi = acos((DB)-1);
int main() {
	int T = 1;
	// scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int a, b, hh, mm;
		scanf("%d%d%d%d", &a, &b, &hh, &mm);
		DB x1 = a * cos(2 * pi / 720 * (hh * 60 + mm));
		DB y1 = a * sin(2 * pi / 720 * (hh * 60 + mm));
		DB x2 = b * cos(2 * pi / 60 * mm);
		DB y2 = b * sin(2 * pi / 60 * mm);
//		printf("(%f, %f) (%f, %f)\n", x1, y1, x2, y2);
		DB dis = sqrtl(max((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2), (DB)0));
		printf("%.20f\n", (double)dis);
	}
	return 0;
}