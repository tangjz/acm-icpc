#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)5e5 + 1;
int n, x, y;
LL ans;
multiset<int> sp;
int main() {
	scanf("%d", &n);
	while(n--) {
		scanf("%d", &x);
		sp.insert(x);
		y = *sp.rbegin();
		if(x < y) {
			ans += y - x;
			sp.erase(--sp.end());
			sp.insert(x);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
