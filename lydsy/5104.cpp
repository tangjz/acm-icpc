//#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long LL;
LL p, C;
struct unreal
{
	LL a, b;
	inline unreal operator * (const unreal &t) const
	{
		unreal tmp = {};
		tmp.a = (a * t.a + b * t.b % p * C) % p;
		tmp.b = (a * t.b + b * t.a) % p;
		return tmp;
	}
};
inline LL Pow(unreal x, LL c, LL n)
{
	unreal ans = {};
	ans.a = 1, C = c;
	while(n)
	{
		if(n & 1) ans = ans * x;
		x = x * x;
		n >>= 1;
	}
	return ans.a;
}
inline LL Pow(LL x, LL n)
{
	LL ans = 1;
	while(n)
	{
		if(n & 1) ans = ans * x % p;
		x = x * x % p;
		n >>= 1;
	}
	return ans;
}
struct HASH { LL a, id; } Hash[100001];
inline bool cmp(const HASH &x, const HASH &y) { return x.a < y.a; }
inline int Search(int l, int r, LL tmp)
{
    while(l <= r)
    {
    	int mid = l + r >> 1;
        if(tmp == Hash[mid].a) return Hash[mid].id;
        tmp < Hash[mid].a ? r = mid - 1 : l = mid + 1;
    }
    return -1;
}
LL lasta;
inline LL Solve(LL a, LL b)//a^x = b(mod p)
{
	LL size = (LL)sqrt(p);
	LL delta = size + (p % size);
	LL tmp = 1;
    if(lasta != a)
	{
		for(int i = 0; i < size; ++i) Hash[i].a = tmp, Hash[i].id = i, tmp = tmp * a % p;
		sort(Hash, Hash + size, cmp);
	}
	lasta = a;
	tmp = b, a = Pow(a, (p - 1) - size % (p - 1));
	for(int i = 0; i < delta; ++i)
	{
		int id = Search(0, size - 1, tmp);
		if(id != -1) return i * size + id;
		tmp = tmp * a % p;
	}
	return p;
}
inline LL Sqrt(LL x)//x^2 = a(mod p)
{
	if(!x) return 0;
	if(Pow(x, p - 1 >> 1) == p - 1) return -1;
	LL a, b;
	do
	{
		a = rand() % p;
		b = (a * a % p - x + p) % p;
	} while(Pow(b, p - 1 >> 1) == 1);
	unreal tmp;
	tmp.a = a, tmp.b = 1;
	return Pow(tmp, b, p + 1 >> 1);
}
LL ans;
inline void SSolve(LL sqrt5, LL num)
{
	num = num * sqrt5 % p * Pow(2, p - 2) % p;
	//(a^x - num) = b(mod p)
	LL a = (1 + sqrt5) * Pow(2, p - 2) % p, b, tmp;
	//x & 1 == 1
	b = Sqrt((p - 1 + num * num) % p);
	if(b != -1)
	{
		tmp = Solve(a, (num + b) % p);
		if(tmp & 1) ans = min(ans, tmp);
		tmp = Solve(a, (num - b + p) % p);
		if(tmp & 1) ans = min(ans, tmp);
	}
	//x & 1 == 0
	b = Sqrt((1 + num * num) % p);
	if(b != -1)
	{
		tmp = Solve(a, (num + b) % p);
		if(!(tmp & 1)) ans = min(ans, tmp);
		tmp = Solve(a, (num - b + p) % p);
		if(!(tmp & 1)) ans = min(ans, tmp);
	}
}
int main()
{
	//srand(time(NULL));
	LL num;
	scanf("%lld", &num);
	ans = p = (int)1e9 + 9;
	LL sqrt5 = Sqrt(5);
	if(sqrt5 == -1 || num == p) { puts("-1"); return 0; }
	SSolve(sqrt5, num);
	SSolve(p - sqrt5, num);
	if(ans == p) puts("-1");
	else printf("%lld\n", ans);
	return 0;
}
