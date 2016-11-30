#include <bitset>
#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn = 20, maxd = 9, mod = 1000000007;
const int maxv = maxn * maxn, maxm = (maxn << 1) + maxv * maxd;
int t, n, m, all, tot, a[maxv], que[maxm];
bitset<maxv + 1> mat[maxm];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		all = n * n;
		tot = 0;
		for(int i = 0; i < all; ++i)
		{
			scanf("%d", a + i);
			int tmp = a[i];
			for(int j = 2; j * j <= tmp; ++j)
				if(tmp % j == 0)
				{
					for(tmp /= j; tmp % j == 0; tmp /= j);
					que[tot++] = j;
				}
			if(tmp > 1)
				que[tot++] = tmp;
		}
		sort(que, que + tot);
		tot = unique(que, que + tot) - que;
		m = 0;
		for(int i = 0; i < tot; ++i)
		{
			mat[m].reset();
			for(int j = 0; j < all; ++j)
			{
				int cnt = 0;
				for( ; a[j] % que[i] == 0; a[j] /= que[i], ++cnt);
				if(cnt & 1)
					mat[m].set(j);
			}
			++m;
		}
		for(int i = 0; i < n; ++i)
		{
			mat[m].reset();
			for(int j = 0, jdx = i * n; j < n; ++j, ++jdx)
				mat[m].set(jdx);
			mat[m++].set(all);
			mat[m].reset();
			for(int j = 0, jdx = i; j < n; ++j, jdx += n)
				mat[m].set(jdx);
			mat[m++].set(all);
		}
		int r = 0, ans = 1;
		for(int i = 0; i < all; ++i)
		{
			int k = -1;
			for(int j = r; j < m; ++j)
				if(mat[j].test(i))
				{
					k = j;
					break;
				}
			if(k == -1)
			{
				if((ans <<= 1) >= mod)
					ans -= mod;
				continue;
			}
			swap(mat[r], mat[k]);
			for(int j = 0; j < m; ++j)
				if(j != r && mat[j].test(i))
					mat[j] ^= mat[r];
			++r;
		}
		for(int i = r; i < m; ++i)
			if(mat[i].count() == 1 && mat[i].test(all))
			{
				ans = 0;
				break;
			}
		printf("%d\n", ans);
	}
	return 0;
}
