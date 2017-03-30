#include <stdio.h>
const int maxn = 15;
int n, f[maxn], d[maxn], c[maxn], m;
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
bool check()
{
	for(int i = 0; i < n; ++i)
		for(int j = i + 1; j < n; ++j)
		{
			int k = (d[i] - d[j]) % m, b = f[j] - f[i], x, y, r;
			if(k < 0)
				k += m;
			r = exgcd(k, m, x, y);
			if(b % r)
				continue;
			x = x * b % m / r;
			if(x < 0)
				x += m / r;
			if(x <= c[i] && x <= c[j])
				return 0;
		}
	return 1;
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d%d%d", f + i, d + i, c + i);
		if(m < f[i])
			m = f[i];
	}
	for( ; !check(); ++m);
	printf("%d\n", m);
	return 0;
}
