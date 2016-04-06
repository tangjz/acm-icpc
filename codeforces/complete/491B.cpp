#include <cstdio>
const int INF = ~0u >> 1;
int c, h, x, y, d[4] = {INF, INF, INF, INF}, ans = INF, pos;
template<class T> T abs(const T& x)
{
	return x < 0 ? -x : x;
}
template<class T> const T& min(const T& x, const T& y)
{
	return x < y ? x : y;
}
template<class T> const T& max(const T& x, const T& y)
{
	return x < y ? y : x;
}
int main()
{
	scanf("%*d%*d%d", &c);
	while(c--)
	{
		scanf("%d%d", &x, &y);
		d[0] = min(d[0], x + y);
		d[1] = min(d[1], x - y);
		d[2] = min(d[2], -x + y);
		d[3] = min(d[3], -x - y);
	}
	scanf("%d", &h);
	for(int i = 1; i <= h; ++i)
	{
		scanf("%d%d", &x, &y);
		int res = max(max(abs(d[0] - x - y), abs(d[1] - x + y)), max(abs(d[2] + x - y), abs(d[3] + x + y)));
		if(res < ans)
		{
			ans = res;
			pos = i;
		}
	}
	printf("%d\n%d\n", ans, pos);
	return 0;
}
