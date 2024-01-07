#include <cstdio>
int n, m, od, ev, fi, se;
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0, x; i < n; ++i)
	{
		scanf("%d", &x);
		x & 1 ? ++od : ++ev;
	}
	fi = n - m >> 1;
	se = n - m - fi;
	puts(n == m && (~od & 1) || m < n && (od <= fi || (~m & 1) && ev <= fi || (~(n - m) & 1) && ((~m & 1) || se < ev)) ? "Daenerys" : "Stannis");
	return 0;
}
