#include <cstdio>
#include <cstring>
const int maxn = 10010, maxm = 11, maxl = 81, mod1 = 233, mod2 = 23333, mod = 199669;
typedef unsigned long long ULL;
int n, m, tot;
char str[maxl];
ULL Hash1[maxn][maxm];
struct Node
{
	int row, nxt;
	ULL H1, H2;
} e[maxn];
int Hash[mod];
int main()
{
	while(scanf("%d%d\n", &n, &m) == 2)
	{
		for(int i = 0; i < n; ++i)
		{
			gets(str);
			for(int j = 0, k = 0; j < m && str[k]; ++j)
			{
				Hash1[i][j] = 0;
				for( ; str[k] && str[k] != ','; ++k)
					Hash1[i][j] = Hash1[i][j] * mod1 + str[k];
				if(str[k] == ',')
					++k;
			}
		}
		bool flag = 0;
		for(int j = 0; j < m; ++j)
		{
			for(int k = j + 1; k < m; ++k)
			{
				tot = 0;
				memset(Hash, 0, sizeof Hash);
				for(int i = 0; i < n; ++i)
				{
					int HH = (Hash1[i][j] * mod2 + Hash1[i][k]) % mod, res;
					for(int it = Hash[HH]; it; it = e[it].nxt)
						if(e[it].H1 == Hash1[i][j] && e[it].H2 == Hash1[i][k])
						{
							flag = 1;
							res = e[it].row;
							break;
						}
					if(flag)
					{
						puts("NO");
						printf("%d %d\n%d %d\n", res + 1, i + 1, j + 1, k + 1);
						break;
					}
					else
					{
						e[++tot] = (Node){i, Hash[HH], Hash1[i][j], Hash1[i][k]};
						Hash[HH] = tot;
					}
				}
				if(flag)
					break;
			}
			if(flag)
				break;
		}
		if(!flag)
			puts("YES");
	}
	return 0;
}