#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, x, ans;
priority_queue<int> Q;
int main()
{
	while(scanf("%d", &n) == 1)
	{
		ans = 0;
		for(int i = 0; i < n; ++i)
		{
			scanf("%d", &x);
			Q.push(-x);
		}
		for(int i = 1; i < n; ++i)
		{
			x = Q.top();
			Q.pop();
			ans -= x += Q.top();
			Q.pop();
			Q.push(x);
		}
		Q.pop();
		printf("%d\n", ans);
	}
	return 0;
}
