#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = (int)1e5 + 1, mod = (int)1e9 + 7;
int t, n, m, a[maxn];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		sort(a, a + n, greater<int>());
		int pos = 0;
		LL sum = 0;
		for( ; pos < n && (sum + a[pos]) >= m * (pos + 1LL); sum += a[pos++]);
		printf("%d\n", pos);
	}
	return 0;
}