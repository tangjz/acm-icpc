#include <cstdio>
#include <cstring>
int t, n, aa, bb, a[101], b[101], f[1001];
int main()
{
	int Case = 0;
	scanf("%d", &t);
	while(t--)
	{
		memset(f, 0, sizeof f);
		scanf("%d%d%d", &aa, &bb, &n);
		for(int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		for(int i = 1; i <= n; ++i)
			scanf("%d", b + i);
		for(int i = 1; i <= n; ++i)
			for(int j = aa; j >= a[i]; --j)
				if(f[j] < f[j - a[i]] + b[i])
					f[j] = f[j - a[i]] + b[i];
		bool flag = 0;
		for(int i = 0; i <= aa; ++i)
			if(f[i] >= bb)
			{
				flag = 1;
				break;
			}
		printf("Case #%d: %s\n", ++Case, flag ? "YES" : "NO");
	}
	return 0;
}
