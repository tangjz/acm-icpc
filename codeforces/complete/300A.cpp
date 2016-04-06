#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <stack>
using namespace std;
queue<int> Q[3];
int n;
int main()
{
	int i, x;
	scanf("%d", &n);
	while(n--)
	{
		scanf("%d", &x);
		if(x < 0) Q[0].push(x);
		else if(x > 0) Q[1].push(x);
		else Q[2].push(x);
	}
	if(Q[1].empty())
	{
		x = Q[0].front(); Q[1].push(x); Q[0].pop();
		x = Q[0].front(); Q[1].push(x); Q[0].pop();
	}
	if((int)Q[0].size() % 2 == 0)
	{
		x = Q[0].front(); Q[2].push(x); Q[0].pop();
	}
	for(i = 0; i < 3; ++i)
	{
		printf("%d", (int)Q[i].size());
		while(!Q[i].empty())
		{
			printf(" %d", x = Q[i].front());
			Q[i].pop();
		}
		printf("\n");
	}
	return 0;
}
