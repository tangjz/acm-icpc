#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int n, m, f[maxn];
pair<int, int> a[maxn];
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		a[i] = make_pair(y - x, x + y);
	}
	sort(a, a + n);
	for(int i = 0; i < n; ++i) {
		if(i && a[i - 1] == a[i])
			continue;
		int p = lower_bound(f + 1, f + m + 1, -a[i].second) - f;
		f[p] = -a[i].second;
		m += m < p;
	}
	printf("%d\n", m);
	return 0;
}
