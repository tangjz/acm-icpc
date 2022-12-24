#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int t, n, m, a[maxn];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		sort(a, a + n, greater<int>());
		for( ; m < n && a[m - 1] == a[m]; ++m);
		printf("%d\n", m);
	}
	return 0;
}