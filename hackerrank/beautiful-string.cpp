#include <bits/stdc++.h>
typedef long long LL;
const int maxn = (int)1e6 + 1;
int c1, c2, c3;
char buf[maxn];
int main() {
	scanf("%s", buf);
	for(int i = 0, j = 0; buf[i]; ++i) {
		++j;
		if(buf[i] != buf[i + 1]) {
			++c1;
			c2 += j >= 2;
			j = 0;
		}
		c3 += i && buf[i - 1] != buf[i] && buf[i - 1] == buf[i + 1];
	}
	printf("%lld\n", c1 * (c1 - 1LL) / 2 + c2 - c3);
	return 0;
}
