#include <cctype>
#include <stdio.h>
const int maxs = 101, maxd = 26;
int n;
bool vis[maxd];
char str[maxs];
int main()
{
	scanf("%d%s", &n, str);
	for(int i = 0; i < n; ++i)
		vis[tolower(str[i]) - 'a'] = 1;
	for(int i = 0; i < maxd; ++i)
		if(!vis[i])
		{
			puts("NO");
			return 0;
		}
	puts("YES");
	return 0;
}
