#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1;
int main() {
	int T;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int n;
		static int a[maxn];
		scanf("%d", &n);
		int low = a[0] = 0;
		LL ans = 0;
		unordered_map<int, int> ctr;
		ctr.reserve(n << 1 | 1);
		++ctr[0];
		for(int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			a[i] += a[i - 1];
			for(int j = 0, k = 0; k <= a[i] - low; k += (j++) << 1 | 1) {
				auto it = ctr.find(a[i] - k);
				if(it != ctr.end())
					ans += it -> second;
			}
			++ctr[a[i]];
			low = min(low, a[i]);
		}
		printf("Case #%d: %lld\n", Case, ans);
	}
	return 0;
}