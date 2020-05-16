#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int main() {
	LL n, m, k, l;
	scanf("%lld%lld%lld%lld", &n, &m, &k, &l);
	l = (k + l - 1) / m + 1;
	printf("%lld\n", l * m <= n ? l : -1);
	return 0;
}