#include <cstdio>
const int maxn = 100001, maxd = 26;
int cnt[maxd], mx, sz, len;
char str[maxn], stk[maxn], out[maxn];
int main()
{
	scanf("%s", str);
	for(int i = 0; str[i]; ++i)
		++cnt[str[i] - 'a'];
	for(mx = 0; mx < maxd && !cnt[mx]; ++mx);
	for(int i = 0; str[i]; ++i)
	{
		for( ; sz && stk[sz - 1] <= 'a' + mx; out[len++] = stk[--sz]);
		stk[sz++] = str[i];
		for(--cnt[str[i] - 'a']; mx < maxd && !cnt[mx]; ++mx);
	}
	for( ; sz; out[len++] = stk[--sz]);
	out[len] = '\0';
	puts(out);
	return 0;
}
