#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const char* direct = "^v<>";
const int maxn = 3010;
int n, tot, que[maxn], ord[maxn], pos[maxn], ans;
struct Node
{
	int x, y, dir;
	int U, D, L, R;
} e[maxn];
bool cmp_x(const int &a, const int &b)
{
	return e[a].x < e[b].x;
}
bool cmp_y(const int &a, const int &b)
{
	return e[a].y < e[b].y;
}
void del(int idx)
{
	if(e[idx].U != -1)
		e[e[idx].U].D = e[idx].D;
	if(e[idx].D != -1)
		e[e[idx].D].U = e[idx].U;
	if(e[idx].L != -1)
		e[e[idx].L].R = e[idx].R;
	if(e[idx].R != -1)
		e[e[idx].R].L = e[idx].L;
}
void reb(int idx)
{
	if(e[idx].U != -1)
		e[e[idx].U].D = idx;
	if(e[idx].D != -1)
		e[e[idx].D].U = idx;
	if(e[idx].L != -1)
		e[e[idx].L].R = idx;
	if(e[idx].R != -1)
		e[e[idx].R].L = idx;
}
inline int nxt(int idx)
{
	switch(e[idx].dir)
	{
		case 0 : return e[idx].U;
		case 1 : return e[idx].D;
		case 2 : return e[idx].L;
		case 3 : return e[idx].R;
	}
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		char ch;
		scanf("%d %d %c", &e[i].x, &e[i].y, &ch);
		for(e[i].dir = 0; direct[e[i].dir] != ch; ++e[i].dir);
		ord[i] = i;
	}
	tot = 0;
	for(int i = 0; i < n; ++i)
		que[tot++] = e[i].x;
	sort(que, que + tot);
	tot = unique(que, que + tot) - que;
	for(int i = 0; i < n; ++i)
		e[i].x = lower_bound(que, que + tot, e[i].x) - que;
	tot = 0;
	for(int i = 0; i < n; ++i)
		que[tot++] = e[i].y;
	sort(que, que + tot);
	tot = unique(que, que + tot) - que;
	for(int i = 0; i < n; ++i)
		e[i].y = lower_bound(que, que + tot, e[i].y) - que;
	sort(ord, ord + n, cmp_y);
	memset(pos, -1, sizeof pos);
	for(int i = 0; i < n; ++i)
	{
		e[ord[i]].U = pos[e[ord[i]].x];
		pos[e[ord[i]].x] = ord[i];
	}
	memset(pos, -1, sizeof pos);
	for(int i = n - 1; i >= 0; --i)
	{
		e[ord[i]].D = pos[e[ord[i]].x];
		pos[e[ord[i]].x] = ord[i];
	}
	sort(ord, ord + n, cmp_x);
	memset(pos, -1, sizeof pos);
	for(int i = 0; i < n; ++i)
	{
		e[ord[i]].L = pos[e[ord[i]].y];
		pos[e[ord[i]].y] = ord[i];
	}
	memset(pos, -1, sizeof pos);
	for(int i = n - 1; i >= 0; --i)
	{
		e[ord[i]].R = pos[e[ord[i]].y];
		pos[e[ord[i]].y] = ord[i];
	}
	//for(int i = 0; i < n; ++i)
	//	printf("%d : %d %d %d %d\n", i, e[i].U, e[i].D, e[i].L, e[i].R);
	for(int i = 0, j; i < n; ++i)
	{
		tot = 0;
		for(que[tot++] = j = i, del(j); (j = nxt(j)) != -1; que[tot++] = j, del(j));
		if(ans < tot)
			ans = tot;
		for( ; tot; reb(que[--tot]));
	}
	printf("%d\n", ans);
	return 0;
}
