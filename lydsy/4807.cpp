#include <stdio.h>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxn = 1000001, BLEN = 6, BSZ = 9, BASE = (int)1e9;
int n, m, tot, pr[maxn], d[maxn], cnt[maxn];
int tmp[3][BLEN], *pre = tmp[0], *cur = tmp[1], *ans = tmp[2];
int main()
{
	scanf("%d%d", &n, &m);
	if(n < m)
		std::swap(n, m);
	for(int i = 0; i < m; ++i)
	{
		++cnt[n - i];
		--cnt[i + 1];
	}
	for(int i = 2; i <= n; ++i)
	{
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) <= n; ++j)
		{
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	ans[0] = 1;
	for(int i = n; i >= 2; --i)
		if(d[i] < i)
		{
			cnt[d[i]] += cnt[i];
			cnt[i / d[i]] += cnt[i];
		}
		else
		{
			memset(cur, 0, sizeof tmp[0]);
			cur[0] = i;
			while(cnt[i] > 0)
			{
				if(cnt[i] & 1)
				{
					std::swap(ans, pre);
					LL val = 0;
					for(int i = 0; i < BLEN; ++i)
					{
						for(int j = 0; j <= i; ++j)
							val += (LL)pre[j] * cur[i - j];
						ans[i] = val % BASE;
						val /= BASE;
					}
				}
				if((cnt[i] >>= 1))
				{
					std::swap(cur, pre);
					LL val = 0;
					for(int i = 0; i < BLEN; ++i)
					{
						for(int j = 0; j <= i; ++j)
							val += (LL)pre[j] * pre[i - j];
						cur[i] = val % BASE;
						val /= BASE;
					}
				}
			}
		}
	bool chk = 0;
	ans[BLEN - 1] %= (int)1e5;
	for(int i = BLEN - 1; i >= 0; --i)
		if(chk)
			printf("%0*d", BSZ, ans[i]);
		else if(ans[i])
		{
			chk = 1;
			printf("%d", ans[i]);
		}
	if(!chk)
		putchar('0');
	putchar('\n');
	return 0;
}
