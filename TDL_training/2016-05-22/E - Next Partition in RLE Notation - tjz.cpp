#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100010;
int tot;
LL n, m;
pair<LL, LL> a[maxn], b[maxn];
int main()
{
	scanf("%d", &tot);
	for(int i = 0; i < tot; ++i)
		scanf("%lld%lld", &a[i].second, &a[i].first);
	sort(a, a + tot);
	LL sum = 0, cnt = 0;
	for(int i = 0; i < tot; ++i)
	{
		if(i > 0)
		{
			LL tmp = (sum + 1) / (a[i].first - 1) + ((sum + 1) % (a[i].first - 1) > 0);
			if(cnt >= tmp)
			{
				int sz = 0;
				for(int j = tot - 1; j >= i; --j)
					b[sz++] = a[j];
				LL val = b[sz - 1].first - 1;
				if(!(--b[sz - 1].second))
					--sz;
				b[sz++] = make_pair(val, 1);
				++sum;
				LL num = (sum - cnt) / (val - 1);
				b[sz - 1].second += num;
				sum -= num * val;
				cnt -= num;
				if(sum - cnt + 1 > 1)
				{
					b[sz++] = make_pair(sum - cnt + 1, 1);
					sum -= sum - cnt + 1;
					--cnt;
				}
				if(cnt > 0)
					b[sz++] = make_pair(1, cnt);
				printf("%d\n", sz);
				for(int i = 0; i < sz; ++i)
					printf("%lld %lld\n", b[i].second, b[i].first);
				return 0;
			}
		}
		sum += a[i].first * a[i].second;
		cnt += a[i].second;
	}
	puts("-1");
	return 0;
}
