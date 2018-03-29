#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxm = 61;
LL n;
int p, m, dig[maxm];
int main() {
	scanf("%lld%d", &n, &p);
	while(n) {
		(dig[m] = n % p) < 0 && (dig[m] += p);
		n = (n - dig[m++]) / -p;
	}
	printf("%d\n", m);
	for(int i = 0; i < m; ++i)
		printf("%d%c", dig[i], " \n"[i == m - 1]);
	return 0;
}
