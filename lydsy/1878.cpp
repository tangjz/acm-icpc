/*
 * 没有修改所以将询问按左端点排序转化为离线
 * 记录每点后继 询问越过某点后修改后继的权值
 * 剩下的就是区间求和了
 */
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 50010, maxm = 200000, maxv = 1000010;
int n, m, num[maxn], bit[maxn], nxt[maxn], pos[maxv], ans[maxm];
struct Node
{
	int l, r, id;
	bool operator < (const Node &x) const
	{ return l == x.l ? r < x.r : l < x.l; }
} que[maxm];
void add(int x, int val) { for( ; x <= n; x += x & -x) bit[x] += val; }
int sum(int x) { int cnt = 0; for( ; x; x -= x & -x) cnt += bit[x]; return cnt; }
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d", &num[i]);
	for(int i = n; i; --i) nxt[i] = pos[num[i]], pos[num[i]] = i;
	for(int i = 0; i < maxv; ++i) if(pos[i]) add(pos[i], 1);
	scanf("%d", &m);
	for(int i = 0; i < m; ++i) scanf("%d%d", &que[i].l, &que[i].r), que[i].id = i;
	sort(que, que + m);
	for(int i = 0, s = 1; i < m; ++i)
	{
		for( ; s < que[i].l; ++s) if(nxt[s]) add(nxt[s], 1);
		ans[que[i].id] = sum(que[i].r) - sum(que[i].l - 1);
	}
	for(int i = 0; i < m; ++i) printf("%d\n", ans[i]);
	return 0;
}
