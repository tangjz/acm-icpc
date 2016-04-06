#include <map>
#include <set>
#include <list>
#include <stack>
#include <queue>
#include <cmath>
#include <string>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
const double eps = 1e-10;
int n, l, x[1010], b[1010], p[1010];
bool vis[1010];
double f[1010], L, R, M;
bool judge()
{
	for(int i = 1; i <= n; ++i)
	{
		f[i] = sqrt(abs(x[i] - l));
		p[i] = 0;
		for(int j = 1; j < i; ++j)
			if(f[i] > f[j] + sqrt(abs(x[i] - x[j] - l)))
			{
				f[i] = f[j] + sqrt(abs(x[i] - x[j] - l));
				p[i] = j;
			}
		f[i] -= M * b[i];
	}
	return f[n] >= 0;
}
int main()
{
	scanf("%d%d", &n, &l);
	for(int i = 1; i <= n; ++i)
		scanf("%d%d", x + i, b + i);
	for(M = 1; judge(); M *= 2);
	L = (int)M / 2;
	R = M;
	while(R - L >= eps)
	{
		M = (L + R) / 2;
		if(judge())
			L = M;
		else
			R = M;
	}
	stack<int> s;
	for(int i = n; i; i = p[i])
		s.push(i);
	while(!s.empty())
	{
		printf("%d ", s.top());
		s.pop();
	}
	putchar('\n');
	return 0;
}
