#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 101;
int n, m;
LL a[maxn], c[3];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		scanf("%lld", a + i);
	for(int i = 2; i <= m + m; ++i) {
		int upp = min(i - 1, m), ctr = 0, mx[2] = {0, 0};
		for(int j = 0; j < n; ++j) {
			int rem = a[j] % i;
			if(rem + rem < i) {
				upp = min(upp, i - 1 - rem);
			} else {
				upp = min(upp, rem);
				ctr ^= 1;
			}
			int val = rem >> 1;
			if(mx[0] <= val)
				swap(mx[0], val);
			if(mx[1] <= val)
				swap(mx[1], val);
		}
		upp = min(upp, i - 1 - mx[ctr & 1]);
		if(upp + upp >= i) {
			int low = i - upp;
			c[ctr] += upp - low + 1;
		}
	}
	c[2] = ((LL)m * m - c[0] - c[1]) / 2;
	printf("%lld %lld %lld %lld\n", c[2], c[2], c[1], c[0]);
	return 0;
}
