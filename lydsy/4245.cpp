#include <cstdio>
typedef long long LL;
const int maxn = 500001;
int n, m;
LL a[maxn], ans;
bool vis[maxn];
template<class T> void scan(T& x)
{
	int ch;
	while((ch = getchar()) < '0' || ch > '9');
	x = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + (ch - '0');
}
int main()
{
	scan(n), scan(m);
	for(int i = 1; i <= n; ++i)
	{
		scan(a[i]);
		a[i] ^= a[i - 1];
	}
	for(int i = 59; i >= 0; --i)
	{
		int cnt = 0;
		for(int j = 1; j <= n; ++j)
			if(!vis[j] && !((a[j] >> i) & 1))
				++cnt;
		if(cnt >= m && !((a[n] >> i) & 1))
		{
			for(int j = 1; j <= n; ++j)
				if(!vis[j] && ((a[j] >> i) & 1))
					vis[j] = 1;
		}
		else
			ans |= 1LL << i;
	}
	printf("%lld\n", ans);
	return 0;
}
