#include <stdio.h>
const int maxn = 100001, maxs = 26;
int n, m, tot;
struct Trie
{
	int ch[maxs];
} e[maxn];
char str[maxn];
bool f[maxn], g[maxn];
int main()
{
	scanf("%d%d", &n, &m);
	++tot;
	for(int i = 0; i < n; ++i)
	{
		int rt = 0;
		scanf("%s", str);
		for(int j = 0; str[j]; ++j)
		{
			str[j] -= 'a';
			if(!e[rt].ch[(int)str[j]])
				e[rt].ch[(int)str[j]] = tot++;
			rt = e[rt].ch[(int)str[j]];
		}
	}
	for(int i = tot - 1; i >= 0; --i)
	{
		int cnt = 0;
		for(int j = 0; j < maxs; ++j)
			if(e[i].ch[j])
			{
				++cnt;
				f[i] |= !f[e[i].ch[j]];
				g[i] |= !g[e[i].ch[j]];
			}
		if(!cnt)
			g[i] = 1;
	}
	puts(f[0] && (g[0] || (m & 1)) ? "First" : "Second");
	return 0;
}
