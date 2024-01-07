#include <bits/stdc++.h>
using namespace std;
int t, Case, n;
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &Case, &n);
		printf("%d %d\n", Case, (int)floor((n * (n - 3) + 20) / 24.0 + ((n << 1) - 3) * (n & 1 ? 1 : -1) / 16.0));
	}
	return 0;
}
