#include <cstdio>
const int maxn = 10010, INF = 0x3f3f3f3f, oper[4][4] = {
{ 1,  2,  3,  4},
{ 2, -1,  4, -3},
{ 3, -4, -1,  2},
{ 4,  3, -2, -1}};
int t, n, pre[maxn][4], suf[maxn][4];
long long m;
char str[maxn];
int trans(char ch)
{
	if(ch == 'i')
		return 2;
	if(ch == 'j')
		return 3;
	if(ch == 'k')
		return 4;
}
int op(int x, int y)
{
	int sgn = 0;
	if(x < 0)
	{
		x = -x;
		sgn ^= 1;
	}
	if(y < 0)
	{
		y = -y;
		sgn ^= 1;
	}
	return sgn ? -oper[x - 1][y - 1] : oper[x - 1][y - 1];
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d%I64d%s", &n, &m, str);
		pre[0][0] = 1;
		for(int i = 1; i <= n; ++i)
			pre[i][0] = op(pre[i - 1][0], trans(str[i - 1]));
		for(int k = 1; k < 4; ++k)
		{
			pre[0][k] = pre[n][k - 1];
			for(int i = 1; i <= n; ++i)
				pre[i][k] = op(pre[i - 1][k], trans(str[i - 1]));
		}
		if(pre[n][(m - 1) % 4] != -1)
		{
			printf("Case #%d: NO\n", Case);
			continue;
		}
		suf[0][0] = 1;
		for(int i = 1; i <= n; ++i)
			suf[i][0] = op(trans(str[n - i]), suf[i - 1][0]);
		for(int k = 1; k < 4; ++k)
		{
			suf[0][k] = suf[n][k - 1];
			for(int i = 1; i <= n; ++i)
				suf[i][k] = op(trans(str[n - i]), suf[i - 1][k]);
		}
		int ilen = INF, klen = INF;
		for(int i = 1; i <= n * 4; ++i)
			if(pre[(i - 1) % n + 1][(i - 1) / n] == trans('i'))
			{
				ilen = i;
				break;
			}
		for(int k = 1; k <= n * 4; ++k)
			if(suf[(k - 1) % n + 1][(k - 1) / n] == trans('k'))
			{
				klen = k;
				break;
			}
		if(ilen != INF && klen != INF && ilen + klen <= n * m)
			printf("Case #%d: YES\n", Case);
		else
			printf("Case #%d: NO\n", Case);
	}
	return 0;
}
