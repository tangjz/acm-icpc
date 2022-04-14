#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1;
int n, ans;
LL m, x;
int main() {
	scanf("%*lld%d%lld%lld", &n, &m, &x);
	for(int i = 0; i < n; ++ans) {
		LL pid = (x - i - 1) / m + 1, upp = pid * m + i;
		while((++i) < n) {
			scanf("%lld", &x);
			if(x > upp)
				break;
		}
	}
	printf("%d\n", ans);
	return 0;
}