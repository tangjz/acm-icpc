#include <stdio.h>
typedef long long LL;
const int maxn = 100;
int t;
LL n, f[maxn], ans;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld", &n);
		f[1] = 2, f[2] = 8, ans = 10;
		for(int i = 3; ; ++i)
		{
			f[i] = (f[i - 1] << 2) + f[i - 2];
			if(f[i] <= n)
				ans += f[i];
			else
				break;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
