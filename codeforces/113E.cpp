#include <cstdio>
typedef long long LL;
const int maxn = 21;
inline int div10(int x, int k)
{
	for( ; k > 0; --k, x /= 10);
	return x;
}
LL solve(int hh, int mm, int min, int dig)
{
	LL ret = (LL)hh * div10(min - 1, dig - 1) + div10(mm, dig - 1);
	static char buf[maxn];
	sprintf(buf, "%d", min - 1);
	for(int i = 0; buf[i]; ++i)
		dig -= buf[i] != '0';
	return (ret += div10(hh, dig - 1));
}
int main()
{
	int hh, mm, n, h1, m1, h2, m2;
	scanf("%d%d%d%d%d%d%d", &hh, &mm, &n, &h1, &m1, &h2, &m2);
	LL ans = solve(h2, m2, mm, n) - solve(h1, m1, mm, n);
	if(h2 < h1 || (h2 == h1 && m2 < m1))
	{
		ans += solve(hh - 1, mm - 1, mm, n);
		static char buf[maxn];
		sprintf(buf, "%d", hh - 1);
		for(int i = 0; buf[i]; ++i)
			n -= buf[i] != '0';
		sprintf(buf, "%d", mm - 1);
		for(int i = 0; buf[i]; ++i)
			n -= buf[i] != '0';
		ans += n <= 0;
	}
	printf("%I64d\n", ans);
	return 0;
}
