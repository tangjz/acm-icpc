#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100010;
int t, n;
long long ans;
priority_queue<int, vector<int>, greater<int> > Q;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		ans = 0;
		while(!Q.empty())
			Q.pop();
		scanf("%d", &n);
		while(n--)
		{
			int x;
			scanf("%d", &x);
			Q.push(x);
		}
		while(!Q.empty())
		{
			int x = Q.top();
			Q.pop();
			if(Q.empty())
				break;
			x += Q.top();
			Q.pop();
			ans += x;
			Q.push(x);
		}
		printf("%I64d\n", ans);
	}
	return 0;
}
