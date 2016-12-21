#include <map>
#include <stdio.h>
#include <cassert>
#include <algorithm>
using namespace std;
const int maxn = 100001;
int t, n, q, b[maxn], tot, que[maxn], fir[maxn], sz[maxn];
pair<int, int> a[maxn];
int main()
{
	assert(scanf("%d", &t) == 1 && 1 <= t && t <= 20);
	for(int Case = 1; Case <= t; ++Case)
	{
		assert(scanf("%d%d", &n, &q) == 2 && 1 <= n && n < maxn && 1 <= q && q < maxn);
		for(int i = 1; i <= n; ++i)
		{
			assert(scanf("%d", &a[i].first) == 1 && 1 <= a[i].first && a[i].first <= 1000000000);
			a[i].second = i;
		}
		sort(a + 1, a + n + 1);
		tot = 0;
		for(int i = 1; i <= n; ++i)
		{
			if(a[i - 1].first != a[i].first)
			{
				que[++tot] = a[i].first;
				fir[tot] = i;
				sz[tot] = 0;
			}
			++sz[tot];
		}
		for(int i = 1; i <= n; ++i)
			assert(scanf("%d", b + i) == 1 && 1 <= b[i] && b[i] <= n);
		map<pair<int, int>, int> Hash;
		printf("Case #%d:\n", Case);
		while(q--)
		{
			int x, y;
			assert(scanf("%d%d", &x, &y) == 2 && 1 <= x && x <= 1000000000 && 1 <= y && y <= n);
			pair<int, int> state = make_pair(x, y);
			if(Hash.count(state))
			{
				printf("%d\n", Hash[state]);
				continue;
			}
			int idx = lower_bound(que + 1, que + tot + 1, x) - que, ans = 0;
			if(idx <= tot && que[idx] == x && y <= sz[idx])
			{
				int cid = 0, cnt = 0;
				while(1)
				{
					int nid = cnt + y <= sz[idx] ? a[fir[idx] + cnt + y - 1].second : n + 1, dt = y;
					int L = cnt + y, R = sz[idx];
					while(L < R)
					{
						int M = (L + R) >> 1;
						if(a[fir[idx] + M - 1].second - (cnt ? a[fir[idx] + cnt - 1].second : 0) < b[y])
							L = M + 1;
						else
							R = M;
					}
					if(L <= sz[idx] && a[fir[idx] + L - 1].second - (cnt ? a[fir[idx] + cnt - 1].second : 0) >= b[y])
					{
						nid = a[fir[idx] + L - 1].second;
						dt = L - cnt;
					}
					else
						nid = n + 1;
					if(nid > n)
					{
						if(cid < n)
							++ans;
						break;
					}
					cid = nid;
					cnt += dt;
					++ans;
				}
			}
			else
				++ans;
			printf("%d\n", Hash[state] = ans);
		}
	}
	return 0;
}
