#include <vector>
#include <stdio.h>
#include <cstring>
const int maxn = 50000, maxw = 1000000000L;
int t, n, m, leaf[maxn], val[maxn], deg[maxn], pos[maxn];
int que[maxn + 1], L, R, minB[maxn], maxB[maxn];
int pL, pR, pM, S;
std::vector<int> e[maxn + 1];
bool check(int ans)
{
	for(int i = 0; i < n; ++i)
	{
		minB[i] = 1;
		maxB[i] = maxw;
	}
	for(int i = 0; i < m; ++i)
		minB[leaf[i]] = maxB[leaf[i]] = val[i];
	for(int i = 1; i <= n; ++i)
	{
		int u = que[i];
		if(minB[u] > maxB[u])
			return 0;
		int low = minB[u] - ans, high = maxB[u] + ans;
		for(std::vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
		{
			int v = *it;
			if(pos[v] <= pos[u])
				continue;
			if(minB[v] < low)
				minB[v] = low;
			if(maxB[v] > high)
				maxB[v] = high;
		}
	}
	return 1;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; ++i)
			std::vector<int>().swap(e[i]);
		for(int i = 1, u, v; i < n; ++i)
		{
			scanf("%d%d", &u, &v);
			--u;
			--v;
			e[u].push_back(v);
			e[v].push_back(u);
		}
		for(int i = 0; i < m; ++i)
		{
			scanf("%d%d", leaf + i, val + i);
			--leaf[i];
		}
		memset(deg, 0, n * sizeof(int));
		memset(pos, -1, n * sizeof(int));
		L = R = 0;
		S = n;
		std::vector<int>().swap(e[S]);
		for(int i = 0; i < m; ++i)
		{
			e[S].push_back(leaf[i]);
			++deg[leaf[i]];
		}
		que[R++] = S;
		for( ; L < R; ++L)
		{
			int u = que[L];
			for(std::vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
			{
				int v = *it;
				if(pos[v] >= 0)
					continue;
				--deg[v];
				if(!deg[v])
				{
					pos[v] = R;
					que[R++] = v;
					for(std::vector<int>::iterator jt = e[v].begin(); jt != e[v].end(); ++jt)
					{
						int v2 = *jt;
						if(pos[v2] == -1)
							++deg[v2];
					}
				}
			}
		}
		for(pL = 0, pR = maxw; pL < pR; )
		{
			pM = pL + pR >> 1;
			if(check(pM))
				pR = pM;
			else
				pL = pM + 1;
		}
		printf("%d\n", pL);
	}
	return 0;
}
