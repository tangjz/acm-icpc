#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 55;
int n, seq[maxn];
long long now[maxn], nxt[maxn], last, ans;
int main()
{
	while(scanf("%d", &n) == 1)
	{
		ans = now[0] = 0;
		last = 1;
		for(int i = 1; i <= n; ++i)
			scanf("%d", seq + i);
		sort(seq + 1, seq + n + 1);
		for(int i = n, dep = seq[n]; dep; --dep)
		{
			for( ; i >= 0 && seq[i] == dep; --i)
			{
				now[++now[0]] = last;
				ans += last;
			}
			sort(now + 1, now + now[0] + 1);
			nxt[0] = 0;
			for(int k = 1; k <= now[0]; k += 2)
				nxt[++nxt[0]] = now[k] + now[k + 1];
			last = now[now[0]];
			now[0] = nxt[0];
			for(int k = 1; k <= now[0]; ++k)
				now[k] = nxt[k];
		}
		printf("%lld\n", ans);
	}
	return 0;
}
