#include <bitset>
#include <cstdio>
const int maxn = 501, maxm = 2000001, maxs = 256, maxd = 63;
int n, flag;
char str[maxm];
std::bitset<maxn> f, g[maxs];
int main()
{
	gets(str);
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		int c;
		static char tmp[maxd];
		scanf("%d%s", &c, tmp);
		for(int j = 0; j < c; ++j)
			g[(size_t)tmp[j]].set(i);
	}
	for(int i = 0; str[i]; ++i)
	{
		f.set(0);
		f = (f << 1) & g[(size_t)str[i]];
		if(f.test(n))
		{
			flag = 1;
			printf("%d\n", i - n + 2);
		}
	}
	if(!flag)
		puts("NULL");
	return 0;
}
