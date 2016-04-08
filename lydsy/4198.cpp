#include <queue>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef pair<LL, int> Node;
int n, k, ans2;
LL ans1;
priority_queue<Node, vector<Node>, greater<Node> > Q;
int main()
{
	scanf("%d%d", &n, &k);
	if((n - 1) % (k - 1))
		for(int i = k - 1 - (n - 1) % (k - 1); i; --i)
			Q.push(make_pair(0, 0));
	while(n--)
	{
		LL w;
		scanf("%lld", &w);
		Q.push(make_pair(w, 0));
	}
	while(!Q.empty())
	{
		int cnt = 0;
		Node ret = make_pair(0, 0), tmp;
		for( ; cnt < k && !Q.empty(); ++cnt)
		{
			tmp = Q.top();
			ret.first += tmp.first;
			if(ret.second < tmp.second)
				ret.second = tmp.second;
			Q.pop();
		}
		if(cnt == 1)
			ans2 = ret.second;
		else
		{
			ans1 += ret.first;
			++ret.second;
			Q.push(ret);
		}
	}
	printf("%lld\n%d\n", ans1, ans2);
	return 0;
}
