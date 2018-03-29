#include <bits/stdc++.h>
using namespace std;
int main() {
	int a, b, L, R, ans;
	scanf("%d%d%d%d", &a, &b, &L, &R);
	int xL = (L - 1) / (a + b), yL = (L - 1) % (a + b);
	int xR = (R - 1) / (a + b), yR = (R - 1) % (a + b);
	if(a <= b) {
		if(xL == xR) {
			ans = min(yR, a - 1) - min(yL, a - 1) + 1;
		} else if(xL + 1 == xR) {
			int lft = max(a - yL, 1), rht = min(yR + 1, a);
			ans = min(lft + rht, a) + (rht == a);
		} else {
			ans = a + 1;
		}
	} else {
		int dif = a - b;
		if(xL == xR) {
			ans = min(yR, a - 1) - min(yL, a - 1) + 1;
		} else if(xL + 1 == xR) {
			ans = max(min(a - yL, dif), 1) + min(yR + 1, a);
		} else if(xL + 2 == xR) {
			ans = a + max(1, max(min(yR + 1, a) - b, 0));
		} else {
			ans = a + dif;
		}
	}
	printf("%d\n", ans);
	return 0;
}
