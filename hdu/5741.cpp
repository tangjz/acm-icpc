#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 1001, maxm = 500001;
int t, n, m, x[maxn], totE, totY, que[maxm * 3], bit[maxm * 3];
struct Event
{
	int x, L, R, typ;
	bool operator < (const Event &t) const
	{
		return x < t.x || (x == t.x && typ < t.typ);
	}
	bool operator == (const Event &t) const
	{
		return x == t.x && L == t.L && R == t.R && typ == t.typ;
	}
} e[maxm * 3];
char ans[maxm];
void add(int x, int v)
{
	for( ; x <= totY; x += x & -x)
		bit[x] += v;
}
int sum(int x)
{
	int ret = 0;
	for( ; x > 0; x -= x & -x)
		ret += bit[x];
	return ret;
}
void addSqr(int x1, int x2, int y1, int y2)
{
	e[totE++] = (Event){x1, y1, y2 + 1, 1};
	e[totE++] = (Event){x2 + 1, y1, y2 + 1, -1};
	que[totY++] = y1;
	que[totY++] = y2 + 1;
	//printf("sqr [%d, %d] * [%d, %d]\n", x1, x2, y1, y2);
}
void addPoi(int id, int x, int y)
{
	e[totE++] = (Event){x, y, id, 2};
	//printf("poi %d %d\n", x, y);
	que[totY++] = y;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		totE = totY = 0;
		scanf("%d%d",  &n, &m);
		for(int i = 0; i < n; ++i)
			scanf("%d", x + i);
		if(n == 1)
			addSqr(0, x[0], 0, 0);
		for(int i = 0; i < n; ++i)
		{
			int cX = 0, cY = 0;
			for(int j = i + 1; j < n; ++j)
			{
				int xL = cX, xR = cX, yL = cY, yR = cY;
				(i & 1 ? yR : xR) += x[i];
				(j & 1 ? yR : xR) += x[j];
				addSqr(xL, xR, yL, yR);
				(j & 1 ? cY : cX) += x[j];
			}
		}
		for(int i = 0; i < m; ++i)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			addPoi(i, x, y);
			ans[i] = '0';
		}
		ans[m] = '\0';
		sort(e, e + totE);
		//totE = unique(e, e + totE) - e;
		sort(que, que + totY);
		totY = unique(que, que + totY) - que;
		memset(bit + 1, 0, n * sizeof(int));
		for(int i = 0; i < totE; ++i)
			if(e[i].typ < 2)
			{
				e[i].L = lower_bound(que, que + totY, e[i].L) - que + 1;
				e[i].R = lower_bound(que, que + totY, e[i].R) - que + 1;
				//printf("%s [%d, %d)\n", e[i].typ > 0 ? "insert" : "remove", que[e[i].L - 1], que[e[i].R - 1]);
				add(e[i].L, e[i].typ);
				add(e[i].R, -e[i].typ);
			}
			else
			{
				e[i].L = lower_bound(que, que + totY, e[i].L) - que + 1;
				int val = sum(e[i].L);
				//printf("query %d : %d\n", que[e[i].L - 1], val);
				if(val > 0)
					ans[e[i].R] = '1';
			}
		puts(ans);
	}
	return 0;
}
