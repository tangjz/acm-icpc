#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1, maxs = 41;
int t, n, top;
LL x, ans;
pair<int, LL> s[maxs];
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%lld", &x);
		s[top++] = make_pair(i, 0LL);
		for(int j = 0; j < top; ++j)
			s[j].second = __gcd(x, s[j].second);
		int k = 0;
		for(int j = 0; j < top; ++j)
			if(!j || s[j - 1].second != s[j].second)
				s[k++] = s[j];
		top = k;
		for(int j = 0; j < top; ++j)
			ans = max(ans, (i - s[j].first + 1) * s[j].second);
	}
	printf("%lld\n", ans);
	return 0;
}
