#include <queue>
#include <stdio.h>
#include <algorithm>
const int maxn = 101, INF = 0x3f3f3f3f;
int t, n, a[maxn][3], busy[3], tim[3], total;
std::priority_queue<int> Q[3];
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		for(int i = 0; i < 3; ++i)
		{
			tim[i] = 0;
			busy[i] = -1;
			for( ; !Q[i].empty(); Q[i].pop());
		}
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
		{
			bool fir = 0;
			for(int j = 0; j < 3; ++j)
			{
				scanf("%d", a[i] + j);
				if(!fir && a[i][j])
				{
					fir = 1;
					Q[j].push(-i);
				}
			}
		}
		for(int i = 0; i < 3; ++i)
			if(!Q[i].empty())
			{
				busy[i] = -Q[i].top();
				Q[i].pop();
				tim[i] = a[busy[i]][i];
			}
		total = 0;
		while(1)
		{
			int mx = INF;
			for(int i = 0; i < 3; ++i)
				if(busy[i] >= 0 && mx > tim[i])
					mx = tim[i];
			if(mx == INF)
				break;
			total += mx;
			for(int i = 2; i >= 0; --i)
			{
				if(busy[i] < 0 || (tim[i] -= mx) > 0)
					continue;
				for(int k = i + 1; k < 3; ++k)
					if(a[busy[i]][k])
					{
						if(busy[k] < 0)
						{
							busy[k] = busy[i];
							tim[k] = a[busy[k]][k];
						}
						else
							Q[k].push(-busy[i]);
						break;
					}
				if(!Q[i].empty())
				{
					busy[i] = -Q[i].top();
					Q[i].pop();
					tim[i] = a[busy[i]][i];
				}
				else
					busy[i] = -1;
			}
		}
		printf("Case #%d: %d\n", Case, total);
	}
	return 0;
}
