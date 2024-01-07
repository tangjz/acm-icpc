#include <map>
#include <cstdio>
#include <algorithm>
typedef long long LL;
const int maxn = 2001;
int n, x[maxn], y[maxn], fm[maxn];
LL ans;
std::map<std::pair<LL, LL>, int> Hash;
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		x[i] = a * c;
		y[i] = b * c;
		fm[i] = a * a + b * b;
	}
	for(int i = 0; i < n; ++i)
	{
		std::map<std::pair<LL, LL>, int>().swap(Hash);
		for(int j = i + 1; j < n; ++j)
		{
			LL p = (LL)x[i] * fm[j] - (LL)x[j] * fm[i];
			LL q = (LL)y[i] * fm[j] - (LL)y[j] * fm[i];
			if(p < 0)
			{
				p = -p;
				q = -q;
			}
			else if(!p && q < 0)
				q = -q;
			else if(!p && !q)
			{
				ans += n - i - 2;
				continue;
			}
			LL r = std::__gcd(p, q);
			p /= r;
			q /= r;
			ans += Hash[std::make_pair(p, q)]++;
		}
	}
	printf("%I64d\n", ans);
	return 0;
}
