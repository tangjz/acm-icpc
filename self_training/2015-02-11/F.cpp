#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
int n, k, size;
priority_queue<int, vector<int>, greater<int> > Q;
int main()
{
	while(scanf("%d%d", &n, &k) == 2)
	{
		while(!Q.empty())
			Q.pop();
		size = 0;
		while(n--)
		{
			int x;
			char op[2];
			scanf("%s", op);
			if(op[0] == 'I')
			{
				scanf("%d", &x);
				if(size < k)
				{
					Q.push(x);
					++size;
				}
				else if(Q.top() < x)
				{
					Q.pop();
					Q.push(x);
				}
			}
			else
				printf("%d\n", Q.top());
		}
	}
	return 0;
}
