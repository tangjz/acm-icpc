#include <set>
#include <stdio.h>
const int maxn = 10001;
int n, m, ans;
std::multiset<int> sp;
int main() {
	scanf("%d%d", &n, &m);
	while(n--) {
		scanf("%d", &ans);
		sp.insert(ans);
	}
	for(ans = 0; sp.size() > 0; ++ans) {
		int mx = *sp.rbegin();
		sp.erase(sp.find(mx));
		if(sp.size() > 0) {
			std::multiset<int>::iterator it = sp.upper_bound(m - mx);
			if(it != sp.begin())
				sp.erase(--it);
		}
	}
	printf("%d\n", ans);
	return 0;
}
