/*
 * 设b某一边比它大的数与比它小的数个数之差为i
 * 左边出现i的次数为left[i] 右边为right[i]
 * ans = ∑left[i] * rigth[-i]
 */
#include <map>
#include <cstdio>
using namespace std;
map<int, int> cnt[2];
int n, b, num[100001], ans = 0;
int main()
{
	int i, j, sum;
	scanf("%d%d", &n ,&b);
	for(i = 0; i < n; ++i)
	{
		scanf("%d", &num[i]);
		if(num[i] == b) j = i;
	}
	cnt[0][0] = 1; cnt[1][0] = 1;
	for(i = j - 1, sum = 0; i >= 0; --i)
	{
		if(num[i] < b) --sum; else ++sum;
		++cnt[0][sum];
	}
	for(i = j + 1, sum = 0; i < n; ++i)
	{
		if(num[i] < b) --sum; else ++sum;
		++cnt[1][sum];
	}
	for(i = -n; i <= n; ++i) ans += cnt[0][i] * cnt[1][-i];
	printf("%d\n", ans);
	return 0;
}
