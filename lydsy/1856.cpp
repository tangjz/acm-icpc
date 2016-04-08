/*
 * 考虑从空串构造出满足要求的字符串，有两种操作：在末尾加0或加1
 * 将其映射到二维平面内：对于某个串，1的个数作为横坐标，0的个数作为纵坐标 
 * 空串在原点(0,0)，加1相当于沿x正半轴移动一格，加0同理 
 * 构造路线即从(0,0)走到(n,m)，不同的字符串即不同的构造路线 
 * 现在要求任意前k个字符中1的个数不少于0的个数，即构造路线不能超过y=x这条直线 
 * 题目转化为经典的卡特兰数 
 */
#include <cstdio>
typedef long long LL;
const int maxn = 2000001, mod = 20100403;
int n, m, fact[maxn];
inline int pow(int x, int k)
{
	int ret = 1;
	while(k)
	{
		if(k & 1) ret = ret * (LL)x % mod;
		x = x * (LL)x % mod;
		k >>= 1;
	}
	return ret;
}
int main()
{
	scanf("%d%d", &n, &m);
	fact[0] = 1;
	for(int i = 1; i < maxn; ++i)
		fact[i] = fact[i - 1] * (LL)i % mod;
	printf("%lld\n", (LL)fact[n + m] * (n + 1 - m) % mod * pow((LL)fact[n + 1] * fact[m] % mod, mod - 2) % mod);
	return 0;
}
