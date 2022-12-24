#include <bits/stdc++.h>
using namespace std;
const int maxl = 1003, BLEN = 8, BASE = (int)1e8, maxn = 127;
bool init(int &len, int num[]) {
	static char buf[maxl];
	if(scanf("%s", buf) != 1)
		return 0;
	len = 0;
	for(int slen = strlen(buf), i = 0, j = (slen - 1) % BLEN + 1; i < slen; ++len, j += BLEN)
		for(num[len] = 0; i < j; ++i)
			num[len] = num[len] * 10 + (buf[i] - '0');
	reverse(num, num + len);
	return 1;
}
int div5(int &len, int num[]) {
	int rem = 0;
	for(int i = len - 1; i >= 0; --i) {
		rem = rem * BASE + num[i];
		num[i] = rem / 5;
		rem %= 5;
	}
	if(len > 1 && !num[len - 1])
		--len;
	return rem;
}
int main() {
	int len, num[maxn], ans;
	while(init(len, num)) {
		for(ans = 1; !(len == 1 && !num[0]); ans %= 10) {
			int rem = div5(len, num);
			static const int table1[] = {1, 1, 2, 6, 4}, table2[] = {6, 2, 4, 8};
			ans *= table1[rem] + (rem == 1 && num[0] & 1 ? 5 : 0);
			if(!(len == 1 && !num[0]))
				ans *= table2[num[0] & 3];
		}
		printf("%d\n", ans);
	}
	return 0;
}