#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int t, n, a[maxn];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		int days = 0, pos = 1, cnt = a[0];
		for( ; pos < n; ++days)
			for(int lim = min(pos + cnt, n); pos < lim; cnt = min(cnt + a[pos++], n));
		printf("%d\n", days);
	}
	return 0;
}
