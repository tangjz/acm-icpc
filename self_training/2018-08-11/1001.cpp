#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e3 + 1;
int n, a[maxn];
int main() {
	while(scanf("%d", &n) == 1) {
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		sort(a, a + n);
		int ans = -1;
		for(int i = 2; i < n; ++i)
			if(a[i] < a[i - 1] + a[i - 2])
				ans = max(ans, a[i] + a[i - 1] + a[i - 2]);
		printf("%d\n", ans);
	}
	return 0;
}
