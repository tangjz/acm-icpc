#include <set>
#include <stdio.h>
#include <cstring>
#include <algorithm>
const int maxn = 100001;
int t, n, h[maxn << 1], pre[maxn], suf[maxn], tot, lnk[maxn << 1];
char str[maxn], buf[maxn << 1];
std::set<int> sp;
struct Edge
{
	int nxt, v;
} e[maxn << 1];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%s", str);
		n = strlen(str);
		for(int i = 0; i < n; ++i)
		{
			buf[i << 1] = str[i];
			buf[i << 1 | 1] = '#';
		}
		buf[n - 1 << 1 | 1] = '\0';
		for(int i = 0, mx = 0, id = 0; i <= n - 1 << 1; ++i)
		{
			h[i] = i < mx ? std::min(mx - i, h[(id << 1) - i]) : 0;
			for( ; h[i] <= i && buf[i - h[i]] == buf[i + h[i]]; ++h[i]);
			if(mx < i + h[i])
			{
				mx = i + h[i];
				id = i;
			}
		}
		std::set<int>().swap(sp);
		tot = 0;
		memset(lnk, -1, (n << 1) * sizeof(int));
		for(int i = 0; i <= n - 1 << 1; ++i)
		{
			sp.insert(i);
			e[tot] = (Edge){lnk[i + h[i]], i};
			lnk[i + h[i]] = tot++;
			for(int it = lnk[i]; it != -1; it = e[it].nxt)
				sp.erase(e[it].v);
			if(~i & 1)
			{
				pre[i >> 1] = i - *sp.begin() + 1;
				if((i >> 1) && pre[i >> 1] < pre[(i >> 1) - 1])
					pre[i >> 1] = pre[(i >> 1) - 1];
			}
		}
		std::set<int>().swap(sp);
		tot = 0;
		memset(lnk, -1, (n << 1) * sizeof(int));
		for(int i = n - 1 << 1; i >= 0; --i)
		{
			sp.insert(i);
			e[tot] = (Edge){lnk[i - h[i]], i};
			lnk[i - h[i]] = tot++;
			for(int it = lnk[i]; it != -1; it = e[it].nxt)
				sp.erase(e[it].v);
			if(~i & 1)
			{
				suf[i >> 1] = *sp.rbegin() - i + 1;
				if((i >> 1) + 1 < n && suf[i >> 1] < suf[(i >> 1) + 1])
					suf[i >> 1] = suf[(i >> 1) + 1];
			}
		}
		int ans = 0;
		for(int i = 1; i < n; ++i)
			if(ans < pre[i - 1] + suf[i])
				ans = pre[i - 1] + suf[i];
		printf("%d\n", ans);
	}
	return 0;
}
