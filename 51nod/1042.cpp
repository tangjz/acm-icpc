#include <stdio.h>
#include <cstring>
const int maxs = 19, maxd = 10;
typedef long long LL;
LL pw10, cnt[maxd];
char s[maxs];
void solve(LL x, int sgn)
{
	sprintf(s, "%lld", x);
	int len = strlen(s), c[maxd] = {};
	pw10 = 1;
	for(int i = 1; i < len; ++i)
	{
		LL all = pw10 * (maxd - 1);
		if(i > 1)
			for(int j = 0; j < maxd; ++j)
				cnt[j] += sgn * all / 10 * (i - 1);
		for(int j = 1; j < maxd; ++j)
			cnt[j] += sgn * pw10;
		pw10 *= 10;
	}
	for(int i = 0; i < len; ++i)
	{
		if(s[i] > '0')
		{
			LL all = pw10 * (s[i] - (i ? '0' : '1'));
			for(int j = 0; j < maxd; ++j)
				cnt[j] += sgn * all * c[j];
			if(i + 1 < len)
				for(int j = 0; j < maxd; ++j)
					cnt[j] += sgn * all / 10 * (len - i - 1);
			for(int j = i ? 0 : 1; '0' + j < s[i]; ++j)
				cnt[j] += sgn * pw10;
		}
		pw10 /= 10;
		++c[s[i] - '0'];
	}
}
int main()
{
	LL a, b;
	scanf("%lld%lld", &a, &b);
	solve(a, -1);
	solve(b + 1, 1);
	for(int i = 0; i < maxd; ++i)
		printf("%lld\n", cnt[i]);
	return 0;
}
