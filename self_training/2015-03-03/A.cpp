#include <cmath>
#include <cstdio>
const int maxn = 31269;
unsigned int t, n, c[maxn], s[maxn];
int main()
{
	for(int i = 1; i < maxn; ++i)
	{
		c[i] = c[i - 1] + (int)log10(i) + 1;
		s[i] = s[i - 1] + c[i];
	}
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i = 1; i < maxn; ++i)
			if(s[i] >= n)
			{
				n -= s[i - 1];
				for(int j = 1; j <= i; ++j)
					if(c[j] >= n)
					{
						n -= c[j - 1];
						n = (int)log10(j) + 1 - n;
						while(n--)
							j /= 10;
						printf("%d\n", j % 10);
						break;
					}
				break;
			}
	}
	return 0;
}
