#include <cmath>
#include <stdio.h>
#include <cstring>
const int maxn = 2000001;
const double pi = acos(-1.0), ans_inf = pi * pi / 6;
int len, n;
double f[maxn];
char str[maxn];
int main()
{
	for(int i = 1; i < maxn; ++i)
		f[i] = f[i - 1] + 1.0 / i / i;
	while(scanf("%s", str) == 1)
	{
		len = strlen(str);
		if(len > 7)
		{
			printf("%.5f\n", ans_inf);
			continue;
		}
		sscanf(str, "%d", &n);
		printf("%.5f\n", n < maxn ? f[n] : ans_inf);
	}
	return 0;
}
