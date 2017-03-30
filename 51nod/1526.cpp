#include <stdio.h>
#include <algorithm>
const int maxs = 800001, maxd = 27;
int n, tot, ans;
struct Trie {
	int cnt[2], nxt[maxd];
} e[maxs];
char str[maxs];
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		int rt = 0;
		scanf("%s", str);
		for(int j = 0; str[j]; ++j)
		{
			int o = str[j] - 'a';
			if(!e[rt].nxt[o])
				e[rt].nxt[o] = ++tot;
			rt = e[rt].nxt[o];
			++e[rt].cnt[0];
		}
	}
	for(int i = 0; i < n; ++i)
	{
		int rt = 0;
		scanf("%s", str);
		for(int j = 0; str[j]; ++j)
		{
			int o = str[j] - 'a';
			if(!e[rt].nxt[o])
				e[rt].nxt[o] = ++tot;
			rt = e[rt].nxt[o];
			++e[rt].cnt[1];
		}
	}
	for(int i = 1; i <= tot; ++i)
		ans += std::min(e[i].cnt[0], e[i].cnt[1]);
	printf("%d\n", ans);
	return 0;
}
