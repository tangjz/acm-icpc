#include <cstdio>
typedef long long LL;
const int maxn = 200010, base = 960991, mod1 = 1000173169, mod2 = (1 << 20) - 1;
int n, a[maxn], tot, tt, tm[mod2 + 1], lnk[mod2 + 1], pw[maxn], pre[maxn], suf[maxn], ans, out[maxn];
struct Hash
{
	int nxt, val;
} e[maxn];
bool insert(int val)
{
	int pos = val & mod2;
	if(tm[pos] < tt)
	{
		tm[pos] = tt;
		lnk[pos] = 0;
	}
	for(int it = lnk[pos]; it; it = e[it].nxt)
		if(e[it].val == val)
			return 0;
	e[++tot] = (Hash){lnk[pos], val};
	lnk[pos] = tot;
	return 1;
}
int main()
{
	scanf("%d", &n);
	pw[0] = 1;
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", a + i);
		pre[i] = ((LL)pre[i - 1] * base + a[i]) % mod1;
		pw[i] = (LL)pw[i - 1] * base % mod1;
	}
	for(int i = n; i; --i)
		suf[i] = ((LL)suf[i + 1] * base + a[i]) % mod1;
	for(int i = 1; i <= n; ++i)
	{
		int cnt = 0;
		++tt;
		tot = 0;
		for(int j = i; j <= n; j += i)
		{
			int val1 = pre[j] - (LL)pre[j - i] * pw[i] % mod1, val2 = suf[j - i + 1] - (LL)suf[j + 1] * pw[i] % mod1;
			if(val1 < 0)
				val1 += mod1;
			if(val2 < 0)
				val2 += mod1;
			if(insert(val1 < val2 ? val1 : val2))
				++cnt;
		}
		if(ans > cnt)
			continue;
		if(ans < cnt)
		{
			ans = cnt;
			out[0] = 0;
		}
		out[++out[0]] = i;
	}
	printf("%d %d\n", ans, out[0]);
	for(int i = 1; i <= out[0]; ++i)
		printf("%d%c", out[i], " \n"[i == out[0]]);
	return 0;
}
