#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1;
const LL maxv = (1LL << 32) - 1;
int n, m;
LL ans;
pair<LL, int> stk[maxn];
int main() {
	scanf("%d", &n);
	while(n--) {
		static char buf[5];
		scanf("%s", buf);
		switch(buf[0]) {
			case 'a' : {
				++ans;
				ans = min(ans, maxv + 1);
				break;
			}
			case 'f' : {
				stk[++m].first = ans;
				scanf("%d", &stk[m].second);
				ans = 0;
				break;
			}
			case 'e' : {
				ans = ans * stk[m].second + stk[m].first;
				ans = min(ans, maxv + 1);
				--m;
				break;
			}
		}
	}
	if(ans <= maxv)
		printf("%lld\n", ans);
	else
		puts("OVERFLOW!!!");
	return 0;
}