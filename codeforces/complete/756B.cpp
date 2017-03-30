#include <stdio.h>
const int maxn = 100001;
int n, a[maxn], f[maxn], q1[maxn], L1, R1, q2[maxn], L2, R2;
int main()
{
	scanf("%d", &n);
	f[0] = 0;
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", a + i);
		f[i] = f[i - 1] + 20;
		for( ; L1 < R1 && a[i] - a[q1[L1]] >= 90; ++L1);
		if(L1 < R1 && f[i] > f[q1[L1] - 1] + 50)
			f[i] = f[q1[L1] - 1] + 50;
		//for( ; L1 < R1 && f[q1[R1 - 1]] >= f[i]; --R1);
		q1[R1++] = i;
		for( ; L2 < R2 && a[i] - a[q2[L2]] >= 1440; ++L2);
		if(L2 < R2 && f[i] > f[q2[L2] - 1] + 120)
			f[i] = f[q2[L2] - 1] + 120;
		//for( ; L2 < R2 && f[q2[R2 - 1]] >= f[i]; --R2);
		q2[R2++] = i;
		printf("%d\n", f[i] - f[i - 1]);
	}
	return 0;
}
