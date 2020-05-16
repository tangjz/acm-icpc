#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e6 + 1;
int n;
LL a[maxn], c[3], ans;
char s[maxn];
bool v[3];
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%I64d", a + i);
	scanf("%s", s);
	for(int i = 0; i < n; ++i)
		if(s[i] == 'W') {
			ans += a[i] * 2;
			c[1] += a[i];
			v[1] = 1;
		} else if(s[i] == 'G') {
			LL rem = a[i], tmp;
			tmp = min(rem, c[1]);
			ans += tmp * 2;
			rem -= tmp;
			c[1] -= tmp;
			c[0] += tmp;
			ans += rem * 3;
			c[2] += rem;
			v[2] = 1;
		} else {
			ans += a[i];
			LL rem = a[i], tmp;
			tmp = min(rem, c[1]);
			ans += tmp;
			rem -= tmp;
			c[1] -= tmp;
			tmp = min(rem, c[0]);
			ans += tmp * 2;
			rem -= tmp;
			c[0] -= tmp;
			c[2] += tmp;
			tmp = min(rem, c[2]);
			ans += tmp * 2;
			rem -= tmp;
			c[2] -= tmp;
			tmp = v[1] ? 3 : 5;
			ans += rem * tmp;
		}
	printf("%I64d\n", ans);
	return 0;
}