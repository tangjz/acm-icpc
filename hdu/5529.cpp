#include <bitset>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 40000, maxm = 10001, maxs = 26;
int t, n, m, q, tot, que[maxm], L, R;
struct Trie
{
	int fail, ch[maxs];
	bool val;
} e[maxm];
char str[maxn + 1], tmp[maxm + 1];
bitset<maxn> f[maxn];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d%d%s", &n, &m, &q, str);
		for(int i = 0; i < n; ++i)
			f[i].reset();
		tot = 0;
		memset(e + (tot++), 0, sizeof(Trie));
		for(int i = 0; i < m; ++i)
		{
			scanf("%s", tmp);
			int o = 0;
			for(int j = 0; tmp[j]; ++j)
			{
				tmp[j] -= 'a';
				if(!e[o].ch[tmp[j]])
				{
					e[o].ch[tmp[j]] = tot;
					memset(e + (tot++), 0, sizeof(Trie));
				}
				o = e[o].ch[tmp[j]];
			}
			e[o].val = 1;
		}
		L = R = 0;
		for(int i = 0; i < maxs; ++i)
			if(e[0].ch[i])
				que[R++] = e[0].ch[i];
		while(L < R)
		{
			int &u = que[L++];
			for(int i = 0; i < maxs; ++i)
				if(e[u].ch[i])
				{
					int &v = e[u].ch[i], k = e[u].fail;
					que[R++] = v;
					while(k && !e[k].ch[i])
						k = e[k].fail;
					e[v].fail = k = e[k].ch[i];
				}
		}
		for(int i = 0; i < n; ++i)
			str[i] -= 'a';
		for(int i = 0; i < n; ++i)
		{
			int o = 0;
			for(int j = i; j < n; ++j)
			{
				if(!e[o].ch[str[j]])
					break;
				o = e[o].ch[str[j]];
				if(e[o].val)
					f[j - i][i] = 1;
			}
		}
		f[0].flip();
		for(int i = 1; i < n; ++i)
		{
			f[i] |= f[i - 1] & (f[i - 1] >> 1) | f[i];
			f[i].flip();
		}
		while(q--)
		{
			scanf("%d%d", &L, &R);
			printf("%d\n", (int)f[R - L][L - 1]);
		}
	}
	return 0;
}
