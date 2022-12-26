#include <cstdio>
typedef long long LL;
const int maxn = 100001;
int t, n, a[maxn];
LL sum;
int main()
{
	while(scanf("%d", &t) != EOF)
	{
		while(t--)
		{
			bool flag = 1;
			sum = 0;
			scanf("%d", &n);
			for(int i = 1; i <= n; ++i)
			{
				scanf("%d", a + i);
				a[i] -= n - 1;
				sum += a[i];
				flag &= -n < a[i] && a[i] < n;
			}
			flag &= !sum;
			puts(flag ? "T" : "F");
		}
	}
	return 0;
}
