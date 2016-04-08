/*
 * dfs字典序最小哈密顿回路 
 */
#include <cstdio>
#include <cstring>
int a[2049] = {}, used[2049] = {}, k, n;
void dfs()
{
	int lastmp = 0, cur = 1, fail, temp, tused[2049], i, j;
	memset(a, -1, sizeof(a));
	while(1)
	{
		if(cur > n)
		{
			fail = 0;
			memset(tused, 0, sizeof(tused));
			for(i = 1; i <= n; ++i)
			{
				temp = 0;
				for(j = 1; j <= k; ++j) temp += a[(i + j - 2) % n + 1] << (k - j);
				if(!tused[temp]) ++tused[temp];
				else { ++fail; break; }
			}
			if(!fail)	
			{
				for(i = 1; i <= n; ++i) printf("%d", a[i]);
				return;
			}
		}
		else
		{
			temp = 0;
			if(a[cur] > 1) a[cur] = 0;
			else ++a[cur];
			if(cur >= k)	
			{
				for(i = 1; i <= k; ++i) temp += a[cur - i + 1] << (i - 1);
				if(!used[temp])
				{
					++used[temp];
					++cur;
					lastmp = temp;
					continue;
				}
			}
			else { ++cur; continue; }
		}
		if(a[cur] >= 1)
		{
			a[cur] = -1;
			--used[lastmp];
			--cur;
		}
		if(cur > n) --cur;
	}
}
int	main()
{
	scanf("%d", &k);
	n = 1 << k;
	printf("%d ", n);
	dfs();
	return 0;
}
