#include <cstdio>
const int maxm = 21;
int n, m, ans[maxm][2][2];
template<class T> void scan(T& x)
{
	int ch, flag;
	while(((ch = getchar()) < '0' || ch > '9') && ch != '-');
	flag = ch == '-';
	x = flag ? 0 : ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + (ch - '0');
	if(flag)
		x = -x;
}
int main()
{
	scan(n), scan(m);
	for(int i = 1; i <= n; ++i)
	{
		int l, r, d;
		scan(l), scan(r), scan(d);
		if(!ans[d][0][1] || ans[d][0][0] > r)
		{
			ans[d][0][0] = r;
			ans[d][0][1] = i;
		}
		if(!ans[d][1][1] || ans[d][1][0] < l)
		{
			ans[d][1][0] = l;
			ans[d][1][1] = i;
		}
	}
	for(int i = 1; i <= m; ++i)
		if(ans[i][0][0] < ans[i][1][0])
			printf("TAK %d %d\n", ans[i][0][1], ans[i][1][1]);
		else
			puts("NIE");
	return 0;
}
