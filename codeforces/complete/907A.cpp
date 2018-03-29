#include <bits/stdc++.h>
using namespace std;
int main() {
	int a, b, c, d;
	scanf("%d%d%d%d", &a, &b, &c, &d);
	int low = max(c, d), mid = max(low + 1, max(b, d << 1 | 1)), upp = max(mid + 1, max(a, d << 1 | 1));
	if(low <= min(c, d) << 1 && mid <= b << 1 && upp <= a << 1) {
		printf("%d %d %d\n", upp, mid, low);
	} else {
		puts("-1");
	}
	return 0;
}
