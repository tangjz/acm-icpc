#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int t;
LL a, b;
bool isprime(LL x) {
	if(x < 2)
		return 0;
	for(LL i = 2; i * i <= x; ++i)
		if(x % i == 0)
			return 0;
	return 1;
}
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%lld%lld", &a, &b);
		puts(a - b == 1 && isprime(a + b) ? "YES" : "NO");
	}
	return 0;
}
