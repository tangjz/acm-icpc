#include <bits/stdc++.h>
typedef double DB;
const int maxn = 1001;
int n, r, x[maxn];
DB y[maxn];
int main() {
	scanf("%d%d", &n, &r);
	for(int i = 0; i < n; ++i)
		scanf("%d", x + i);
	for(int i = 0; i < n; ++i) {
		y[i] = r;
		for(int j = 0; j < i; ++j) {
			int dx = std::abs(x[i] - x[j]);
			if(dx <= 2 * r)
				y[i] = std::max(y[i], y[j] + sqrt(4 * r * r - dx * dx));
		}
		printf("%.20f%c", y[i], " \n"[i == n - 1]);
	}
	return 0;
}
