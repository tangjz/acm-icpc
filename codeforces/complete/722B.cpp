#include <stdio.h>
const int maxn = 101;
const char *buf = "aeiouy";
int n, p[maxn];
char str[1 << 10];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d ", p + i);
	for(int i = 1; i <= n; ++i)
	{
		gets(str);
		for(int j = 0; str[j]; ++j)
			for(int k = 0; buf[k]; ++k)
				if(str[j] == buf[k])
				{
					--p[i];
					break;
				}
		if(p[i])
		{
			puts("NO");
			return 0;
		}
	}
	puts("YES");
	return 0;
}
