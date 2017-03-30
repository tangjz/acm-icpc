#include <stdio.h>
typedef long long LL;
const int maxn = 1000001;
int t, n, mx = 1;
LL f[maxn];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i; mx <= n; ++mx)
		{
			if(mx % 7)
			{
				static char buf[7];
				sprintf(buf, "%d", mx);
				for(i = 0; buf[i]; ++i)
					if(buf[i] == '7')
						break;
				if(!buf[i])
					f[mx] = (LL)mx * mx;
			}
			f[mx] += f[mx - 1];
		}
		printf("%lld\n", f[n]);
	}
	return 0;
}
