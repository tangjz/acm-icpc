#include <cstdio>
const int maxn = 10, w[maxn] = {1, 5, 10, 20, 50, 100, 200, 500, 1000, 2000}, INF = (int)2e6;
int t, p, c[maxn], sum, ans;
void upd(int &x, int y)
{
	if(x > y)
		x = y;
}
int solve(int x)
{
	if(x < 0)
		return INF;
	int cnt = 0;
	for(int i = maxn - 1; i >= 0; --i)
		if(i == 7 || i == 4)
		{
			int cc = x / w[i] >> 1;
			upd(cc, c[i] >> 1);
			cnt += cc << 1;
			x -= cc * w[i] << 1;
		}
		else
		{
			int cc = x / w[i];
			upd(cc, c[i]);
			cnt += cc;
			x -= cc * w[i];
		}
	return x ? INF : cnt;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &p);
		sum = 0;
		p = -p;
		for(int i = 0; i < maxn; ++i)
		{
			scanf("%d", c + i);
			sum += c[i];
			p += c[i] * w[i];
		}
		ans = solve(p);
		if(c[7])
		{
			--c[7];
			upd(ans, solve(p - w[7]) + 1);
			if(c[4])
			{
				--c[4];
				upd(ans, solve(p - w[7] - w[4]) + 2);
				++c[4];
			}
			++c[7];
		}
		if(c[4])
		{
			--c[4];
			upd(ans, solve(p - w[4]) + 1);
			++c[4];
		}
		if(ans == INF)
			puts("-1");
		else
			printf("%d\n", sum - ans);
	}
	return 0;
}
