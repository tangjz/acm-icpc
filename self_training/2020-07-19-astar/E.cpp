// p(disjoint) = (1/a[i-1] - 1/a[i]) / (2/a[i-1])
// p(disjoint) * (a[i]/2) = (a[i] - a[i-1]) / 4
// ans = V - E = sum(a[i]/2) - sum((1-p(disjoint))*(a[i]/2)) = (a[0] + a[n-1]) / 4
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = (int)1e9 + 7, inv2 = (mod + 1) >> 1;
int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		int n, fir, las;
		scanf("%d%d", &n, &fir);
		las = fir;
		for(int i = 1; i < n; ++i)
			scanf("%d", &las);
		int ans = (fir + las) / 2 * (LL)inv2 % mod;
		printf("%d\n", ans);
	}
}