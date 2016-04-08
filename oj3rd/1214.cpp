#include <cstdio>
const int maxn = 1010;
int nxt[maxn];
char s[maxn];
int main()
{
	while(scanf("%s", s) == 1)
	{
		nxt[0] = nxt[1] = 0;
		for(int i = 1; s[i]; ++i)
		{
			int j = nxt[i];
			while(j && s[i] != s[j])
				j = nxt[j];
			nxt[i + 1] = s[i] == s[j] ? j + 1 : 0;
		}
		printf("-1");
		for(int i = 1; s[i]; ++i)
			printf(" %d", nxt[i]);
		putchar('\n');
	}
	return 0;
}
