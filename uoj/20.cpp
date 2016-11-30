#include <cstdio>
const int maxn = 101, maxm = 1000001, maxs = 10003, maxp = 3, maxv = 23333;
const int prime[maxp] = {19997, 21893, 22877};
int n, m, a[maxn][maxp], res[maxp][maxv], tot;
bool ans[maxm];
char str[maxs];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i <= n; ++i)
	{
		scanf("%s", str);
		bool flag = str[0] == '-';
		for(int j = flag; str[j]; ++j)
			for(int k = 0; k < maxp; ++k)
				a[i][k] = ((a[i][k] << 3) + (a[i][k] << 1) + (str[j] - '0')) % prime[k];
		if(!flag)
			continue;
		for(int j = 0; j < maxp; ++j)
			if(a[i][j])
				a[i][j] = prime[j] - a[i][j];
	}
	for(int i = 0; i < maxp; ++i)
		for(int j = 0; j < prime[i]; ++j)
		{
			int val = 0, now = 1;
			for(int k = 0; k <= n; ++k)
			{
				val = (val + now * a[k][i]) % prime[i];
				now = now * j % prime[i];
			}
			res[i][j] = val;
		}
	for(int i = 0; i <= m; ++i)
	{
		bool flag = 1;
		for(int j = 0; j < maxp; ++j)
			if(res[j][i % prime[j]])
			{
				flag = 0;
				break;
			}
		if(flag)
		{
			ans[i] = 1;
			++tot;
		}
	}
	printf("%d\n", tot);
	for(int i = 0; i <= m; ++i)
		if(ans[i])
			printf("%d\n", i);
	return 0;
}
