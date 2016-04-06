#include <cstdio>
#include <cstring>
int t, n;
char op[2], str[10][11];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		memset(str, ' ', sizeof str);
		scanf("%s%d", op, &n);
		for(int i = 0; i < n; ++i)
		{
			str[i][0] = op[0];
			if(++op[0] > 'z')
				op[0] -= 26;
		}
		for(int i = 1; i < n - 1; ++i)
		{
			str[i][i] = op[0];
			if(++op[0] > 'z')
				op[0] -= 26;
		}
		for(int i = 0; i < n; ++i)
		{
			str[i][n - 1] = op[0];
			str[i][n] = '\0';
			puts(str[i]);
			if(++op[0] > 'z')
				op[0] -= 26;
		}
	}
	return 0;
}
