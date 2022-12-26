#include <cstdio>
#include <cctype>
inline int ScanInt(){int r=0,c;while(!isdigit(c=getchar()));r=c-'0';while(isdigit(c=getchar()))r=(r<<3)+(r<<1)+c-'0';return r;}
struct Node { int d, s, t; } q[1000001] = {};
int n, m, room[1000001] = {}, sum[1000001] = {};
int main()
{
	n = ScanInt();
	m = ScanInt();
	int i, tmp, l = 1, r = m, mid, cnt_sum = 0, cnt_q = 0;
	for(i = 1; i <= n; ++i) room[i] = ScanInt();
	while(l <= r)
	{
		mid = (l + r) >> 1;
		if(mid > cnt_q)
		{
			for(i = cnt_q + 1; i <= mid; ++i) q[i].d = ScanInt(), q[i].s = ScanInt(), q[i].t = ScanInt();
			cnt_q = mid;
		}
		for(i = cnt_sum + 1;i <= mid; ++i)
		{
			sum[q[i].s] += q[i].d;
			sum[q[i].t + 1] -= q[i].d;
		}
		for(i = mid + 1; i <= cnt_sum; ++i)
		{
			sum[q[i].s] -= q[i].d;
			sum[q[i].t + 1] += q[i].d;
		}
		cnt_sum = mid;
		tmp = 0;
		for(i = 1; i <= n; ++i)
		{
			tmp += sum[i];
			if(room[i] < tmp)break;
		}
		if(i <= n) r = mid - 1;
		else l = mid + 1;
	}
	if(m == l - 1) printf("0\n");
	else printf("-1\n%d\n", l);
	return 0;
}
