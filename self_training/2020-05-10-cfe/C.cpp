#include <bits/stdc++.h>
using namespace std;
typedef unsigned int UL;
typedef long long LL;
typedef unsigned long long ULL;
typedef double DB;
typedef long double LDB;
const int maxn = (int)3e5 + 1, maxd = 26, mod = (int)1e9 + 7, INF = 0x3f3f3f3f;
const LL INFLL = 0x3f3f3f3f3f3f3f3fLL;
const DB pi = acos((DB)-1);

int main() {
	int T = 1;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int a, b, q;
		scanf("%d%d%d", &a, &b, &q);
		int low = max(a, b), upp = a / __gcd(a, b) * b;
		if(low == upp) {
			while(q--) {
				scanf("%*lld%*lld");
				printf("0 ");
			}
			puts("");
			continue;
		}
		while(q--) {
			LL L, R;
			scanf("%lld%lld", &L, &R);
			LL ans = R - L + 1;
			for(int i = 0; i < low; ++i)
				ans -= (R >= i ? (R - i) / upp + 1 : 0) - (L > i ? (L - 1 - i) / upp + 1 : 0);
			printf("%lld ", ans);
		}
		puts("");
	}
	return 0;
}