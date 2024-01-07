#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)2e5 + 1;
int main() {
	int T;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int n, m;
		static int a[maxn];
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		int ans = 0;
		for(int i = 0; i <= n - m; ++i) {
			if(a[i] != m)
				continue;
			bool chk = 1;
			for(int j = 0; chk && j < m; ++j)
				chk &= a[i + j] == m - j;
			ans += chk;
		}
		printf("Case #%d: %d\n", Case, ans);
	}
	return 0;
}