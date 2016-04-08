/*
 * k个瓶子之间的倾倒操作相当于辗转相减，可以得到的最小值即为k个瓶子容量的最大公因数 
 * 从大到小枚举所有因数 检查是否有至少k个数有这个因数... 
 */
#include <map>
#include <cstdio>
#include <algorithm>
using namespace std;
map<int, int> cnt;
int n, k, x, i;
int main()
{
	scanf("%d%d", &n, &k);
	while(n--)
	{
		scanf("%d", &x);
		for(i = 1; i * i < x; ++i)
			if(x % i == 0) ++cnt[i], ++cnt[x / i];
		if(i * i == x) ++cnt[i];
	}
	map<int, int>::iterator it = cnt.end(), jt = cnt.begin();
	for(--it, --jt; it != jt; --it)
		if(it -> second >= k)
		{
			printf("%d\n", it -> first);
			break;
		}
	return 0;
}
