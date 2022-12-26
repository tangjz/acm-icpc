#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e3 + 1;
int n, m, p, f[maxn];
int main() {
	scanf("%d%d%d", &n, &m, &p);
	f[1] = m;
	for(int i = 2; i <= n; ++i)
		(f[i] = ((LL)m * f[i - 1] - f[(i + 1) >> 1]) % p) < 0 && (f[i] += p);
	printf("%d\n", f[n]);
	return 0;
}
