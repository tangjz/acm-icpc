#include <bits/stdc++.h>
using namespace std;
const int maxn = 31;
int t, n, m, dam[maxn];
char buf[maxn];

int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%s", &m, buf);
		n = strlen(buf);
		for(int i = 0, v = 1; i < n; ++i)
			if(buf[i] == 'C') {
				dam[i] = 0;
				v <<= 1;
			} else {
				dam[i] = v;
				m -= v;
			}
		int ans = 0;
		while(m < 0) {
			bool chk = 0;
			for(int i = n - 1; i > 0; --i)
				if(buf[i - 1] == 'C' && buf[i] == 'S') {
					swap(buf[i - 1], buf[i]);
					swap(dam[i - 1], dam[i]);
					dam[i - 1] >>= 1;
					m += dam[i - 1];
					chk = 1;
					break;
				}
			if(!chk)
				break;
			++ans;
		}
		if(m < 0) {
			printf("Case #%d: IMPOSSIBLE\n", Case);
		} else {
			printf("Case #%d: %d\n", Case, ans);
		}
	}
	return 0;
}
