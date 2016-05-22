#include <stdio.h>
#include <cstring>
#include <cassert>
typedef long long LL;
const int maxn = 1000010, maxd = 26, maxs = 41, mod = 3518261, sd1 = 31, md1 = 691041943, sd2 = 37, md2 = 1010347633;
int n, cnt[maxd], tot, lnk[mod];
struct Hash
{
	int nxt, h1, h2, cnt;
} e[maxn];
char str[maxs];
int main()
{
	scanf("%d", &n);
	++tot;
	while(n--)
	{
		scanf("%s", str);
		for(int i = 0; str[i]; ++i)
		{
			assert(str[i] >= 'A' && str[i] <= 'Z');
			++cnt[str[i] - 'A'];
		}
		int h1 = 0, h2 = 0;
		for(int i = 0; i < maxd; ++i)
			for( ; cnt[i] > 0; --cnt[i])
			{
				h1 = ((LL)h1 * sd1 + i + 1) % md1;
				h2 = ((LL)h2 * sd2 + i + 1) % md2;
			}
		int pos = ((LL)h1 << 31 | h2) % mod, it;
		for(it = lnk[pos]; it > 0; it = e[it].nxt)
			if(e[it].h1 == h1 && e[it].h2 == h2)
			{
				printf("%d\n", e[it].cnt++);
				break;
			}
		if(!it)
		{
			puts("0");
			e[tot] = (Hash){lnk[pos], h1, h2, 1};
			lnk[pos] = tot++;
		}
	}
	return 0;
}
