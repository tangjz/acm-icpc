/*
 * 因为k也被xor了所以可以数一行出现的数的个数从而算出上次是否连通...
 * 最后一次可以暴力算
 */
#include <cstdio>
const int maxn = 100001, maxm = 500001, maxk = 16;
int n, m, q, g[maxm][2], cnt, t, tt[maxk], fa[maxn];
bool vis[maxm];
char ch;
inline int getint()
{
	while((ch = getchar()) < '0' || ch > '9');
	t = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		t = (t << 3) + (t << 1) + ch - '0';
	return t;
}
inline int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
int main()
{
	int k, kk;
	n = getint(), m = getint();
	for(int i = 1; i <= m; ++i)
		g[i][0] = getint(), g[i][1] = getint();
	q = getint();
	k = getint();
	for(int i = 0; i < k; ++i)
	{
		while((ch = getchar()) < '0' || ch > '9');
		while((ch = getchar()) >= '0' && ch <= '9');
	}
	for(int i = 2; i < q; ++i)
	{
		k = getint();
		kk = 0;
		while(ch != '\n')
		{
			while(((ch = getchar()) < '0' || ch > '9') && ch != '\n');
			if(ch == '\n') break;
			while((ch = getchar()) >= '0' && ch <= '9');
			++kk;
		}
		k ^= kk;
		puts(k > cnt ? "Connected" : "Disconnected");
		cnt = k;
	}
	k = getint();
	kk = 0;
	while(ch != '\n')
	{
		while(((ch = getchar()) < '0' || ch > '9') && ch != '\n');
		if(ch == '\n') break;
		t = ch - '0';
		while((ch = getchar()) >= '0' && ch <= '9')
			t = (t << 3) + (t << 1) + ch - '0';
		tt[kk++] = t;
	}
	k ^= kk;
	puts(k > cnt ? "Connected" : "Disconnected");
	cnt = k;
	for(int i = 0; i < kk; ++i)
		vis[tt[i] ^ cnt] = 1;
	for(int i = 1; i <= n; ++i)
		fa[i] = i;
	for(int i = 1; i <= m; ++i)
		if(!vis[i]) fa[find(g[i][0])] = find(g[i][1]);
	for(int i = 2, fa1 = find(1); i <= n; ++i)
		if(find(i) != fa1)
		{
			puts("Disconnected");
			return 0;
		}
	puts("Connected");
	return 0;
}
