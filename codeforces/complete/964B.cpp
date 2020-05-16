#include <bits/stdc++.h>
using namespace std;
int main() {
	int n, A, B, C, T;
	scanf("%d%d%d%d%d", &n, &A, &B, &C, &T);
	int ans = 0;
	while(n--) {
		int x;
		scanf("%d", &x);
		ans += max(A, A + (C - B) * (T - x));
	}
	printf("%d\n", ans);
	return 0;
}