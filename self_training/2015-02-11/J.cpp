#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
const int maxk = 751;
int k, a[maxk], b[maxk], c[maxk], id[maxk];
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > Q;
int main()
{
	while(scanf("%d", &k) != EOF)
	{
		for(int i = 0; i < k; ++i)
			scanf("%d", a + i);
		sort(a, a + k);
		for(int i = 1; i < k; ++i)
		{
			for(int j = 0; j < k; ++j)
				scanf("%d", b + j);
			sort(b, b + k);
			for(int j = 0; j < k; ++j)
				Q.push(make_pair(a[j] + b[id[j] = 0], j));
			for(int j = 0; j < k; ++j)
			{
				c[j] = Q.top().first;
				int s = Q.top().second;
				Q.pop();
				Q.push(make_pair(a[s] + b[++id[s]], s));
			}
			for(int j = 0; j < k; ++j)
				a[j] = c[j];
			while(!Q.empty())
				Q.pop();
		}
		for(int i = 0; i < k; ++i)
			printf("%d%c", a[i], " \n"[i == k - 1]);
	}
	return 0;
}
