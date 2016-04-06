#include <cstdio>
int n, m;
char str[51];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < m; ++j)
			if(!(i & 1) || ((i >> 1) & 1) && !j || !((i >> 1) & 1) && j == m - 1)
				str[j] = '#';
			else
				str[j] = '.';
		puts(str);
	}
	return 0;
}
