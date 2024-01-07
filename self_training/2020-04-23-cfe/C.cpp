#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = (int)3e5 + 1, mod = (int)1e9 + 7;
const LL INF = (LL)1e13;
int t, n;
LL a[maxn], b[maxn];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		LL sum = 0, low = INF;
		for(int i = 0; i < n; ++i) {
			scanf("%lld%lld", a + i, b + i);
			if(i > 0) {
				sum += max(a[i] - b[i - 1], 0LL);
				low = min(low, min(a[i], b[i - 1]));
			}
		}
		sum += max(a[0] - b[n - 1], 0LL);
		low = min(low, min(a[0], b[n - 1]));
		printf("%lld\n", sum + low);
	}
	return 0;
}