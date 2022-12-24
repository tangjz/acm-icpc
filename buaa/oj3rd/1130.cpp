#include <cstdio>
#include <algorithm>
using namespace std;
int n, k;
long long ans;
struct Node
{
	long long a, b;
	bool operator < (const Node &x) const
	{
		return a * x.b < x.a * b || a * x.b == x.a * b && a < x.a;
	}
} s[1001];
int main()
{
	while(scanf("%d%d", &n, &k) == 2)
	{
		ans = 0;
		for(int i = 0; i < n; ++i)
			scanf("%d", &s[i].a);
		for(int i = 0; i < n; ++i)
			scanf("%d", &s[i].b);
		sort(s, s + n);
		for(int i = 0; i < n; ++i)
			if(s[i].a <= k)
			{
				k -= s[i].a;
				ans += s[i].b;
			}
			else
				break;
		printf("%lld\n", ans);
	}
	return 0;
}
