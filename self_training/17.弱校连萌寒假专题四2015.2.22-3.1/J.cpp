#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100002;
int n, a[maxn], b[maxn], ans;
priority_queue<pair<int, int> > Q;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	sort(a + 1, a + n + 1);
	for(int i = 1, cnt = 0; i <= n + 1; ++i)
		if(a[i] != a[i - 1])
		{
			if(cnt > 0)
				Q.push(make_pair(cnt, a[i - 1]));
			cnt = 1;
		}
		else
			++cnt;
	while(1)
	{
		pair<int, int> tmp[3];
		bool flag = 0;
		for(int i = 0; i < 3; ++i)
		{
			if(Q.empty())
			{
				flag = 1;
				break;
			}
			tmp[i] = Q.top();
			Q.pop();
			b[ans * 3 + i] = tmp[i].second;
			--tmp[i].first;
		}
		if(flag)
			break;
		for(int i = 0; i < 3; ++i)
			if(tmp[i].first > 0)
				Q.push(tmp[i]);
		++ans;
	}
	printf("%d\n", ans);
	for(int i = 0; i < ans; ++i)
	{
		if(b[i * 3] < b[i * 3 + 1])
			swap(b[i * 3], b[i * 3 + 1]);
		if(b[i * 3] < b[i * 3 + 2])
			swap(b[i * 3], b[i * 3 + 2]);
		if(b[i * 3 + 1] < b[i * 3 + 2])
			swap(b[i * 3 + 1], b[i * 3 + 2]);
		printf("%d %d %d\n", b[i * 3], b[i * 3 + 1], b[i * 3 + 2]);
	}
	return 0;
}
