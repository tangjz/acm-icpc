#include <stdio.h>
#include <algorithm>
const int maxn = 1000010;
int n, h[maxn], l[maxn], r[maxn];
long long c[maxn], ans;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", h + i);
	std::rotate(h + 1, std::max_element(h + 1, h + n + 1), h + n + 1);
	for(int i = 2; i <= n; ++i)
	{
		l[i] = i - 1;
		while(l[i] && h[i] > h[l[i]]) l[i] = l[l[i]];
		if(h[i] == h[l[i]])
		{
			c[i] = c[l[i]] + 1;
			l[i] = l[l[i]];
		}
		ans += c[i];
	}
	for(int i = n - 1; i; --i)
	{
		r[i] = i + 1;
		while(r[i] && h[i] >= h[r[i]]) r[i] = r[r[i]];
	}
	for(int i = 1; i <= n; ++i)
		if(h[i] != h[1])
		{
			ans += 2;
			if(l[i] == 1 && r[i] == 0)
				--ans;
		}
	printf("%lld\n", ans);
	return 0;
}
