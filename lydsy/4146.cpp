#include <cstdio>
const int maxn = 2000001;
typedef long long LL;
int n, x, cnt[maxn];
LL ans;
void scan(int &x)
{
	int ch;
	while((ch = getchar()) < '0' || ch > '9');
	x = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + (ch - '0');
}
int main()
{
	scan(n);
	while(n--)
	{
		scan(x);
		++cnt[x];
	}
	for(int i = 1; i < maxn; ++i)
	{
		if(!cnt[i])
			continue;
		ans += (LL)cnt[i] * (cnt[i] - 1);
		for(int j = i + i; j < maxn; j += i)
			ans += (LL)cnt[i] * cnt[j];
	}
	printf("%lld\n", ans);
	return 0;
}
