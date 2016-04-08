#include <cstdio>
const int maxn = 110;
int t, n, pos, que[maxn], l, r, now, cnt[11], ans;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &pos);
		l = 0, r = n, now = 1, ans = 0;
		for(int i = 1; i <= 9; ++i)
			cnt[i] = 0;
		for(int i = 0; i < n; ++i)
		{
			scanf("%d", que + i);
			if(now < que[i])
				now = que[i];
			++cnt[que[i]];
		}
		while(l != r)
			if(que[l] == now)
			{
				++ans;
				if(l == pos)
					break;
				--cnt[que[l++]];
				if(l >= maxn)
					l -= maxn;
				while(now && !cnt[now])
					--now;
			}
			else
			{
				if(l == pos)
					pos = r;
				que[r++] = que[l++];
				if(l >= maxn)
					l -= maxn;
				if(r >= maxn)
					r -= maxn;
			}
		printf("%d\n", ans);
	}
	return 0;
}