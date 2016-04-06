#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long LL;
int t, m, a, b, c, pow2, x, y, z;
template<class T> void exgcd(T a, T b, T &x, T &y)
{
	if(!b)
	{
		x = 1;
		y = 0;
		return;
	}
	exgcd(b, a % b, y, x);
	y -= a / b * x;
}
int mod_pow(int x, LL k, int mod)
{
	int ret = 1;
	while(k)
	{
		if(k & 1)
			ret = (LL)ret * x % mod;
		x = (LL)x * x % mod;
		k >>= 1;
	}
	return ret;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		x = y = z = 0;
		scanf("%d%d%d%d", &m, &a, &b, &c);
		for(pow2 = 0; ~(m >> pow2) & 1; ++pow2);
		{
			int s, t, px, py, pz;
			exgcd(m >> pow2, 1 << pow2, s, t);
			if(c == 1)
			{
				px = py = 1;
				pz = 2;
			}
			else if(a == 1 && b == 1)
			{
				px = 2;
				py = (m >> pow2) - 1;
				pz = 1;
			}
			else
			{
				LL s, t;
				exgcd((LL)c, (LL)a * b, s, t);
				if(s < 0)
					s += (LL)a * b;
				t = -t;
				if(t < 0)
					t += c;
				px = mod_pow(2, b * t, m >> pow2);
				py = mod_pow(2, a * t, m >> pow2);
				pz = mod_pow(2, s, m >> pow2);
			}
			x = (x + (1 << pow2) * t * (LL)px) % m;
			y = (y + (1 << pow2) * t * (LL)py) % m;
			z = (z + (1 << pow2) * t * (LL)pz) % m;
		}
		if(pow2)
		{
			int s, t, px, py, pz;
			exgcd(m >> pow2, 1 << pow2, s, t);
			if(pow2 > 1)
				if(a == 1 && b == 1 && c == 1)
				{
					px = py = 1;
					pz = 2;
				}
				else if(c == 1)
				{
					px = pz = 1;
					py = 1 << pow2 - 1;
					if(b == 1)
						swap(px, py);
				}
				else
				{
					px = 1;
					py = (1 << pow2) - 1;
					pz = 1 << pow2 - 1;
					if(~b & 1)
						swap(px, py);
				}
			else
			{
				px = py = 1;
				pz = 0;
			}
			x = (x + (m >> pow2) * s * (LL)px) % m;
			y = (y + (m >> pow2) * s * (LL)py) % m;
			z = (z + (m >> pow2) * s * (LL)pz) % m;
		}
		if(x < 0)
			x += m;
		if(y < 0)
			y += m;
		if(z < 0)
			z += m;
		printf("%d %d %d\n", x, y, z);
	}
	return 0;
}
