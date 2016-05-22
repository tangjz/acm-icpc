#include <stdio.h>
const int maxn = 100000, maxs = 30, maxd = 26, maxo = maxn * maxs + 10;
int nxt[maxo][maxd];
int n, tot, fa[maxo], val[maxo], tag[maxo];
char typ[maxs + 1], str[maxs + 1];
int main()
{
	scanf("%d", &n);
	++tot;
	while(n--)
	{
		scanf("%s%s", typ, str);
		if(typ[0] == 'i')
		{
			int o = 0;
			for(int i = 0; str[i]; ++i)
			{
				str[i] -= 'a';
				if(!nxt[o][str[i]])
				{
					fa[tot] = o;
					nxt[o][str[i]] = tot++;
				}
				o = nxt[o][str[i]];
				if(tag[o])
				{
					for(int j = 0; j < maxd; ++j)
					{
						val[nxt[o][j]] = 0;
						tag[nxt[o][j]] = 1;
					}
					tag[o] = 0;
				}
			}
			for( ; o > 0; o = fa[o])
				++val[o];
		}
		else if(typ[0] == 'd')
		{
			int o = 0;
			for(int i = 0; str[i]; ++i)
			{
				str[i] -= 'a';
				if(!nxt[o][str[i]])
				{
					o = 0;
					break;
				}
				o = nxt[o][str[i]];
				if(tag[o])
				{
					for(int j = 0; j < maxd; ++j)
					{
						val[nxt[o][j]] = 0;
						tag[nxt[o][j]] = 1;
					}
					tag[o] = 0;
				}
			}
			tag[o] = 1;
			for(int tmp = val[o]; o > 0; o = fa[o])
				val[o] -= tmp;
		}
		else
		{
			int o = 0;
			for(int i = 0; str[i]; ++i)
			{
				str[i] -= 'a';
				if(!nxt[o][str[i]])
				{
					o = 0;
					break;
				}
				o = nxt[o][str[i]];
				if(tag[o])
				{
					for(int j = 0; j < maxd; ++j)
					{
						val[nxt[o][j]] = 0;
						tag[nxt[o][j]] = 1;
					}
					tag[o] = 0;
				}
			}
			puts(val[o] ? "Yes" : "No");
		}
	}
	return 0;
}
