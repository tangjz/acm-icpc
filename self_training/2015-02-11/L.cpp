#include <queue>
#include <cstdio>
using namespace std;
const int maxt =  1001, maxa = 1e6 + 1;
int n, pos[maxa];
queue<int> que[maxt], team;
int main()
{
	for(int Case = 1; scanf("%d", &n) != EOF && n; ++Case)
	{
		for(int i = 1, m, x; i <= n; ++i)
		{
			scanf("%d", &m);
			while(m--)
			{
				scanf("%d", &x);
				pos[x] = i;
			}
		}
		printf("Scenario #%d\n", Case);
		char op[10];
		while(scanf("%s", op) != EOF && op[0] != 'S')
			if(op[0] == 'E')
			{
				int x, it;
				scanf("%d", &x);
				if(que[it = pos[x]].empty())
					team.push(it);
				que[it].push(x);
			}
			else
			{
				int it = team.front();
				printf("%d\n", que[it].front());
				que[it].pop();
				if(que[it].empty())
					team.pop();
			}
		putchar('\n');
		while(!team.empty())
		{
			int it = team.front();
			while(!que[it].empty())
				que[it].pop();
			team.pop();
		}
	}
	return 0;
}
