#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 21;
int t, Case, n;
LL c[maxn], f[maxn];
int main() {
	c[0] = c[1] = 1;
	f[0] = f[1] = 2;
	for(int i = 2; i < maxn; ++i) {
		for(int j = i - 1; j >= 0; --j) {
			f[i] += c[j] * f[j] * f[i - 1 - j] >> 2;
			c[j + 1] += c[j];
		}
		c[0] = 1;
	}
	f[1] = 1;
	scanf("%d", &t);
	while(t--) {
		scanf("%d%d", &Case, &n);
		printf("%d %lld\n", Case, f[n]);
	}
	return 0;
}
