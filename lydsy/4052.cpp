#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100001, maxs = 15;
int t, n, top;
long long ans;
pair<int, long long> s[maxs];
long long gcd(long long x, long long y)
{
	return y ? gcd(y, x % y) : x;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		ans = top = 0;
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
		{
			long long x;
			scanf("%lld", &x);
			s[top++] = {i, 0LL};
			for(int j = 0; j < top; ++j)
				s[j].second = gcd(x, s[j].second);
			int k = 0;
			for(int j = 0; j < top; ++j)
				if(!j || s[j - 1].second != s[j].second)
					s[k++] = s[j];
			top = k;
			for(int j = 0; j < top; ++j)
				ans = max(ans, (i - s[j].first + 1) * s[j].second);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
