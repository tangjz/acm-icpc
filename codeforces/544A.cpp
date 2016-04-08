#include <cstdio>
#include <cstring>
const int maxn = 101, maxs = 256;
int n, len, tot, pos[maxn];
char str[maxn];
bool vis[maxs];
int main()
{
	scanf("%d%s", &n, str);
	len = strlen(str);
	for(int i = 0; i < len; ++i)
		if(!vis[(int)str[i]])
		{
			pos[tot++] = i;
			vis[(int)str[i]] = 1;
		}
	if(tot < n)
	{
		puts("NO");
		return 0;
	}
	puts("YES");
	pos[n] = len;
	for(int i = 0; i < n; ++i)
	{
		char j = str[pos[i + 1]];
		str[pos[i + 1]] = '\0';
		puts(str + pos[i]);
		str[pos[i + 1]] = j;
	}
	return 0;
}
