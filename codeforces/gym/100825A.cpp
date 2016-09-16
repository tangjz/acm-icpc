#include <cstdio>
#include <algorithm>
typedef long long LL;
const int maxn = 101, INF = 0x3f3f3f3f;
int n, px, py, pz;
struct Node
{
	int m, x, y, z, vx, vy, vz;
	bool operator < (const Node &t) const
	{
		if(x != t.x)
			return x < t.x;
		if(y != t.y)
			return y < t.y;
		return z < t.z;
	}
} a[maxn];
bool cmp(const Node &a, const Node &b)
{
	return a.m > b.m || (a.m == b.m && a < b);
}
int exgcd(int a, int b, int &x, int &y)
{
	if(!b)
	{
		x = 1;
		y = 0;
		return a;
	}
	int r = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return r;
}
bool CRT(int &r1, int &m1, int r2, int m2)
{
	int x, y, g = exgcd(m1, m2, x, y);
	if((r2 - r1) % g != 0)
		return 0;
	x = (r2 - r1) * (LL)x % m2;
	if(x < 0)
		x += m2;
	x /= g;
	r1 += m1 * x;
	m1 *= m2 / g;
	return 1;
}
int main()
{
	while(scanf("%d%d%d%d", &n, &px, &py, &pz) == 4)
	{
		for(int i = 0; i < n; ++i)
			scanf("%d%d%d%d%d%d%d", &a[i].m, &a[i].x, &a[i].y, &a[i].z, &a[i].vx, &a[i].vy, &a[i].vz);
		while(1)
		{
			int tim = INF;
			for(int i = 0; i < n; ++i)
				for(int j = i + 1; j < n; ++j)
				{
					int res = 0, mod = 1, val, tx, ty, r;
					if((val = (a[i].vx - a[j].vx) % px) < 0)
						val += px;
					if(val)
					{
						if(std::__gcd(std::abs(a[j].x - a[i].x), px) % (r = exgcd(val, px, tx, ty)) != 0)
							continue;
						if((val = ((LL)tx * (a[j].x - a[i].x) % px) / r) < 0)
							val += px;
						if(!CRT(res, mod, val, px / r))
							continue;
					}
					else if((a[j].x - a[i].x) % px != 0)
						continue;
					if((val = (a[i].vy - a[j].vy) % py) < 0)
						val += py;
					if(val)
					{
						if(std::__gcd(std::abs(a[j].y - a[i].y), py) % (r = exgcd(val, py, tx, ty)) != 0)
							continue;
						if((val = ((LL)tx * (a[j].y - a[i].y) % py) / r) < 0)
							val += py;
						if(!CRT(res, mod, val, py / r))
							continue;
					}
					else if((a[j].y - a[i].y) % py != 0)
						continue;
					if((val = (a[i].vz - a[j].vz) % pz) < 0)
						val += pz;
					if(val)
					{
						if(std::__gcd(std::abs(a[j].z - a[i].z), pz) % (r = exgcd(val, pz, tx, ty)) != 0)
							continue;
						if((val = ((LL)tx * (a[j].z - a[i].z) % pz) / r) < 0)
							val += pz;
						if(!CRT(res, mod, val, pz / r))
							continue;
					}
					else if((a[j].z - a[i].z) % pz != 0)
						continue;
					if(tim > res)
						tim = res;
				}
			if(tim == INF)
				break;
			for(int i = 0; i < n; ++i)
			{
				if((a[i].x = (a[i].x + (LL)tim * a[i].vx) % px) < 0)
					a[i].x += px;
				if((a[i].y = (a[i].y + (LL)tim * a[i].vy) % py) < 0)
					a[i].y += py;
				if((a[i].z = (a[i].z + (LL)tim * a[i].vz) % pz) < 0)
					a[i].z += pz;
			}
			std::sort(a, a + n);
			int tot = 0;
			for(int i = 0, j = 0; i < n; )
			{
				for( ; j < n && a[i].x == a[j].x && a[i].y == a[j].y && a[i].z == a[j].z; ++j);
				int cnt = j - i;
				Node tmp = (Node){0, a[i].x, a[i].y, a[i].z, 0, 0, 0};
				for( ; i < j; ++i)
				{
					tmp.m += a[i].m;
					tmp.vx += a[i].vx;
					tmp.vy += a[i].vy;
					tmp.vz += a[i].vz;
				}
				tmp.vx /= cnt;
				tmp.vy /= cnt;
				tmp.vz /= cnt;
				a[tot++] = tmp;
			}
			n = tot;
		}
		std::sort(a, a + n, cmp);
		printf("%d\n", n);
		for(int i = 0; i < n; ++i)
			printf("P%d: %d %d %d %d %d %d %d\n", i, a[i].m, a[i].x, a[i].y, a[i].z, a[i].vx, a[i].vy, a[i].vz);
	}
	return 0;
}
