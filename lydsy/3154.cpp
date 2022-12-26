#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 1025;
int n, xx, yy, dxx, dxy, dx, dyx, dyy, dy, bit[maxn][maxn][4];
void add(int x, int y, int v)
{
	int v0 = v, v1 = v0 * x, v2 = v0 * y, v3 = v1 * y;
	for(int i = x; i <= n; i += i & -i)
		for(int j = y; j <= n; j += j & -j)
		{
			bit[i][j][0] += v0;
			bit[i][j][1] += v1;
			bit[i][j][2] += v2;
			bit[i][j][3] += v3;
		}
}
int sum(int x, int y)
{
	int r0 = 0, r1 = 0, r2 = 0, r3 = 0;
	for(int i = x; i > 0; i -= i & -i)
		for(int j = y; j > 0; j -= j & -j)
		{
			r0 += bit[i][j][0];
			r1 += bit[i][j][1];
			r2 += bit[i][j][2];
			r3 += bit[i][j][3];
		}
	return r0 * (x + 1) * (y + 1) - r1 * (y + 1) - r2 * (x + 1) + r3;
}
void trans(int px, int py, int &nx, int &ny)
{
	--px;
	--py;
	nx = (px * dxx + py * dxy + dx) % n;
	if(nx < 0)
		nx += n;
	ny = (px * dyx + py * dyy + dy) % n;
	if(ny < 0)
		ny += n;
	++nx;
	++ny;
}
int main()
{
	scanf("%d", &n);
	xx = yy = -1;
	dxx = dyy = 1;
	for(char op[3]; scanf("%s", op) != EOF; )
	{
		int a, b, c, d, e;
		if(op[0] == 'L' || op[0] == 'k')
		{
			scanf("%d%d%d%d", &a, &b, &c, &d);
			if(op[0] == 'L')
				scanf("%d", &e);
			if((a < c) ^ (xx < 0))
				swap(a, c);
			if((b < d) ^ (yy < 0))
				swap(b, d);
			trans(a, b, a, b);
			trans(c, d, c, d);
			if(op[0] == 'L')
			{
				if(a <= c)
					if(b <= d)
					{
						add(a, b, e);
						add(a, d + 1, -e);
						add(c + 1, b, -e);
						add(c + 1, d + 1, e);
					}
					else
					{
						add(a, 1, e);
						add(a, d + 1, -e);
						add(a, b, e);
						add(c + 1, 1, -e);
						add(c + 1, d + 1, e);
						add(c + 1, b, -e);
					}
				else //if(a > c)
					if(b <= d)
					{
						add(1, b, e);
						add(1, d + 1, -e);
						add(c + 1, b, -e);
						add(c + 1, d + 1, e);
						add(a, b, e);
						add(a, d + 1, -e);
					}
					else
					{
						add(1, 1, e);
						add(1, d + 1, -e);
						add(1, b, e);
						add(c + 1, 1, -e);
						add(c + 1, d + 1, e);
						add(c + 1, b, -e);
						add(a, 1, e);
						add(a, d + 1, -e);
						add(a, b, e);
					}
			}
			else
			{
				int ret = 0;
				if(a <= c)
					if(b <= d)
						ret = sum(c, d) - sum(a - 1, d) - sum(c, b - 1) + sum(a - 1, b - 1);
					else
						ret = sum(c, n) - sum(c, b - 1) + sum(c, d)
							- sum(a - 1, n) + sum(a - 1, b - 1) - sum(a - 1, d);
				else //if(a > c)
					if(b <= d)
						ret = sum(n, d) - sum(a - 1, d) + sum(c, d)
							- sum(n, b - 1) + sum(a - 1, b - 1) - sum(c, b - 1);
					else
						ret = sum(n, n) - sum(n, b - 1) + sum(n, d)
							- sum(a - 1, n) + sum(a - 1, b - 1) - sum(a - 1, d)
							+ sum(c, n) - sum(c, b - 1) + sum(c, d);
				printf("%d\n", ret);
			}
		}
		else if(op[0] == 'C')
		{
			scanf("%d%d%d", &a, &b, &e);
			trans(a, b, a, b);
			int now = sum(a, b) - sum(a - 1, b) - sum(a, b - 1) + sum(a - 1, b - 1);
			add(a, b, e - now);
			add(a, b + 1, now - e);
			add(a + 1, b, now - e);
			add(a + 1, b + 1, e - now);
		}
		else if(op[0] == 'Q')
		{
			for(int i = 1; i <= n; ++i)
				for(int j = 1; j <= n; ++j)
				{
					trans(i, j, a, b);
					int ret = sum(a, b) - sum(a - 1, b) - sum(a, b - 1) + sum(a - 1, b - 1);
					printf("%d%c", ret, " \n"[j == n]);
				}
		}
		else if(op[0] == 'F')
		{
			if(op[1] == 'x')
			{
				yy = -yy;
				dx = (dx - dxy) % n;
				dxy = -dxy;
				dy = (dy - dyy) % n;
				dyy = -dyy;
			}
			else
			{
				xx = -xx;
				dx = (dx - dxx) % n;
				dxx = -dxx;
				dy = (dy - dyx) % n;
				dyx = -dyx;
			}
		}
		else if(op[0] == 'D')
		{
			scanf("%d", &a);
			if(op[1] == 'x')
			{
				dx = (dx - a * dxx) % n;
				dy = (dy - a * dyx) % n;
			}
			else
			{
				dx = (dx - a * dxy) % n;
				dy = (dy - a * dyy) % n;
			}
		}
		else //if(op[0] == 'R')
		{
			swap(dxx, dxy);
			swap(dyx, dyy);
			swap(xx, yy);
			if(op[1] == '+')
			{
				dx = (dx - dxy) % n;
				dxy = -dxy;
				dy = (dy - dyy) % n;
				dyy = -dyy;
				yy = -yy;
			}
			else
			{
				dx = (dx - dxx) % n;
				dxx = -dxx;
				dy = (dy - dyx) % n;
				dyx = -dyx;
				xx = -xx;
			}
		}
	}
	return 0;
}
