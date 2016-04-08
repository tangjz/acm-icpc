#include <cstdio>
const int maxn = 250001;
int n, m, tot, pre[maxn], in[maxn], out[maxn], bit[maxn << 1];
struct Edge
{
	int nxt, v;
} e[maxn];
void add(int x, int v)
{
	for( ; x <= tot; x += x & -x)
		bit[x] += v;
}
int sum(int x)
{
	int ret = 0;
	for( ; x > 0; x -= x & -x)
		ret += bit[x];
	return ret;
}
void AddEdge(int u, int v)
{
	e[++tot] = (Edge){pre[u], v};
	pre[u] = tot;
}
void dfs(int u)
{
	in[u] = ++tot;
	for(int it = pre[u]; it; it = e[it].nxt)
		dfs(e[it].v);
	out[u] = ++tot;
}
void scan(int &x)
{
	static int ch;
	while((ch = getchar()) < '0' || ch > '9');
	x = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + (ch - '0');
}
void print(int x)
{
	static int len, num[6];
	for(len = 0; x; x /= 10)
		num[len++] = x % 10;
	if(!len)
		num[len++] = 0;
	while(len)
		putchar('0' + num[--len]);
	putchar('\n');
}
int main()
{
	scan(n);
	for(int i = 1, u, v; i < n; ++i)
	{
		scan(u), scan(v);
		if(u < v)
			AddEdge(u, v);
		else
			AddEdge(v, u);
	}
	tot = 0;
	dfs(1);
	for(int i = 2; i <= n; ++i)
	{
		add(in[i], 1);
		add(out[i], -1);
	}
	scan(m);
	m += n - 1;
	while(m--)
	{
		int a, b;
		char op[2];
		scanf("%s", op), scan(a);
		if(op[0] == 'A')
		{
			scan(b);
			if(a < b)
			{
				add(in[b], -1);
				add(out[b], 1);
			}
			else
			{
				add(in[a], -1);
				add(out[a], 1);
			}
		}
		else
			print(sum(in[a]));
	}
	return 0;
}
