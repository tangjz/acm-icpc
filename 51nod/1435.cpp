#include <cstdio>
const int maxs = 16, maxn = 10;
const int tot = 4, prime[tot] = {2, 3, 5, 7}, last[maxn] = {0, 1, 2, 3, 2, 5, 2, 7, 2, 3};
int n, cnt[maxn];
char str[maxs];
int main()
{
	scanf("%d%s", &n, str);
	for(int i = 0; i < n; ++i)
		++cnt[str[i] - '0'];
	for(int i = maxn - 2; i >= 2; --i)
		cnt[i] += cnt[i + 1];
	for(int i = maxn - 1; i >= 2; --i)
		if(i != last[i])
		{
			cnt[last[i]] += cnt[i];
			cnt[i / last[i]] += cnt[i];
		}
		else
		{
			for(int j = 0; j < cnt[i]; ++j)
				putchar('0' + i);
			for(int j = 2; j <= i; ++j)
				cnt[j] -= cnt[i];
		}
	putchar('\n');
	return 0;
}
