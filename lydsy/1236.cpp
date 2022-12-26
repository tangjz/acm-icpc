/*
 * 先把n按十进制拆出每一位 假设有一共L位
 * 先求前L-1位的和:
 * 个位直接算
 * 对于有i位的所有数求和
 * 显然第一个数的第一位前面是负号
 * 如果i是奇数,相邻两项相消,剩下1,最后和就是+10 ^ (i - 1) / 2
 * 如果i是偶数,除了最高位,所有位出现那些数字的概率均相等,所以除了最高位和次高位,相邻的两位均可以相消
 * 				由于没有以0开头的数,所以第二位相对于第一位少了45 * 10 ^ (i - 2),最后的和就是-45 * 10 ^ (i - 2)
 * 然后处理L位的所有数
 * 如果L为奇数,相邻两项相消,剩下1,根据n的奇偶把最后一个数判掉(可能不成对)
 * 如果L为偶数,就一位一位向下算就好了,毕竟每一位的正负是确定的
 */
#include <cstdio>
long long n, len, num[17], s[10], ans, f[16];
int main()
{
	int i;
	scanf("%lld", &n);
	if(n < 10)
	{
		printf("%lld\n", n & 1 ? n + 1 >> 1 : -(n + 1 >> 1));
		return 0;
	}
	for(long long tmp = n; tmp; tmp /= 10) num[++len] = tmp % 10;
	ans = 5;
	for(f[i = 0] = 1, ++i; i <= 15; ++i) f[i] = f[i - 1] * 10;
	for(i = 1; i < 10; ++i) s[i] = s[i - 1] + i;
	for(i = 2; i < len; ++i)
		if(i & 1) ans += 9 * f[i - 1] >> 1;
		else ans -= 45 * f[i - 2];
	if(len & 1)
	{
		if(n & 1) ans += n + 1 - f[len - 1] >> 1;
		else
		{
			ans += n - f[len - 1] >> 1;
			for(i = len; i; --i)
				if(i & 1) ans -= num[i];
				else ans += num[i];
		}
	}
	else
		for(i = len; i; --i)
			if(num[i])
			{
				if(i & 1) ans += s[num[i] - 1] * f[i - 1] + num[i] * (n % f[i - 1] + 1);
				else ans += (45 * (num[i] - (i == len)) - s[num[i] - 1] * 10) * f[i - 2] - num[i] * (n % f[i - 1] + 1);
			}
	printf("%lld\n", ans);
	return 0;
}
