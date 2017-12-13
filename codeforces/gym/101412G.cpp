#include <bitset>
#include <cstdio>
typedef long long LL;
const int maxn = 2000, maxm = 15;
int n, m, q, r[maxn], val[maxm], dis[maxm];
std::bitset<maxn> cnt[maxm], cost;
struct Point
{
	int x, y, z;
	LL dot(const Point &t) const
	{
		return (LL)x * t.x + (LL)y * t.y + (LL)z * t.z;
	}
	inline LL mode() const
	{
		return dot(*this);
	}
	Point det(const Point &t) const
	{
		return (Point){y * t.z - z * t.y, z * t.x - x * t.z, x * t.y - y * t.x};
	}
	Point operator - (const Point &t) const
	{
		return (Point){x - t.x, y - t.y, z - t.z};
	}
} cir[maxn], lht[maxm], obj;
int sgn(int x)
{
	return (x > 0) - (x < 0);
}
int main()
{
	while(scanf("%d%d%d", &n, &m, &q) == 3 && n + m + q)
	{
		for(int i = 0; i < n; ++i)
			scanf("%d%d%d%d", &cir[i].x, &cir[i].y, &cir[i].z, r + i);
		for(int i = 0; i < m; ++i)
			scanf("%d%d%d%d", &lht[i].x, &lht[i].y, &lht[i].z, val + i);
		scanf("%d%d%d", &obj.x, &obj.y, &obj.z);
		for(int i = 0; i < n; ++i)
			cir[i] = cir[i] - obj;
		for(int i = 0; i < m; ++i)
		{
			lht[i] = lht[i] - obj;
			dis[i] = lht[i].mode();
			cnt[i].reset();
			for(int j = 0; j < n; ++j)
			{
				int sgn1 = sgn((lht[i] - cir[j]).mode() - r[j] * r[j]);
				int sgn2 = sgn(cir[j].mode() - r[j] * r[j]);
				if(sgn1 * sgn2 < 0
				|| sgn1 > 0 && sgn2 > 0 && lht[i].det(cir[j]).mode() < r[j] * r[j] * (LL)dis[i]
				&& lht[i].dot(lht[i] - cir[j]) > 0 && lht[i].dot(cir[j]) > 0)
					cnt[i].set(j);
			}
		}
		double ans = 0;
		for(int i = 0; i < 1 << m; ++i)
		{
			double value = 0;
			cost.reset();
			for(int j = 0; j < m; ++j)
				if((i >> j) & 1)
				{
					cost |= cnt[j];
					value += (double)val[j] / dis[j];
				}
			if((int)cost.count() <= q && ans < value)
				ans = value;
		}
		printf("%.10f\n", ans);
	}
	return 0;
}
