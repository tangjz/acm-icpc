#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100010;
int t, n, x[maxn], p[maxn], m[maxn];
long long ans;
priority_queue<pair<int, int> > Q;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		ans = 0;
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
			scanf("%d%d%d", x + i, p + i, m + i);
		while(!Q.empty())
			Q.pop();
		for(int i = n; i >= 1; --i)
		{
			if(m[i])
				Q.push(make_pair(p[i], m[i]));
			while(x[i] && !Q.empty())
			{
				pair<int, int> tmp = Q.top();
				Q.pop();
				int num = min(x[i], tmp.second);
				ans += num * tmp.first;
				x[i] -= num;
				tmp.second -= num;
				if(tmp.second)
					Q.push(tmp);
			}
		}
		printf("%I64d\n", ans);
	}
	return 0;
}
