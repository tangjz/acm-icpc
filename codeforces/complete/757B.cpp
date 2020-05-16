#include <stdio.h>
const int maxn = 100001;
int n, mx, s[maxn], ans;
int main()
{
	scanf("%d", &n);
	for(int i = 1, x; i <= n; ++i)
	{
		scanf("%d", &x);
		if(mx < x)
			mx = x;
		++s[x];
	}
	for(int i = 1; i <= mx; ++i)
		for(int j = i + i; j <= mx; j += i)
			s[i] += s[j];
	for(int i = 2; i <= mx; ++i)
		if(ans < s[i])
			ans = s[i];
	if(ans == 0)
		ans = 1;
	printf("%d\n", ans);
	return 0;
}

