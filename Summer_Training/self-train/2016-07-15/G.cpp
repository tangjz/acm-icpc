#include <cstdio>
#include <algorithm>
typedef long long LL;
const int maxn = 2001;
int n, m, tot, ans;
struct Point
{
	int x, y;
	LL dot(const Point &t) const
	{
		return (LL)x * t.x + (LL)y * t.y;
	}
	LL det(const Point &t) const
	{
		return (LL)x * t.y - (LL)y * t.x;
	}
	LL mode2() const
	{
		return dot(*this);
	}
	bool operator < (const Point &t) const
	{
		if(!y && !t.y && (LL)x * t.x <= 0)
			return x > t.x;
		if(!y && x >= 0 && t.y != 0)
			return 1;
		if(!t.y && t.x >= 0 && y != 0)
			return 0;
		if((LL)t.y * y <= 0)
			return y > t.y;
		LL tmp = det(t);
		return tmp > 0;// || tmp == 0 && mode2() < t.mode2();
	}
	bool operator == (const Point &t) const
	{
		return det(t) == 0 && dot(t) > 0;
	}
	Point operator + (const Point &t) const
	{
		return (Point){x + t.x, y + t.y};
	}
	Point operator - (const Point &t) const
	{
		return (Point){x - t.x, y - t.y};
	}
} O = (Point){0, 0};
struct Node
{
	Point p;
	int typ, val;
	bool operator < (const Node &t) const
	{
		return p < t.p || p == t.p && (typ < t.typ || typ == t.typ && val < t.val);
	}
} a[maxn], b[maxn << 3];
int main()
{
	while(scanf("%d%d", &n, &m) == 2 && n + m)
	{
		ans = 0;
		for(int i = 0; i < n; ++i)
		{
			scanf("%d%d%d", &a[i].p.x, &a[i].p.y, &a[i].val);
			a[i].typ = 1;
			ans += a[i].val;
		}
		for(int i = 0; i < m; ++i)
		{
			scanf("%d%d%d", &a[n + i].p.x, &a[n + i].p.y, &a[n + i].val);
			a[n + i].typ = 0;
			ans += a[n + i].val;
		}
		n += m;
		for(int i = 0; i < n; ++i)
		{
			tot = 0;
			for(int j = 0; j < n; ++j)
			{
				if(i == j)
					continue;
				Point tmp = a[j].p - a[i].p;
				b[tot++] = (Node){tmp, a[j].typ, a[j].val};
				b[tot++] = (Node){tmp, -1, j};
				b[tot++] = (Node){O - tmp, -1, j};
			}
			std::sort(b, b + tot);
			int staL, staR, sum = 0;
			//printf("Case #%d\n", i);
			for(int j = 0; j < tot; ++j)
			{
				b[tot + j] = b[j];
				/*if(b[j].typ == -1)
					printf("vector (%d, %d)\n", b[j].p.x, b[j].p.y);
				else
					printf("%s point (%d, %d) %d\n", b[j].typ == 0 ? "Red" : "Blue", b[j].p.x, b[j].p.y, b[j].val);*/
			}
			for(staL = 0; b[staL].typ >= 0; ++staL);
			for(staR = staL + 1; b[staR].typ >= 0 || b[staL].val != b[staR].val; ++staR);
			for(int j = staL + 1; j < staL + tot; ++j)
			{
				if(b[j].typ < 0)
					continue;
				if((b[j].typ > 0) == (j < staR))
					sum += b[j].val;
			}
			//printf("push (%d, %d) %d\n", b[staR].p.x, b[staR].p.y, sum);
			if(ans > sum)
				ans = sum;
			for(int j = 1; j < n - 1 << 1; ++j)
			{
				for(++staL; b[staL].typ >= 0; ++staL)
					if(b[staL].typ == 1)
						sum -= b[staL].val;
					else
						sum += b[staL].val;
				for(++staR; b[staR].typ >= 0; ++staR)
					if(b[staR].typ == 1)
						sum += b[staR].val;
					else
						sum -= b[staR].val;
				//printf("push (%d, %d) %d\n", b[staR].p.x, b[staR].p.y, sum);
				if(ans > sum)
					ans = sum;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
