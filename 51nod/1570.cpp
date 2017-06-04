#include <cstdio>
#include <cstring>
typedef long long LL;
const int maxn = 4, maxs = 501, mod = 1000000007, maxd = 1 << maxn, maxm = 1 << maxd;
inline void mod_inc(int &x, int y)
{
	if((x += y) >= mod)
		x -= mod;
}
inline void mod_dec(int &x, int y)
{
	if((x -= y) < 0)
		x += mod;
}
int qtot;
struct Node {
	int way[maxm | 1];
} que[maxs >> 2 | 1], x, y, z;
char str[maxs], *ptr = str;
int expression()
{
	if(*ptr != '(')
	{
		int cID;
		if(*ptr == '?')
			cID = maxn << 1;
		else if(*ptr >= 'A' && *ptr <= 'D')
			cID = *ptr - 'A';
		else
			cID = maxn + *ptr - 'a';
		++ptr;
		return cID;
	}
	++ptr; // '('
	int LID = expression();
	++ptr; // ')'
	char op = *(ptr++);
	++ptr; // '('
	int RID = expression();
	++ptr; // ')'
	int cID = qtot++;
	if(op == '&' || op == '?') // and
	{
		memcpy(x.way, que[LID].way, maxm * sizeof(int));
		for(int i = 0; i < maxd; ++i)
			for(int j = maxm - 1; j >= 0; --j)
				if(j & (1 << i))
					mod_inc(x.way[j ^ (1 << i)], x.way[j]);
		memcpy(y.way, que[RID].way, maxm * sizeof(int));
		for(int i = 0; i < maxd; ++i)
			for(int j = maxm - 1; j >= 0; --j)
				if(j & (1 << i))
					mod_inc(y.way[j ^ (1 << i)], y.way[j]);
		for(int i = 0; i < maxm; ++i)
			z.way[i] = (LL)x.way[i] * y.way[i] % mod;
		for(int i = 0; i < maxd; ++i)
			for(int j = maxm - 1; j >= 0; --j)
				if(j & (1 << i))
					mod_dec(z.way[j ^ (1 << i)], z.way[j]);
		for(int i = 0; i < maxm; ++i)
			mod_inc(que[cID].way[i], z.way[i]);
	}
	if(op == '|' || op == '?') // or
	{
		memcpy(x.way, que[LID].way, maxm * sizeof(int));
		for(int i = 0; i < maxd; ++i)
			for(int j = 0; j < maxm; ++j)
				if(j & (1 << i))
					mod_inc(x.way[j], x.way[j ^ (1 << i)]);
		memcpy(y.way, que[RID].way, maxm * sizeof(int));
		for(int i = 0; i < maxd; ++i)
			for(int j = 0; j < maxm; ++j)
				if(j & (1 << i))
					mod_inc(y.way[j], y.way[j ^ (1 << i)]);
		for(int i = 0; i < maxm; ++i)
			z.way[i] = (LL)x.way[i] * y.way[i] % mod;
		for(int i = 0; i < maxd; ++i)
			for(int j = 0; j < maxm; ++j)
				if(j & (1 << i))
					mod_dec(z.way[j], z.way[j ^ (1 << i)]);
		for(int i = 0; i < maxm; ++i)
			mod_inc(que[cID].way[i], z.way[i]);
	}
	return cID;
}
int n, expID, digit[maxd], ways;
void dfs(int dep, int mask)
{
	if(dep == maxd)
	{
		mod_inc(ways, que[expID].way[mask]);
		return;
	}
	if(digit[dep] == -1)
	{
		dfs(dep + 1, mask);
		dfs(dep + 1, mask | (1 << dep));
	}
	else
		dfs(dep + 1, mask | (digit[dep] << dep));
}
int main()
{
	scanf("%s%d", str, &n);
	memset(digit, -1, maxd * sizeof(int));
	while(n--)
	{
		int dig = 0;
		for(int i = 0; i < maxn; ++i)
		{
			int x;
			scanf("%d", &x);
			dig |= x << i;
		}
		int v;
		scanf("%d", &v);
		digit[dig] = v;
	}
	qtot = maxn << 1 | 1;
	for(int i = 0; i < maxn; ++i)
	{
		{ // ? = 'A' + i
			int mask = 0;
			for(int j = 0; j < maxd; ++j)
				if(j & (1 << i))
					mask |= 1 << j;
			++que[i].way[mask];
			++que[maxn << 1].way[mask];
		}
		{ // ? = 'a' + i
			int mask = 0;
			for(int j = 0; j < maxd; ++j)
				if(~j & (1 << i))
					mask |= 1 << j;
			++que[maxn + i].way[mask];
			++que[maxn << 1].way[mask];
		}
	}
	expID = expression();
	dfs(0, 0);
	printf("%d\n", ways);
	return 0;
}
