#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1;
int n, m, x[maxn];
LL low, upp;
int main() {
	scanf("%d%d", &m, &n);
	m <<= 1;
	for(int i = 0; i < n; ++i)
		scanf("%d %*c", x + i);
	sort(x, x + n);
	for(int i = 1; i < n; i += 2)
		x[i] = m - x[i];
	sort(x, x + n);
	low = ~0ULL >> 1;
	upp = -low;
	for(int i = 0; i < n; ++i) {
		LL val = (LL)x[i] * n - (LL)i * m;
		low = min(low, val);
		upp = max(upp, val);
	}
	printf("%.6f\n", (double)(upp - low) / (n << 1));
	return 0;
}
