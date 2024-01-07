#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int NMAX = 110000, EMAX = 110000, VMAX = 110000;

struct Edge
{
	int y;
	int next;
};

int N, M;
int V[VMAX], eid, indegree[NMAX];
Edge E[EMAX];
deque<int> Q;

void insert(int x, int y)
{
	E[++eid] = (Edge){y, V[x]};
	V[x] = eid;
	indegree[y] += 1;
}

bool findCycle()
{
	int i, x, left = N;
	for(i = 1;i <= N;i += 1)
	{
		if(!indegree[i])
		{
			Q.push_back(i);
			left -= 1;
		}
	}
	while(!Q.empty())
	{
		x = Q.front();
		Q.pop_front();
		for(i = V[x];i;i = E[i].next)
		{
			indegree[E[i].y] -= 1;
			if(!indegree[E[i].y])
			{
				left -= 1;
				Q.push_back(E[i].y);
			}
		}
	}
	return left > 0;
}

int main()
{
	int i, x, y;
	scanf("%d %d", &N, &M);
	for(i = 1;i <= M;i += 1)
	{
		scanf("%d %d", &x, &y);
		insert(x, y);
	}
	if(N <= 1)
		printf("-1\n");
	else if(!M)
		printf("2\n");
	else
	{
		if(findCycle())
			printf("0\n");
		else
			printf("1\n");
	}
	exit(0);
}
