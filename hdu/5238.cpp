#include <cstdio>
const int maxn = 65536, mod[4] = {7, 13, 17, 19};
int t, n, m, seg[maxn << 1][4][19], mod_pow[4][19][19];
int exgcd(int a, int b, int &x, int &y)
{
	if(!b)
	{
		x = 1;
		y = 0;
		return a;
	}
	int r = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return r;
}
//x = a1 + m1 * t1
//x = a2 + m2 * t2 
//m1 * t1 - m2 * t2 = a2 - a1
//x = a1 + m1 * t1 = a1 + m1 * t10 + m1 * m2 / gcd(m1, m2)
int CRT(int a[], const int m[], int len)
{
	int res = 0, mod = 1;
	for(int i = 0; i < len; ++i)
	{
		int x, y, r;
		r = exgcd(mod, m[i], x, y);
		x = (a[i] - res) / r * x % (m[i] / r);
		if(x < 0)
			x += (m[i] / r);
		res += mod * x;
		mod *= m[i] / r;
	}
	return res;
}
int calc(int x, char op, int y, int id)
{
	if(op == '+')
		return (x + y) % mod[id];
	if(op == '*')
		return x * y % mod[id];
	y %= mod[id] - 1;
	return mod_pow[id][x][y];
}
void build(int o, int l, int r)
{
	if(l == r)
	{
		int x;
		char op, str[20];
		scanf("%s", str);
		sscanf(str, "%c%d", &op, &x);
		for(int i = 0; i < 4; ++i)
			for(int j = 0; j < mod[i]; ++j)
				seg[o][i][j] = calc(j, op, x, i);
		return;
	}
	int m = l + r >> 1;
	build(o + o, l, m);
	build(o + o + 1, m + 1, r);
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < mod[i]; ++j)
			seg[o][i][j] = seg[o + o + 1][i][seg[o + o][i][j]];
}
void rebuild(int o, int l, int r, int x)
{
	if(l == r)
	{
		int x;
		char op, str[20];
		scanf("%s", str);
		sscanf(str, "%c%d", &op, &x);
		for(int i = 0; i < 4; ++i)
			for(int j = 0; j < mod[i]; ++j)
				seg[o][i][j] = calc(j, op, x, i);
		return;
	}
	int m = l + r >> 1;
	if(x <= m)
		rebuild(o + o, l, m, x);
	else
		rebuild(o + o + 1, m + 1, r, x);
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < mod[i]; ++j)
			seg[o][i][j] = seg[o + o + 1][i][seg[o + o][i][j]];
}
int main()
{
	for(int i = 0; i < 4; ++i)
		for(int j = 1; j < mod[i]; ++j)
		{
			mod_pow[i][j][0] = 1;
			for(int k = 1; k < mod[i] - 1; ++k)
				mod_pow[i][j][k] = mod_pow[i][j][k - 1] * j % mod[i];
		}
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d%d", &n, &m);
		printf("Case #%d:\n", Case);
		build(1, 1, n);
		for(int i = 1, x, y; i <= m; ++i)
		{
			scanf("%d%d", &x, &y);
			if(x == 1)
			{
				int res[4] = {seg[1][0][y % mod[0]], seg[1][1][y % mod[1]], seg[1][2][y % mod[2]], seg[1][3][y % mod[3]]};
				printf("%d\n", CRT(res, mod, 4));
			}
			else
				rebuild(1, 1, n, y);
		}
	}
	return 0;
}
