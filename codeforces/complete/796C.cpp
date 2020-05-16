#include <set>
#include <vector>
#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn = 300001;
int n, a[maxn], mx, cnt[2], ans;
vector<int> e[maxn];
int main()
{
	scanf("%d", &n);
	mx = (int)-2e9;
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", a + i);
		if(mx < a[i])
			mx = a[i];
	}
	for(int i = 1; i <= n; ++i)
	{
		cnt[0] += a[i] == mx;
		cnt[1] += a[i] == mx - 1;
	}
	for(int i = 1; i < n; ++i)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	if(cnt[0] == 1)
		for(int i = 1; i <= n; ++i)
		{
			if(a[i] != mx)
				continue;
			int tp = 0;
			for(vector<int>::iterator it = e[i].begin(); it != e[i].end(); ++it)
				tp += a[*it] == mx - 1;
			if(tp == cnt[1])
			{
				printf("%d\n", mx);
				return 0;
			}
		}
	for(int i = 1; i <= n; ++i)
	{
		int tp = a[i] == mx;
		for(vector<int>::iterator it = e[i].begin(); it != e[i].end(); ++it)
			tp += a[*it] == mx;
		if(tp == cnt[0])
		{
			printf("%d\n", mx + 1);
			return 0;
		}
	}
	printf("%d\n", mx + 2);
	return 0;
}
