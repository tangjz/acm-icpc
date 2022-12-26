/*
 * 枚举答案 检查可行解时 先枚举将 后贪心递推 先凑刻子再从该处向后凑顺子
 */
#include <cstdio>
int n, m, num[401], tmp[401], ans[401], tot = 0;
int main()
{
	int i, j, k;
	scanf("%d%d", &n, &m);
	for(i = 0; i <= m * 3; ++i) { scanf("%d", &j); ++num[j]; }
	for(i = 1; i <= n; ++i)
	{
		++num[i];
		for(j = 1; j <= n; ++j)
			if(num[j] >= 2)
			{
				for(k = 1; k <= n; ++k) tmp[k] = num[k];
				tmp[j] -= 2;
				for(k = 1; k <= n; ++k)
				{
					tmp[k] %= 3;
					if(k + 2 > n && tmp[k] || tmp[k] > tmp[k + 1] || tmp[k] > tmp[k + 1]) break;
					tmp[k + 1] -= tmp[k];
					tmp[k + 2] -= tmp[k];
				}
				if(k > n) break;
			}
		--num[i];
		if(j <= n) ans[tot++] = i;
	}
	if(!tot) printf("NO\n");
	else
	{
		for(i = 0; i < tot - 1; ++i) printf("%d ", ans[i]);
		printf("%d\n", ans[tot - 1]);
	}
	return 0;
}
