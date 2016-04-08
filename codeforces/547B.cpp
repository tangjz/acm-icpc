#include <map>
#include <set>
#include <list>
#include <queue>
#include <deque>
//#include <stack>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 200010, mod = 1000000007;
int n, a[maxn], l[maxn], r[maxn], stack[maxn], pos[maxn], top, id[maxn], ans[maxn], last;
bool cmp(const int &x, const int &y)
{
	return a[x] < a[y];
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", &a[i]);
		id[i] = i;
	}
	top = 0;
	for(int i = 1; i <= n; ++i)
	{
		while(top && stack[top - 1] >= a[i])
			--top;
		if(top)
			l[i] = pos[top - 1] + 1;
		else
			l[i] = 1;
		stack[top] = a[i];
		pos[top++] = i;
	}
	top = 0;
	for(int i = n; i >= 1; --i)
	{
		while(top && stack[top - 1] >= a[i])
			--top;
		if(top)
			r[i] = pos[top - 1] - 1;
		else
			r[i] = n;
		stack[top] = a[i];
		pos[top++] = i;
	}
	sort(id + 1, id + n + 1, cmp);
	for(int i = n; i >= 1; --i)
	{
		int len = r[id[i]] - l[id[i]] + 1, &w = a[id[i]];
		//printf("%d : %d %d \n", id[i], l[id[i]], r[id[i]]);
		for(int j = len; j > last; --j)
			ans[j] = w;
		last = max(last, len);
	}
	for(int i = 1; i <= n; ++i)
		printf("%d%c", ans[i], " \n"[i == n]);
	return 0;
}
