#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 10010;
int n, s[maxn];
pair<int, int> p[maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d%d", &p[i].first, &p[i].second);
	sort(p, p + n);
	for(int i = 0; i < n; ++i)
		s[i] = (i ? s[i - 1] : 0) + p[i].second;
	int x = lower_bound(s, s + n, s[n - 1] >> 1) - s;
	printf("%d\n", x);
	long long ret = 0;
	for(int i = 0; i < n; ++i)
		ret += (long long)abs(p[i].first - p[x].first) * p[i].second;
	printf("%lld\n", ret);
	return 0;
} 
