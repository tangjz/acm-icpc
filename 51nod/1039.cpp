#include <ctime>
#include <stdio.h>
#include <cstdlib>
#include <algorithm>
typedef long long LL;
int a, b, p;
int mod_pow(int x, int k)
{
	int ret = 1;
	for( ; k > 0; k >>= 1, x = (LL)x * x % p)
		if(k & 1)
			ret = (LL)ret * x % p;
	return ret;
}
int mod_inv(int x)
{
	return x <= 1 ? x : p - (int)(p / x * (LL)mod_inv(p % x) % p);
}
struct Pair
{
	int x, y;
	Pair operator * (const Pair &t) const
	{
		return (Pair){
			(int)(((LL)x * t.x + (LL)y * t.y % p * b) % p),
			(int)(((LL)x * t.y + (LL)y * t.x) % p)
		};
	}
	Pair pow(int k)
	{
		Pair ret = (Pair){1, 0}, tmp = *this;
		for( ; k > 0; k >>= 1, tmp = tmp * tmp)
			if(k & 1)
				ret = ret * tmp;
		return ret;
	}
};
int mod_sqrt(int x)
{
	if(!x || p <= 2)
		return x;
	if(mod_pow(x, p - 1 >> 1) != 1)
		return -1;
	int w, y;
	do
	{
		w = ((LL)rand() << 15 | rand()) % p;
		if((y = ((LL)w * w - x) % p) < 0)
			y += p;
	} while(mod_pow(y, p - 1 >> 1) == 1);
	Pair A = (Pair){w, 1};
	b = y;
	A = A.pow(p + 1 >> 1);
	return A.x;
}
struct Triple
{
	int x, y, z;
	Triple operator * (const Triple &t) const
	{
		return (Triple){
			(int)(((LL)x * t.x + ((LL)y * t.z + (LL)z * t.y) % p * a) % p),
			(int)(((LL)x * t.y + (LL)y * t.x + (LL)z * t.z % p * a) % p),
			(int)(((LL)x * t.z + (LL)y * t.y + (LL)z * t.x) % p)
		};
	}
	Triple pow(int k)
	{
		Triple ret = (Triple){1, 0, 0}, tmp = *this;
		for( ; k > 0; k >>= 1, tmp = tmp * tmp)
			if(k & 1)
				ret = ret * tmp;
		return ret;
	}
};
int main()
{
	int t;
	scanf("%d", &t);
	srand(time(NULL));
	while(t--)
	{
		scanf("%d%d", &p, &a);
		if(!a || p <= 3)
		{
			printf("%d\n", a);
			continue;
		}
		if(p % 3 != 1)
		{
			printf("%d\n", mod_pow(a, ((p << 1) - 1) / 3));
			continue;
		}
		if(mod_pow(a, (p - 1) / 3) != 1)
		{
			puts("No Solution");
			continue;
		}
		Triple A;
		do
		{
			A.x = ((LL)rand() << 15 | rand()) % p;
			A.y = ((LL)rand() << 15 | rand()) % p;
			A.z = ((LL)rand() << 15 | rand()) % p;
			A = A.pow((p - 1) / 3);
		} while(A.x || A.z);
		int g = (mod_sqrt(p - 3) - 1LL) * (p + 1 >> 1) % p, ans[3];
		ans[0] = mod_inv(A.y);
		ans[1] = (LL)ans[0] * g % p;
		ans[2] = (LL)ans[1] * g % p;
		std::sort(ans, ans + 3);
		for(int i = 0; i < 3; ++i)
			printf("%d%c", ans[i], " \n"[i == 2]);
	}
	return 0;
}
