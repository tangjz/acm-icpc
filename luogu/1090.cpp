#include <queue>
#include <cstdio>
using namespace std;
priority_queue<int, vector<int>, greater<int> > Q;
int n, ans;
int main()
{
	int i, val;
	scanf("%d", &n);
	for(i = 0; i < n; ++i) { scanf("%d", &val); Q.push(val); }
	for(i = 1; i < n; ++i)
	{
		val = Q.top(); Q.pop();
		val += Q.top(); Q.pop();
		ans += val; Q.push(val);
	}
	printf("%d\n", ans);
	return 0;
}
