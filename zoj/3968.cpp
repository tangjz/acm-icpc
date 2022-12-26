#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef long double DB;
const DB eps = 1e-12;
int t, x[3], y[3], r[3], px, py, pr2, tot;
DB ansx[9], ansy[9], ansr[9];
int sgn(DB x)
{ // assert(!std::isnan(x));
	return (x > eps) - (x < -eps);
}
template<class T> inline T sqr(T x)
{
	return x * x;
}
inline int lcm(int x, int y)
{ // assert(x && y);
	return x / __gcd(x, y) * y;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		for(int i = 0; i < 3; ++i)
		{
			scanf("%d%d%d", x + i, y + i, r + i);
			x[i] <<= 1;
			y[i] <<= 1;
			r[i] <<= 1;
		}
		if(x[0] > x[1])
		{
			swap(x[0], x[1]);
			swap(y[0], y[1]);
			swap(r[0], r[1]);
		}
		if((x[1] - x[0]) < abs(r[1] - r[0]))
		{
			puts("0");
			continue;
		}
		int dt = ((x[1] - x[0]) - (r[0] + r[1])) >> 1;
		r[0] += dt; // assert(r[0] > 0);
		r[1] += dt; // assert(r[1] > 0);
		r[2] += dt;
		px = x[0] + r[0]; // py = 0;
		int dis = abs(sqr(x[2] - px) + sqr(y[2] - py) - sqr(r[2]));
		pr2 = lcm(lcm(r[0], r[1]) << 1, dis ? dis : r[2] << 1); // ~ 10^8
		int xL = px - (pr2 >> 1) / r[0], xR = px + (pr2 >> 1) / r[1]; // inverse A, B into line
		if((xR - xL) & 1)
		{
			pr2 <<= 1;
			xL = px - (pr2 >> 1) / r[0];
			xR = px + (pr2 >> 1) / r[1];
		}
		int rM = (xR - xL) >> 1, xM = xL + rM;
		tot = 0;
		if(dis == 0)
		{ // inverse C into line
			int dis2 = (pr2 >> 1) / r[2];
			DB rx2 = px + dis2 * (x[2] - px) / (DB)r[2], ry2 = py + dis2 * (y[2] - py) / (DB)r[2];
			DB yM = ry2 - (x[2] - px) / (DB)(y[2] - py) * (xM - rx2);
			DB dy = yM / (DB)dis2 * rM;
			// (xM, yM - dy, rM)
			ansx[tot] = xM;
			ansy[tot] = yM - dy;
			ansr[tot++] = rM;
			// (xM, yM + dy, rM)
			ansx[tot] = xM;
			ansy[tot] = yM - dy;
			ansr[tot++] = rM;
		}
		else
		{ // inverse C into circle
			int coeff = pr2 / dis, rr2 = coeff * r[2];
			int rx2 = px + (x[2] - px) * coeff, ry2 = py + (y[2] - py) * coeff;
			int disL = abs(rx2 - xM);
			if(disL <= rM + rr2)
			{
				DB dy = sqrt(sqr((LL)(rM + rr2)) - sqr((LL)disL));
				// (xM, ry2 - dy, rM)
				ansx[tot] = xM;
				ansy[tot] = ry2 - dy;
				ansr[tot++] = rM;
				if(disL < rM + rr2)
				{ // (xM, ry2 + dy, rM)
					ansx[tot] = xM;
					ansy[tot] = ry2 + dy;
					ansr[tot++] = rM;
				}
			}
			if(disL <= rM - rr2)
			{
				DB dy = sqrt(sqr((LL)(rM - rr2)) - sqr((LL)disL));
				// (xM, ry2 - dy, rM)
				ansx[tot] = xM;
				ansy[tot] = ry2 - dy;
				ansr[tot++] = rM;
				if(disL < rM - rr2)
				{ // (xM, ry2 + dy, rM)
					ansx[tot] = xM;
					ansy[tot] = ry2 + dy;
					ansr[tot++] = rM;
				}
			}
		}
		int cnt = 0;
		DB rad = 2e4;
		for(int i = 0; i < tot; ++i)
		{
			DB ax = ansx[i], ay = ansy[i], ar = ansr[i];
			DB dis2 = abs(sqr(ax - px) + sqr(ay - py) - sqr(ar)), coeff = pr2 / dis2;
			DB bx = px - (ax - px) * coeff, by = py - (ay - py) * coeff, br = ar * coeff;
			//printf("inversal %f %f %f\n", (double)ax, (double)ay, (double)ar);
			//printf("original %f %f %f\n", (double)bx, (double)by, (double)br);
			bool flag = 1;
			for(int j = 0; j < 3 && flag; ++j)
				flag &= !sgn(sqr(bx - x[j]) + sqr(by - y[j]) - sqr(br - r[j]));
			if(flag)
			{
				if(sgn(br - rad) < 0)
				{
					rad = br;
					cnt = 0;
				}
				if(!sgn(br - rad))
					++cnt;
			}
		}
		rad = (rad - dt) * 0.5;
		if(cnt)
			printf("%d %.12f\n", cnt << 1, (double)rad);
		else
			puts("0");
	}
	return 0;
}
