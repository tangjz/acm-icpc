#include <stdio.h>
#include <cstring>
#include <algorithm>
const int maxn = 1000001;
int n, z[maxn];
char str[maxn];
int main()
{
	scanf("%s", str);
	n = strlen(str);
	for(int i = 0, L = 0, R = 1; i < n; ++i)
	{
		if(i < R && z[i - L] < R - i)
		{
			z[i] = z[i - L];
			continue;
		}
		int x = std::max(i, R);
		for( ; x < n && str[x] == str[x - i]; ++x);
		z[i] = x - i;
		if(i < x)
		{
			L = i;
			R = x;
		}
	}
	z[0] = n;
	long long ans = 0;
	for(int i = 0; i < n; ++i)
		ans += z[i];
	printf("%lld\n", ans);
	return 0;
}
