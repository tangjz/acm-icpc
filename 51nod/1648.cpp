#include <stdio.h>
const int maxn = 100009;
struct Node
{
	int fa, ch[2], size;
} t[maxn];
int n, m, tot, p[maxn];
void maintain(int o)
{
	if(!o)
		return;
	t[o].size = t[t[o].ch[0]].size + t[t[o].ch[1]].size + 1;
}
void setch(int o, int f, int oo)
{
	t[o].ch[f] = oo;
	t[oo].fa = o;
	maintain(o);
}
bool isroot(int o)
{
	return !t[o].fa || t[t[o].fa].ch[0] != o && t[t[o].fa].ch[1] != o;
}
void rotate(int o)
{
	int d = t[t[o].fa].ch[1] == o, oo = t[o].fa;
	setch(oo, d, t[o].ch[d ^ 1]);
	if(isroot(t[o].fa))
	{
		t[o].fa = t[t[o].fa].fa;
		setch(o, d ^ 1, oo);
	}
	else
	{
		setch(t[t[o].fa].fa, t[t[t[o].fa].fa].ch[1] == t[o].fa, o);
		setch(o, d ^ 1, oo);
		maintain(t[o].fa);
	}
}
void splay(int o)
{
	while(!isroot(o))
	{
		if(!isroot(t[o].fa))
		{
			int d1 = t[t[o].fa].ch[1] == o, d2 = t[t[t[o].fa].fa].ch[1] == t[o].fa;
			if(d1 == d2)
				rotate(t[o].fa);
			else
				rotate(o);
		}
		rotate(o);
	}
}
void access(int o)
{
	int oo = o, ooo = 0;
	while(oo)
	{
		splay(oo);
		setch(oo, 1, ooo);
		ooo = oo;
		oo = t[oo].fa;
	}
	splay(o);
}
void add(int &o)
{
	o = ++tot;
	t[o].size = 1;
}
int last(int o)
{
	for(int cnt = 2; cnt; )
		if(t[t[o].ch[0]].size + 1 == cnt)
			return o;
		else if(cnt <= t[t[o].ch[0]].size)
			o = t[o].ch[0];
		else
		{
			cnt -= t[t[o].ch[0]].size + 1;
			o = t[o].ch[1];
		}
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n + 1; ++i)
		add(p[i]);
	for(int i = 1, x; i <= n; ++i)
	{
		scanf("%d", &x);
		x += i;
		if(x > n + 1)
			x = n + 1;
		t[p[i]].fa = p[x];
	}
	while(m--)
	{
		int typ, x, y;
		scanf("%d%d", &typ, &x);
		if(!typ)
		{
			scanf("%d", &y);
			y += x;
			if(y > n + 1)
				y = n + 1;
			splay(p[x]);
			t[t[p[x]].ch[0]].fa = t[p[x]].fa;
			setch(p[x], 0, 0);
			t[p[x]].fa = p[y];
		}
		else
		{
			access(p[x]);
			printf("%d %d\n", last(p[x]), t[p[x]].size - 1);
		}
	}
	return 0;
}
