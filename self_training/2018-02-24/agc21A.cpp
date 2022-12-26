#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int main() {
	LL n;
	scanf("%lld", &n);
	char buf[21];
	int len = sprintf(buf, "%lld", n + 1), tp = 0, ans = 0;
	for(int i = 0; i < len; ++i) {
		buf[i] -= '0';
		if(buf[i])
			ans = max(ans, tp + buf[i] - 1 + (len - 1 - i) * 9);
		tp += buf[i];
	}
	printf("%d\n", ans);
	return 0;
}
