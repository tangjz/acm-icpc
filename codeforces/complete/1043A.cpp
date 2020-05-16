#include <bits/stdc++.h>
using namespace std;
const int maxn = 101;
int n, a[maxn], mx, sum;
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		scanf("%d", a + i);
		mx = max(mx, a[i]);
		sum += a[i];
	}
	printf("%d\n", max((sum + sum) / n + 1, mx));
	return 0;
}