/*
 * 第一问快速幂
 * 第二问扩展欧几里得
 * 第三问大步小步
 */
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
int pow(int x, int k, int p)
{
	int ret = 1;
	while(k)
	{
		if(k & 1) ret = ret * (LL)x % p;
		x = x * (LL)x % p;
		k >>= 1;
	}
	return ret;
}
void exgcd(int a, int b, int &x, int &y)
{
	if(!b) { x = 1; y = 0; return; }
	exgcd(b, a % b, y, x);
	y -= (a / b) * x;
}
int Size, Num;
pair<int, int> Hash[40000];
int find(int x)
{
	int l = 0, r = Size - 1;
	while(l < r)
	{
		int mid = l + r >> 1;
		if(Hash[mid].first < x) l = mid + 1;
		else r = mid;
	}
	if(Hash[l].first == x) return Hash[l].second;
	return -1;
}
void bsgs(int y, int z, int p)
{
	Size = (int)sqrt(p);
	Num = p / Size + (p % Size != 0);
	for(int i = 0, t = 1; i < Size; ++i, t = t * (LL)y % p)
		Hash[i] = make_pair(t, i);
	sort(Hash, Hash + Size);
	int inv, tmp;
	exgcd(y, p, inv, tmp);
	if(inv < 0) inv += p;
	inv = pow(inv, Size, p);
	for(int i = 0, t = z, tt; i < Num; ++i, t = t * (LL)inv % p)
		if((tt = find(t)) != -1)
		{
			printf("%d\n", i * Size + tt);
			return;
		}
	puts("Orz, I cannot find x!");
}
int t, k, y, z, p;
int main()
{
	scanf("%d%d", &t, &k);
	while(t--)
	{
		scanf("%d%d%d", &y, &z, &p);
		y %= p;
		z %= k == 1 ? p - 1 : p;
		if(k == 1) printf("%d\n", pow(y, z, p));
		else if(k == 2)
			if(!z) puts("0");
			else if(!y) puts("Orz, I cannot find x!");
			else
			{
				int inv, tmp;
				exgcd(y, p, inv, tmp);
				if(inv < 0) inv += p;
				printf("%d\n", inv * (LL)z % p);
			}
		else if(k == 3)
			if(!y)
				if(!z) puts("1");
				else puts("Orz, I cannot find x!");
			else bsgs(y, z, p);
	}
	return 0;
}
