#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)2e5 + 1, maxd = 10;
int t, len, cnt[maxd];
char buf[maxn];
int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%s", buf);
		len = strlen(buf);
		int odd = 0, chk = 0;
		memset(cnt, 0, sizeof cnt);
		for(int i = 0; i < len; ++i)
			cnt[buf[i] - '0'] ^= 1;
		for(int i = 0; i < maxd; ++i)
			odd += cnt[i] & 1;
		for(int i = len - 1; i >= 0 && !chk; --i) {
			int dig = buf[i] - '0';
			odd -= cnt[dig] & 1;
			cnt[dig] ^= 1;
			odd += cnt[dig] & 1;
			for(int j = dig - 1; j >= !i && !chk; --j) {
				odd -= cnt[j] & 1;
				cnt[j] ^= 1;
				odd += cnt[j] & 1;
				if(odd <= len - 1 - i && !((len - 1 - i - odd) & 1)) {
					buf[i] = '0' + j;
					int k;
					for(k = i + 1; k < len - odd; ++k)
						buf[k] = '9';
					for(int o = maxd - 1; o >= 0; --o)
						if(cnt[o])
							buf[k++] = '0' + o;
					puts(buf);
					chk = 1;
				}
				odd -= cnt[j] & 1;
				cnt[j] ^= 1;
				odd += cnt[j] & 1;
			}
		}
		if(!chk) {
			int len2 = len - 1 - !(len & 1);
			for(int i = 0; i < len2; ++i)
				buf[i] = '9';
			buf[len2] = '\0';
			puts(buf);
		}
	}
	return 0;
}
