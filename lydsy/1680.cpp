#include <cstdio>
long long n, s, c, y, tmp, ans;
int main()
{
	scanf("%lld%lld\n", &n, &s);
	for(int i = 0; i < n; ++i)
	{
		scanf("%lld%lld", &c, &y);
		if(!i) tmp = c;
		else tmp += s;
		if(tmp > c) tmp = c;
		ans += tmp * y;
	}
	printf("%lld\n", ans);
	return 0;
}

