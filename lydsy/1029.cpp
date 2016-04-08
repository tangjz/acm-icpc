/*
 * 按照截止时间依次贪心处理 
 * 能做则做 
 * 不能做则使最浪费时间的最小 
 * heap维护事件即可 
 */
#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;
#define x first
#define y second
const int maxn = 150010;
int n, ans;
pair<int, int> t[maxn];
priority_queue<int> q;
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) scanf("%d%d", &t[i].y, &t[i].x);
	sort(t, t + n);
	for(int i = 0, s = 0, tmp; i < n; ++i)
		if(s + t[i].y <= t[i].x)
		{
			s += t[i].y;
			q.push(t[i].y);
			++ans;
		}
		else
		{
			tmp = q.top();
			if(t[i].y < tmp)
			{
				s += t[i].y - tmp;
				q.pop();
				q.push(t[i].y);
			}
		}
	printf("%d\n", ans);
	return 0;
}
