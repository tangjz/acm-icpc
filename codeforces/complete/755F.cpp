#include <cstdio>
#include <cstring>
typedef unsigned long long ULL;
const int maxn = 1000001, maxs = 15627;
int n, m, sz, perm[maxn], cnt[maxn], ans1, ans2;
ULL f[maxs], g[maxs];
bool bit_test(ULL a[], int pos)
{
	return (a[pos >> 6] >> (pos & 63)) & 1;
}
void bit_shift(ULL a[], int dt, ULL b[])
{
	int dx = dt >> 6, dy = dt & 63;
	memset(b, 0, sz * sizeof(ULL));
	for(int i = 0; i + dx < sz; ++i)
	{
		b[i + dx] |= a[i] << dy;
		if(i + dx + 1 < sz && dy)
			b[i + dx + 1] |= a[i] >> ((1 << 6) - dy);
	}
}
void bit_and(ULL a[], ULL b[])
{
	for(int i = 0; i < sz; ++i)
		a[i] |= b[i];
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
		scanf("%d", perm + i);
	for(int i = 1; i <= n; ++i)
	{
		if(perm[i] == -1)
			continue;
		int val = 0;
		for(int j = i, k = perm[j]; ; j = k, k = perm[j])
		{
			perm[j] = -1;
			++val;
			if(k == i)
				break;
		}
		++cnt[val];
		if(val & 1)
			++ans2;
	}
	sz = (m >> 6) + 1;
	f[0] = 1;
	for(int i = 1; i <= n && !bit_test(f, m); ++i)
	{
		if(!cnt[i])
			continue;
		for(int j = 0, pw = 1; pw <= cnt[i] && !bit_test(f, m); ++j, pw <<= 1)
		{
			cnt[i] -= pw;
			bit_shift(f, i << j, g);
			bit_and(f, g);
		}
		if(cnt[i] && !bit_test(f, m))
		{
			bit_shift(f, i * cnt[i], g);
			bit_and(f, g);
		}
	}
	ans1 = m + !bit_test(f, m);
	if(m <= (n - ans2) >> 1)
		ans2 = m << 1;
	else if(m <= (n + ans2) >> 1)
		ans2 = m + ((n - ans2) >> 1);
	else
		ans2 = n;
	printf("%d %d\n", ans1, ans2);
	return 0;
}
