#include <cstdio>
const int maxn = 1000010;
int t, n, m, x[maxn], que[maxn], l, r;
long long s[maxn], ans;
char str[maxn];
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d%d%s", &n, &m, str + 1);
		x[0] = 0;
		for(int i = 1; i <= n; ++i)
			x[i] = x[i - 1] + (str[i] == '_' ? 0 : (str[i] == '/' ? 1 : -1));
		for(int i = n; i >= 1; --i)
			x[i] += x[i - 1];
		s[0] = 0;
		for(int i = 1; i <= n; ++i)
			s[i] = s[i - 1] + x[i];
		ans = 0x3f3f3f3f3f3f3f3fLL;
		l = r = 0;
		for(int i = 1; i < m; ++i)
		{
			while(l < r && x[que[r - 1]] >= x[i])
				--r;
			que[r++] = i;
		}
		for(int i = m; i <= n; ++i)
		{
			while(l < r && x[que[r - 1]] >= x[i])
				--r;
			que[r++] = i;
			int now = x[que[l]];
			if(now & 1)
				--now;
			if(ans > s[i] - s[i - m] - (long long)now * m)
				ans = s[i] - s[i - m] - (long long)now * m;
			if(que[l] == i - m + 1)
				++l;
		}
		printf("Case #%d: %lld.%d\n", Case, ans >> 1, (ans & 1) ? 5 : 0);
	}
	return 0;
}
