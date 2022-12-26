#include <set>
#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn = 50001;
int n, m;
long long ans;
pair<int, int> a[maxn];
multiset<int> sp;
int main() {
	scanf("%d%d", &n, &m);
	while(n--) {
		int x;
		scanf("%d", &x);
		sp.insert(x);
	}
	for(int i = 0; i < m; ++i) {
		int c, w;
		scanf("%d%d", &w, &c);
		a[i] = make_pair(c, -w);
	}
	sort(a, a + m);
	for(int i = 0; i < m; ++i) {
		multiset<int>::iterator it = sp.upper_bound(-a[i].second);
		if(it != sp.begin()) {
			sp.erase(--it);
			ans += a[i].first;
			if(sp.empty())
				break;
		}
	}
	if(sp.empty())
		printf("%lld\n", ans);
	else
		puts("No Solution");
	return 0;
}
