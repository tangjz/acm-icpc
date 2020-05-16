#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1;
int n, m;
LL f[maxn];
inline LL calc(int n, int m) {
	int k = n / m;
	return (1 + (k - 1LL) * m + 1) * k / 2;
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i * i <= n; ++i) {
		if(n % i > 0)
			continue;
		f[m++] = calc(n, i);
		f[m++] = calc(n, n / i);
	}
	sort(f, f + m);
	m = unique(f, f + m) - f;
	for(int i = 0; i < m; ++i)
		printf("%I64d%c", f[i], " \n"[i == m - 1]);
	puts("");
	return 0;
}