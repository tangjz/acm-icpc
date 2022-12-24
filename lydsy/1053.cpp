/*
 * 考虑约数个数最大的数们，如果交换相邻两个质因子的个数，那么质因子越小出现次数越多的数越小，越有可能是反质数
 * 剪枝1：当前得到的数不能超过n
 * 剪枝2：必须是前几个质因数的乘积，而且满足质因数越小出现次数越多
 * 剪枝3：满足剪枝2的x的质因子的数量不会很多，可以计算大概不会超过10个
 */
#include <cstdio>
const int tot = 10, prime[] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
int n, ans, cnt;
void dfs(int i, int last, int x, int sum)
{
	if(cnt < sum || cnt == sum && x < ans) cnt = sum, ans = x;
	if(i > tot) return;
	for(int j = 1; j <= last; ++j)
		if((long long)x * prime[i] <= n)
		{
			x *= prime[i];
			dfs(i + 1, j, x, sum * (j + 1));
		}
		else break;
}
int main()
{
	scanf("%d", &n);
	dfs(1, 23, 1, 1);
	printf("%d\n", ans);
	return 0;
}
