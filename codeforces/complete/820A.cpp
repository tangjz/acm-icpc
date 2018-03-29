#include <bits/stdc++.h>
using namespace std;
int c, v0, v1, a, l, ans;
int main() {
	scanf("%d%d%d%d%d", &c, &v0, &v1, &a, &l);
	for(ans = 0; c > 0; ++ans) {
		c -= v0 - (ans ? l : 0);
		v0 = min(v0 + a, v1);
	}
	printf("%d\n", ans);
	return 0;
}
