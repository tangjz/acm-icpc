#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = (int)2e3 + 1, maxd = 26 + 1;
const int mod = (int)1e9 + 7;


int main() {
	int T = 1;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		int n, k, ctr[maxd] = {};
		static char buf[maxn];
		scanf("%d%d%s", &n, &k, buf);
		for(int i = 0; i < n; ++i)
			++ctr[(int)(buf[i] - 'a')];
		for(int i = n; i >= 1; --i) {
			int com = i / __gcd(i, k);
			int upp = 0;
			for(int j = 0; j < maxd; ++j)
				upp += ctr[j] / com * com;
			if(i <= upp) {
				printf("%d\n", i);
				break;
			}
		}
		// printf("Case #%d:");
	}

	return 0;
}