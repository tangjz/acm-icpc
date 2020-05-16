#include <bits/stdc++.h>
using namespace std;
int t, n;
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		printf("%lld\n", n * 4LL / __gcd(4, n + 1) + 1);
	}
	return 0;
}