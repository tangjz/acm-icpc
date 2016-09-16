#include <cstdio>
const int maxn = 101;
int n, m;
char str[maxn];
int main()
{
	scanf("%d%d", &n, &m);
	if((n * n >> 1) + (n & 1) < m)
	{
		puts("NO");
		return 0;
	}
	puts("YES");
	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < n; ++j)
			if(m && !((i + j) & 1))
			{
				str[j] = 'L';
				--m;
			}
			else
				str[j] = 'S';
		str[n] = '\0';
		puts(str);
	}
	return 0;
}
