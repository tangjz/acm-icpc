/*
 * 单调队列 + 并查集
 * 注意到这个数列只增加不删除，而最大值我们其实可以把它维护成一个单调减队列
 * 在这个单调队列中，我们等价于把那些非最优点隐形
 * 那么由这些凸峰分隔成了若干个区间，我们可以利用一个并查集来维护从i到末尾最大值的祖先
 */
#include <cstdio>
int  n, d, q[200010], loc[200010], head, tail, len;
int query(int x)
{
	int l = 0, r = tail + 1, mid;
	while(l < r - 1)
	{
		mid = l + r >> 1;
		if (loc[mid] < x) l = mid;
		else r = mid;
	}
	return q[l + 1];
}
int main ()
{
	char s[10];
	head = 1, tail = 0;
	scanf("%d%d", &n, &d);
	for (int i = 1, ans = 0, x; i <= n; ++i)
	{
		scanf ("%s%d", s, &x);
		if(s[0] == 'Q') printf("%d\n", ans = query(len - x + 1));
		if(s[0] == 'A')
		{
			x = (x + ans) % d;
			while (head <= tail && q[tail] < x) --tail;
			q[++tail] = x;
			loc[tail] = ++len;
		}
	}
	return 0;
}
