#include <cstdio>
int n;
char str[200];
int main()
{
	scanf("%d%s", &n, str);
	for(int i = 1; i < n; ++i)
		for(int j = 0; j < n && j + i * 4 < n; ++j)
			if(str[j] == '*' && str[j + i] == '*' && str[j + 2 * i] == '*' && str[j + 3 * i] == '*' && str[j + 4 * i] == '*')
			{
				puts("yes");
				return 0;
			}
	puts("no");
	return 0;
}
