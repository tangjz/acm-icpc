#include <cstdio>
#include <algorithm>
const int maxn = 1001, maxd = 26, mod = 1000000007;
int n, lim[maxd + 1];
char str[maxn + 2];
struct Info {
	int way, len, cnt;
} f[maxn];
void upd(Info &x, Info y)
{
	if((x.way += y.way) >= mod)
		x.way -= mod;
	x.len = std::max(x.len, y.len);
	x.cnt = std::min(x.cnt, y.cnt);
}
int main()
{
	scanf("%d%s", &n, str + 1);
	for(int i = 0; i < maxd; ++i)
		scanf("%d", lim + i);
	f[0] = (Info){1, 0, 0};
	for(int i = 1; i <= n; ++i)
		f[i] = (Info){0, 0, (int)(~0u >> 1)};
	for(int i = 0; i < n; ++i)
	{
		int limit = (int)(~0u >> 1);
		for(int j = 1; i + j <= n; ++j)
		{
			limit = std::min(limit, lim[str[i + j] - 'a']);
			if(j > limit)
				break;
			upd(f[i + j], (Info){f[i].way, std::max(f[i].len, j), f[i].cnt + 1});
		}
	}
	printf("%d\n%d\n%d\n", f[n].way, f[n].len, f[n].cnt);
	return 0;
}
