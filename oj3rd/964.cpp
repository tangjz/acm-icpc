#include <cstdio>
#include <cstring>
const int maxn = 1000010, maxm = 1000010;
int n, m, tot, lnk[maxm];
char str[maxn][11], tmp[11];
struct List
{
	unsigned long long h;
	int nxt;
} e[maxn];
unsigned long long BKDRHash(char *s)
{
	unsigned long long seed = 131, ret = 0;
	while(*s)
		ret = ret * seed + (*s++);
	return ret;
}
int main()
{
	while(scanf("%d", &n) == 1)
	{
		for(int i = 0; i < n; ++i)
		{
			scanf("%s", str[i]);
			unsigned long long hh = BKDRHash(str[i]);
			e[++tot] = (List){hh, lnk[hh % maxm]};
			lnk[hh % maxm] = tot;
		}
		scanf("%d", &m);
		while(m--)
		{
			bool flag = 0;
			scanf("%s", tmp);
			unsigned long long hh = BKDRHash(tmp);
			for(int it = lnk[hh % maxm]; it; it = e[it].nxt)
				if(e[it].h == hh)
				{
					flag = 1;
					break;
				}
			puts(flag ? "Yes" : "No");
		}
	}
	return 0;
}
