#include <cstdio>
int t, n, m, sum;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		sum = 0;
		scanf("%d%d", &n, &m);
		for(int i = 0, x; i < n; ++i)
			for(int j = 0; j < m; ++j)
			{
				scanf("%d", &x);
				sum += (i + j) & 1 ? x : -x;
			}
		puts(sum ? "No" : "Yes");
	}
	return 0;
}
