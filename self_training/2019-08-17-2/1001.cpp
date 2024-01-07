#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e3 + 1;
int T, n, m, a[maxn], b[maxn];
int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		m = n;
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		for(int i = 0; i < n; ++i)
			scanf("%d", b + i);
		for( ; n && !a[n - 1]; --n);
		for( ; m && !b[m - 1]; --m);
		int fz, fm;
		if(n > m) {
			fz = 1;
			fm = 0;
		} else if(n < m) {
			fz = 0;
			fm = 1;
		} else {
			fz = a[n - 1];
			fm = b[m - 1];
		}
		int r = __gcd(fz, fm);
		printf("%d/%d\n", fz / r, fm / r);
	}
	return 0;
}