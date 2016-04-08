#include <cstdio>
#include <cstring>
const int maxn = 10000001;
typedef long long LL;
int n, p, ans;
char s[maxn];
int main()
{
	while(scanf("%s%d", s, &p) == 2)
	{
		if(strlen(s) > 7)
		{
			puts("0");
			continue;
		}
		sscanf(s, "%d", &n);
		if(n >= p)
		{
			puts("0");
			continue;
		}
		ans = 1;
		for(int i = 2; i <= n; ++i)
			ans = (LL)ans * i % p;
		printf("%d\n", ans);
	}
	return 0;
}
