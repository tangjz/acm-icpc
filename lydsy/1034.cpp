/*
 * 贪心出最大值 反贪心出最小值
 */
#include <cstdio>
#include <algorithm>
using namespace std;
int n;
struct Team
{
	int val[100001];
	void init()
	{
		for(int i = 0; i < n; ++i) scanf("%d", &val[i]);
		sort(val, val + n);
	}
	int win(const Team loser) const
	{
		int ans = 0, l1 = 0, r1 = n - 1, l2 = 0, r2 = n - 1;
		while(l1 <= r1)
		{
			if(val[l1] > loser.val[l2]) { ans += 2; ++l1; ++l2; }
			else if(val[r1] > loser.val[r2]) { ans += 2; --r1; --r2; }
			else { ans += (val[l1] == loser.val[r2]); ++l1; --r2; }
		}
		return ans;
	}
} sb, sx;
int main()
{
	scanf("%d", &n);
	sb.init(); sx.init();
	printf("%d %d\n", sb.win(sx), n * 2 - sx.win(sb));
	return 0;
}
