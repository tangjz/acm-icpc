#include <map>
#include <stdio.h>
#include <algorithm>
typedef long long LL;
const int maxn = 100, maxp = 6, pr[maxp] = {2, 3, 5, 7, 11, 13}, maxpr = pr[maxp - 1];
int sg[maxn];
struct Hash
{
	int val[maxp];
	bool operator < (const Hash &t) const
	{
		for(int i = 0; i < maxp; ++i)
			if(val[i] != t.val[i])
				return val[i] < t.val[i];
		return 0;
	}
} cur;
std::map<Hash, int> sp;
int main()
{
	for(int i = 0; i < maxpr; ++i)
	{
		int tot = 0;
		for(int j = 0; pr[j] <= i; ++j)
			cur.val[tot++] = sg[i - pr[j]];
		std::sort(cur.val, cur.val + tot);
		for(int j = 0, k = 0; ; ++j)
			if(k < tot && cur.val[k] == j)
				while(k < tot && cur.val[k] == j)
					++k;
			else
			{
				sg[i] = j;
				break;
			}
	}
	int sta, cir;
	for(int i = maxpr; ; ++i)
	{
		for(int j = 0; j < maxp; ++j)
			cur.val[j] = sg[i - pr[j]];
		if(sp.count(cur))
		{
			sta = sp[cur];
			cir = i - sp[cur];
			break;
		}
		sp[cur] = i;
		std::sort(cur.val, cur.val + maxp);
		for(int j = 0, k = 0; ; ++j)
			if(k < maxp && cur.val[k] == j)
				while(k < maxp && cur.val[k] == j)
					++k;
			else
			{
				sg[i] = j;
				break;
			}
	}
	int t, n, SG;
	LL x;
	scanf("%d", &t);
	while(t--)
	{
		SG = 0;
		scanf("%d", &n);
		while(n--)
		{
			scanf("%lld", &x);
			SG ^= x < sta ? sg[(int)x] : sg[(int)((x - sta) % cir) + sta];
		}
		puts(SG ? "Manasa" : "Sandy");
	}
	return 0;
}
