#include <queue>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 200001;
int n, m, c[maxn];
long long ans;
vector<pair<int, int> > e[maxn];
priority_queue<pair<int, int> > Q;
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		scanf("%d", c + i);
	while(m--)
	{
		int l, r, v;
		scanf("%d%d%d", &l, &r, &v);
		--l;
		--r;
		e[l].push_back(make_pair(-r, v));
	}
	for(int i = 0; i <= n; ++i)
	{
		while(!Q.empty() && -Q.top().first < i)
		{
			ans += Q.top().second;
			Q.pop();
		}
		for(vector<pair<int, int> >::iterator it = e[i].begin(); it != e[i].end(); ++it)
			Q.push(*it);
		while(!Q.empty() && c[i])
		{
			pair<int, int> now = Q.top();
			Q.pop();
			int rev = min(now.second, c[i]);
			now.second -= rev;
			c[i] -= rev;
			if(now.second)
				Q.push(now);
		}
	}
	printf("%I64d\n", ans);
	return 0;
}
