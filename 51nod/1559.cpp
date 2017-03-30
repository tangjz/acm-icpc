#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxq = 200001, maxs = 262144 | 1;
int n, m, k, q, seg[maxs];
bool ans[maxq];
struct Point
{
	int x, y;
	bool operator < (const Point &t) const
	{
		return x < t.x;
	}
} rook[maxq];
struct Query
{
	int id, x1, y1, x2, y2;
	bool operator < (const Query &t) const
	{
		return x2 < t.x2;
	}
} query[maxq];
void upd(int o, int L, int R, int x, int val)
{
	if(L == R)
	{
		seg[o] = val;
		return;
	}
	int M = L + R >> 1;
	if(x <= M)
		upd(o + o, L, M, x, val);
	else
		upd(o + o + 1, M + 1, R, x, val);
	seg[o] = min(seg[o + o], seg[o + o + 1]);
}
int que(int o, int L, int R, int l, int r)
{
	if(l <= L && R <= r)
		return seg[o];
	int M = L + R >> 1;
	if(r <= M)
		return que(o + o, L, M, l, r);
	else if(l > M)
		return que(o + o + 1, M + 1, R, l, r);
	else
		return min(que(o + o, L, M, l, r), que(o + o + 1, M + 1, R, l, r));
}
int main()
{
	scanf("%d%d%d%d", &n, &m, &k, &q);
	for(int i = 0; i < k; ++i)
		scanf("%d%d", &rook[i].x, &rook[i].y);
	sort(rook, rook + k);
	for(int i = 0; i < q; ++i)
	{
		query[i].id = i;
		scanf("%d%d%d%d", &query[i].x1, &query[i].y1, &query[i].x2, &query[i].y2);
	}
	sort(query, query + q);
	for(int i = 0, j = 0; i < q; ++i)
	{
		while(j < k && rook[j].x <= query[i].x2)
		{
			upd(1, 1, m, rook[j].y, rook[j].x);
			++j;
		}
		ans[query[i].id] |= que(1, 1, m, query[i].y1, query[i].y2) >= query[i].x1;
	}
	memset(seg, 0, sizeof seg);
	swap(n, m);
	for(int i = 0; i < k; ++i)
		swap(rook[i].x, rook[i].y);
	sort(rook, rook + k);
	for(int i = 0; i < q; ++i)
	{
		swap(query[i].x1, query[i].y1);
		swap(query[i].x2, query[i].y2);
	}
	sort(query, query + q);
	for(int i = 0, j = 0; i < q; ++i)
	{
		while(j < k && rook[j].x <= query[i].x2)
		{
			upd(1, 1, m, rook[j].y, rook[j].x);
			++j;
		}
		ans[query[i].id] |= que(1, 1, m, query[i].y1, query[i].y2) >= query[i].x1;
	}
	for(int i = 0; i < q; ++i)
		puts(ans[i] ? "YES" : "NO");
	return 0;
}
