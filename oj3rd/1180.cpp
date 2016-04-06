#include <cstdio>
int k, first;
char str[21][21];
int main()
{
	while(scanf("%d", &k) == 1)
	{
		if(first)
			putchar('\n');
		else
			first = 1;
		for(int i = 0; i < k - i; ++i)
		{
			for(int j = i; j < k - i; ++j)
				str[i][j] = str[k - i - 1][j] = i & 1 ? '#' : '*';
			for(int j = i + 1; j < k - i - 1; ++j)
				str[j][i] = str[j][k - i - 1] = i & 1 ? '#' : '*';
		}
		for(int i = 0; i < k; ++i)
		{
			str[i][k] = '\0';
			puts(str[i]);
		}
	}
	return 0;
}
