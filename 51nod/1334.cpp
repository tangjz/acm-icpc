#include <stdio.h>
#include <algorithm>
typedef long long LL;
const int maxw = 3001;
int Gcd[maxw][maxw], t, w, called;
inline LL f(int r, LL x)
{
	if(r == 1 || !x)
		return x + 1;
	int g = Gcd[w][r];
	LL lim = x / (r / g), ret = 0;
	for(int b = 0; b < g && b <= lim; ++b)
	{
		LL a = (lim - b) / g;
		int dt = b * (w / g) + 1;
		ret += f(dt, a);
	}
	return ret;
}
int main()
{
	for(int i = 1; i < maxw; ++i)
		for(int j = 1; j < i; ++j)
			Gcd[i][j] = std::__gcd(i, j);
	scanf("%d", &t);
	while(t--)
	{
		LL L, R, ans = 0;
		scanf("%lld%lld%d", &L, &R, &w);
		called = 0;
		for(int i = 1; i < w && i <= R; ++i)
			ans += f(i, (R - i) / w) - (i < L ? f(i, (L - 1 - i) / w) : 0);
		printf("%lld\n", ans);
	}
	return 0;
}
