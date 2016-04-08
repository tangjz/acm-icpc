#include <cstdio>
#include <cstring>
int tot;
char pre[27], mid[27], suf[27];
void dfs(int pl, int pr, int ml, int mr)
{
	int pos;
	for(pos = ml; pos <= mr; ++pos)
		if(mid[pos] == pre[pl])
			break;
	if(pos > ml)
		dfs(pl + 1, pl + pos - ml, ml, pos - 1);
	if(pos < mr)
		dfs(pr - mr + pos + 1, pr, pos + 1, mr);
	suf[tot++] = pre[pl];
}
int main()
{
	while(scanf("%s%s", pre, mid) == 2)
	{
		tot = 0;
		dfs(0, strlen(pre) - 1, 0, strlen(mid) - 1);
		suf[tot] = '\0';
		puts(suf);
	}
	return 0;
}