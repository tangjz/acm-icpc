#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100010;
int n, m, tot, seq[maxn], ans;
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		tot = ans = 0;
		for(int i = 0; i < n; ++i)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			if(u < v)
				seq[tot++] = v - u;
			else if(u == v)
			{
				++ans;
				if(m)
				{
					--m;
					ans += 2;
				}
			}
			else
				ans += 3;
		}
		sort(seq, seq + tot);
		for(int i = 0; i < tot; ++i)
			if(seq[i] <= m)
			{
				m -= seq[i];
				++ans;
				if(m)
				{
					--m;
					ans += 2;
				}
			}
			else
				break;
		printf("%d\n", ans);
	}
	return 0;
}
