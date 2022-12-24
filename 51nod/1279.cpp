#include <stdio.h>
const int maxn = 50001;
int n, m, a[maxn], pos, ans;
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0, mx = ~0u >> 1; i < n; ++i) {
		scanf("%d", a + i);
		a[i] = (mx = mx < a[i] ? mx : a[i]);
	}
	for(pos = n - 1; pos >= 0 && m--; --pos, ++ans) {
		int x;
		scanf("%d", &x);
		for( ; pos >= 0 && x > a[pos]; --pos);
		if(pos < 0)
			break;
	}
	printf("%d\n", ans);
	return 0;
}
