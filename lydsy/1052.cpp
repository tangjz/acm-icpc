#include <cstdio>
#include <cstring>
const int maxn = 20001, INF = 0x3f3f3f3f;
int n, x[maxn], y[maxn], tag[maxn];
bool dfs(int dep, int d)
{
	if(dep == 4)
	{
		for(int i = 0; i < n; ++i)
			if(!tag[i])
				return 0;
		return 1;
	}
	int x1 = INF, y1 = INF, x2 = -INF, y2 = -INF; 
	for(int i = 0; i < n; ++i)
		if(!tag[i])
		{
			if(x1 > x[i])
				x1 = x[i];
			if(y1 > y[i])
				y1 = y[i];
			if(x2 < x[i])
				x2 = x[i];
			if(y2 < y[i])
				y2 = y[i];
		}
	for(int i = 0; i < n; ++i)
		if(!tag[i] && x[i] - x1 <= d && y[i] - y1 <= d)
			tag[i] = dep;
	if(dfs(dep + 1, d))
		return 1;
	for(int i = 0; i < n; ++i)
		if(tag[i] == dep)
			tag[i] = 0;
	for(int i = 0; i < n; ++i)
		if(!tag[i] && x[i] - x1 <= d && y2 - y[i] <= d)
			tag[i] = dep;
	if(dfs(dep + 1, d))
		return 1;
	for(int i = 0; i < n; ++i)
		if(tag[i] == dep)
			tag[i] = 0;
	for(int i = 0; i < n; ++i)
		if(!tag[i] && x2 - x[i] <= d && y[i] - y1 <= d)
			tag[i] = dep;
	if(dfs(dep + 1, d))
		return 1;
	for(int i = 0; i < n; ++i)
		if(tag[i] == dep)
			tag[i] = 0;
	for(int i = 0; i < n; ++i)
		if(!tag[i] && x2 - x[i] <= d && y2 - y[i] <= d)
			tag[i] = dep;
	if(dfs(dep + 1, d))
		return 1;
	for(int i = 0; i < n; ++i)
		if(tag[i] == dep)
			tag[i] = 0;
	return 0;
}
bool check(int d)
{
	memset(tag, 0, sizeof tag);
	return dfs(1, d);
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d%d", x + i, y + i);
	int L = 0, R = 2e9 + 1, M;
	while(L < R)
	{
		M = L + (R - L >> 1);
		if(check(M))
			R = M;
		else
			L = M + 1;
	}
	printf("%d\n", L);
	return 0;
} 
