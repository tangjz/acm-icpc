/*
 * 将矩阵乘法的式子分解后合并发现是前缀和
 */
#include <cstdio>
const int BUFSIZE = 1000000;
char buf[BUFSIZE], *pt = buf + BUFSIZE, *pend = buf + BUFSIZE;
inline void read() { if (pt >= pend) pt = buf, fread(buf, 1, BUFSIZE, stdin); }
inline void scan(int &t) { t = 0; read(); bool nega = 0; while(!(((*pt) >= '0' && (*pt) <= '9') || (*pt == '-'))) ++pt, read(); if((*pt) == '-') nega = 1, ++pt, read(); while(((*pt) >= '0' && (*pt) <= '9')) t = (t << 3) + (t << 1) + (*(pt++)) - '0', read(); if (nega) t = -t; }
template<typename _> inline void swap(_& x, _& y) { const _ t(x); x = y; y = t; }
int n, m, x[2001][2001], y[2001][2001];
int main()
{
	int i, j, a, b, c, d;
	scan(n); scan(m);
	for(i = 1; i <= n; ++i)
		for(j = 1; j <= n; ++j) scan(x[i][j]), x[i][j] += x[i - 1][j];
	for(i = 1; i <= n; ++i)
		for(j = 1; j <= n; ++j) scan(y[i][j]), y[i][j] += y[i][j - 1];
	while(m--)
	{
		scan(a); scan(b); scan(c); scan(d);
		if(a > c) swap(a, c);
		if(b > d) swap(b, d);
		long long ans(0);
		for(i = 1; i <= n; ++i) ans += (long long)(x[c][i] - x[a - 1][i]) * (y[i][d] - y[i][b - 1]);
		printf("%lld\n", ans);
	}
}
