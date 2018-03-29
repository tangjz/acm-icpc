#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)5e5 + 1;
int n, x, y;
LL ans;
multiset<int> sp;
int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		scanf("%d", &x);
		sp.insert(x -= i);
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
