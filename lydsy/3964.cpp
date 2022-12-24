#include <bits/stdc++.h>
using namespace std;
typedef double DB;
const DB pi = acos(-1);
const int maxn = 501, maxt = 50;
int n, a[maxn];
DB getAngles(int L, int R, DB rad) {
	DB ret = 0;
	for(int i = L; i < R; ++i)
		ret += asin(a[i] / 2.0 / rad);
	return ret;
};
DB solve(int L, int R) {
	if(R - L < 3) {
		if(R - L == 2 && a[L] > a[L + 1])
			swap(a[L], a[L + 1]);
		return 0;
	}
	int sum = 0, pos = L;
	for(int i = L; i < R; ++i) {
		sum += a[i];
		if(a[pos] < a[i])
			pos = i;
	}
	DB ret = solve(L, pos) + solve(pos + 1, R);
	inplace_merge(a + L, a + pos + 1, a + R);
	if(a[R - 1] * 2 < sum) {
		DB low = a[R - 1] / 2.0, upp;
		bool hasLarge = getAngles(L, R, low) < pi;
		if(hasLarge) {
			upp = sum * pi;
			for(int j = 0; j < maxt; ++j) {
				DB mid = low + (upp - low) / 2;
				if(getAngles(L, R - 1, mid) < asin(a[R - 1] / 2.0 / mid))
					low = mid;
				else
					upp = mid;
			}
		} else {
			upp = sum / 2.0;
			for(int j = 0; j < maxt; ++j) {
				DB mid = low + (upp - low) / 2;
				if(getAngles(L, R, mid) < pi)
					upp = mid;
				else
					low = mid;
			}
		}
		DB area = 0;
		for(int i = L; i < R - hasLarge; ++i)
			area += a[i] * sqrtl(low * low - a[i] * a[i] / 4.0);
		if(hasLarge)
			area -= a[R - 1] * sqrtl(low * low - a[R - 1] * a[R - 1] / 4.0);
		ret = max(ret, area / 2);
	}
	return ret;
}
int main() {
	for(int Case = 1; scanf("%d", &n) == 1 && n; ++Case) {
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		printf("Case %d: %.5f\n", Case, solve(0, n));
	}
	return 0;
}
