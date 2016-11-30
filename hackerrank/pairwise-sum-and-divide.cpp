#include <stdio.h>
typedef long long LL;
const int maxn = 200001;
int t, n, x, s[2];
LL ans;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		s[0] = s[1] = 0;
		for(int i = 0; i < n; ++i)
		{
			scanf("%d", &x);
			if(--x < 2)
				++s[x];
		}
		printf("%lld\n", s[0] * (n - 1LL) + (s[1] * (s[1] - 1LL) >> 1));
	}
	return 0;
}
