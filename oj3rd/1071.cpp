#include <cstdio>
const int maxn = 10001;
int n, f[maxn];
char str[maxn << 1];
int main()
{
	while(scanf("%d", &n) == 1)
	{
		for(int i = 0; i < n - 1; ++i)
			str[i] = ' ';
		for(int i = 1; i <= n; ++i)
		{
			f[i] = 1;
			for(int j = i - 1; j > 1; --j)
				f[j] ^= f[j - 1];
			for(int j = 1; j <= i; ++j)
			{
				str[n - i + j * 2 - 2] = f[j] ? '/' : ' ';
				str[n - i + j * 2 - 1] = f[j] ? '\\' : ' ';
			}
			str[n + i] = '\0';
			puts(str);
		}
	}
	return 0;
}
