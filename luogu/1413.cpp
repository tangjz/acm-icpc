#include <queue>
#include <vector>
#include <cstdio>
using namespace std;
priority_queue<int, vector<int>, greater<int> > Q[6];
int n, ans;
int main()
{
	scanf("%d", &n);
	while(n--)
	{
		int id, t;
		scanf("%d%d", &id, &t);
		Q[--id].push(t);
	}
	for(int i = 0; i < 6; ++i)
		while(!Q[i].empty())
		{
			int t = Q[i].top(); Q[i].pop();
			++ans;
			while(Q[i].top() < t + 60 && !Q[i].empty()) Q[i].pop();
		}
	printf("%d\n", ans);
	return 0;
}