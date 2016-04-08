#include <cstdio>
const int maxn = 1010, maxs = 31010;
int t, n, s[maxn], tot, ans;
struct Trie
{
	int cnt, ch[2];
	void clear()
	{
		cnt = ch[0] = ch[1] = 0;
	}
} e[maxs];
void change(int x, int v)
{
	int o = 0;
	for(int i = 30; i >= 0; --i)
	{
		int j = (x >> i) & 1;
		if(!e[o].ch[j])
		{
			e[o].ch[j] = tot;
			e[tot++].clear();
		}
		o = e[o].ch[j];
		e[o].cnt += v;
	}
}
int find(int x)
{
	int o = 0, ret = 0;
	for(int i = 30; i >= 0; --i)
	{
		int j = ~(x >> i) & 1;
		if(e[o].ch[j] && e[e[o].ch[j]].cnt)
		{
			o = e[o].ch[j];
			ret |= j << i;
		}
		else
		{
			o = e[o].ch[j ^= 1];
			ret |= j << i;
		}
	}
	return ret;
}
void upd(int &x, int y)
{
	if(x < y)
		x = y;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		tot = ans = 0;
		e[tot++].clear();
		for(int i = 0; i < n; ++i)
		{
			scanf("%d", s + i);
			change(s[i], 1);
		}
		for(int i = 0; i < n; ++i)
		{
			change(s[i], -1);
			for(int j = i + 1; j < n; ++j)
			{
				change(s[j], -1);
				int val = find(s[i] + s[j]);
				upd(ans, (s[i] + s[j]) ^ val);
				change(s[j], 1);
			}
			change(s[i], 1);
		}
		printf("%d\n", ans);
	}
	return 0;
}
