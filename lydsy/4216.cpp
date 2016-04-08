#include <cstdio>
typedef long long LL;
const int maxn = 500050;
int n, m, t, a[maxn];
LL s[maxn >> 4], ans;
template<class T> void scan(T& x)
{
	int ch, flag;
	while(((ch = getchar()) < '0' || ch > '9') && ch != '-');
	flag = ch == '-';
	x = flag ? 0 : ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + (ch - '0');
	if(flag)
		x = -x;
}
template<class T> void print(T x)
{
	int len = 0, num[20];
	for( ; x; x /= 10)
		num[len++] = x % 10;
	if(!len)
		num[len++] = 0;
	while(len)
		putchar('0' + num[--len]);
	putchar('\n');
}
int main()
{
	scan(n), scan(m), scan(t);
	for(int i = 1; i <= n; ++i)
	{
		scan(a[i]);
		s[i >> 4] += a[i];
	}
	for(int i = 1; i <= n >> 4; ++i)
		s[i] += s[i - 1];
	while(m--)
	{
		int l, r;
		scan(l), scan(r);
		if(t)
		{
			l = (l ^ ans) % n + 1;
			r = (r ^ ans) % n + 1;
			if(l > r)
			{
				l = l + r;
				r = l - r;
				l = l - r;
			}
		}
		ans = s[r >> 4] - s[l - 1 >> 4];
		for(int i = 0, j = (r >> 4) << 4; i < 1 << 4; ++i, ++j)
			if(j > r)
				ans -= a[j];
		for(int i = 0, j = (l - 1 >> 4) << 4; i < 1 << 4; ++i, ++j)
			if(j >= l)
				ans += a[j];
		if(ans < 0)
		{
			putchar('-');
			ans = -ans;
		}
		print(ans);
	}
	return 0;
} 
