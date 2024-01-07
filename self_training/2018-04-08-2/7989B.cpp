#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, maxv = (int)1e7 + 1;
int n, a[maxn];
LL ans;
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		scanf("%d", a + i);
		if(i && !a[i] && a[i - 1]) {
			puts("-1");
			return 0;
		}
	}
	for(int i = 1; i < n; ++i)
		while(a[i - 1] > a[i])
			if(a[i] * 2 < maxv) {
				++ans;
				a[i] *= 2;
			} else {
				a[i - 1] = (a[i - 1] + 1) >> 1;
				ans += n - i;
			}
	printf("%lld\n", ans);
	return 0;
}
