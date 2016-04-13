#include <queue>
#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn = 100001;
int n, l[maxn], r[maxn];
long long a[maxn], ans;
priority_queue<pair<long long, int> > Q;
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", a + i);
		Q.push({a[i], i});
		l[i] = i ? i - 1 : n - 1;
		r[i] = i + 1 < n ? i + 1 : 0;
	}
	for(int i = 0, cnt = 0; i < n && cnt < n / 3; ++i)
	{
		pair<int, int> tmp = Q.top();
		Q.pop();
		if(l[r[tmp.second]] == tmp.second)
		{
			++cnt;
			ans += tmp.first;
			int L = l[tmp.second];
			int R = r[tmp.second];
			a[tmp.second] = a[L] + a[R] - a[tmp.second];
			l[tmp.second] = l[L];
			r[tmp.second] = r[R];
			l[r[R]] = r[l[L]] = tmp.second;
			Q.push({a[tmp.second], tmp.second});
		}
	}
	printf("%lld\n", ans);
	return 0;
}
