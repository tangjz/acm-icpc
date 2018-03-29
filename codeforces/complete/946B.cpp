#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL n, m;
int main() {
	scanf("%lld%lld", &n, &m);
	while(n && m)
		if(n >= m * 2)
			n %= m * 2;
		else if(m >= n * 2)
			m %= n * 2;
		else
			break;
	printf("%lld %lld\n", n, m);
	return 0;
}
