#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int main() {
	LL n;
	int ans = 0;
	scanf("%lld", &n);
	for(LL i = 1; i * i <= n; ++i)
		if(n % i == 0)
			ans += 1 + (i * i < n);
	printf("%d\n", ans);
}