#include <cstdio>
const int maxn = 1001, maxm = maxn * maxn;
int n, m, ans[maxm][3];
int main()
{
	scanf("%d", &n);
	if(n & 1)
		for(int i = 0; i < n; ++i)
			for(int j = 1; j << 1 < n; ++j)
			{
				ans[m][0] = i + 1;
				ans[m][1] = (i + j) % n + 1;
				ans[m++][2] = (i - j + n) % n + 1;
			}
	else
	{
		for(int i = 0; i < n - 1; ++i)
			for(int j = 1; j << 1 < n - 1; ++j)
			{
				ans[m][0] = i + 1;
				ans[m][1] = (i + j) % (n - 1) + 1;
				ans[m++][2] = (i - j + n - 1) % (n - 1) + 1;
				if(j == 1)
					continue;
				ans[m][0] = i + 1;
				ans[m][1] = (i + j) % (n - 1) + 1;
				ans[m++][2] = (i - j + n - 1) % (n - 1) + 1;
			}
		for(int i = 0; i < n - 1; ++i)
		{
			ans[m][0] = i + 1;
			ans[m][1] = (i + 1) % (n - 1) + 1;
			ans[m++][2] = n;
			ans[m][0] = i + 1;
			ans[m][1] = (i + 1) % (n - 1) + 1;
			ans[m++][2] = n;
		}
		for(int i = 0; i < n - 1; ++i)
		{
			ans[m][0] = i + 1;
			ans[m][1] = (i + 2) % (n - 1) + 1;
			ans[m++][2] = n;
		}
	}
	printf("%d\n", m);
	for(int i = 0; i < m; ++i)
		printf("%d %d %d\n", ans[i][0], ans[i][1], ans[i][2]);
	return 0;
}
