#include <cstdio>
const long long INF = 100000;
long long c, hr, hb, wr, wb, ans;
void swap(long long &x, long long &y)
{
	long long t = x;
	x = y;
	y = t;
}
void upd(long long &x, long long y)
{
	if(x < y)
		x = y;
}
int main()
{
	scanf("%I64d%I64d%I64d%I64d%I64d", &c, &hr, &hb, &wr, &wb);
	if(wr > wb)
	{
		swap(wr, wb);
		swap(hr, hb);
	}
	if(wb >= INF)
		for(long long i = 0; i * wb <= c; ++i)
			upd(ans, i * hb + (c - i * wb) / wr * hr);
	else
	{
		if(wb * hr > wr * hb)
		{
			swap(wr, wb);
			swap(hr, hb);
		}
		for(long long i = 0; i <= wb && i * wr <= c; ++i)
			upd(ans, i * hr + (c - i * wr) / wb * hb);
	}
	printf("%I64d\n", ans);
	return 0;
}
