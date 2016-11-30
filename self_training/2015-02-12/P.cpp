#include <cstdio>
#include <cstring>
const int maxs = 101;
char a[maxs], c[maxs];
int b, d, alen, clen, cnt[maxs], nxt[maxs], sum;
int main()
{
	scanf("%d%d%s%s", &b, &d, a, c);
	alen = strlen(a);
	clen = strlen(c);
	for(int i = 0; i < clen; ++i)
	{
		int now = i;
		for(int j = 0; j < alen; ++j)
			if(c[now] == a[j])
			{
				++now;
				if(now >= clen)
				{
					++cnt[i];
					now = 0;
				}
			}
		nxt[i] = now;
	}
	for(int i = 0, now = 0; i < b; ++i, now = nxt[now])
		sum += cnt[now];
	printf("%d\n", sum / d);
	return 0;
}
