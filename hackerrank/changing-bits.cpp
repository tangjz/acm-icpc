#include <stdio.h>
typedef unsigned long long ULL;
const int maxn = 100001, maxs = ((maxn - 1) >> 6) + 1, maxm = 500001;
int n, m, sz;
ULL A[maxs], B[maxs], C[maxs];
char buf[maxm];
int main()
{
	scanf("%d%d%s", &n, &m, buf);
	for(int i = 0; i < n; ++i)
		if(buf[n - 1 - i] == '1')
			A[i >> 6] |= 1ULL << (i & 63);
	scanf("%s", buf);
	for(int i = 0; i < n; ++i)
		if(buf[n - 1 - i] == '1')
			B[i >> 6] |= 1ULL << (i & 63);
	while(m--)
	{
		int x, y;
		char op[1 << 4 | 1];
		scanf("%s%d", op, &x);
		if(op[0] == 's')
		{
			scanf("%d", &y);
			ULL *F = op[4] == 'a' ? A : B;
			if(((F[x >> 6] >> (x & 63)) & 1) ^ y)
				F[x >> 6] ^= 1ULL << (x & 63);
		}
		else
		{
			if(x > n)
			{
				buf[sz++] = '0';
				continue;
			}
			ULL d = 0;
			for(int i = 0; i <= (x >> 6); ++i)
			{
				C[i] = A[i] + B[i] + d;
				d = (B[i] || d) && C[i] <= A[i];
			}
			buf[sz++] = '0' + ((C[x >> 6] >> (x & 63)) & 1);
		}
	}
	buf[sz] = '\0';
	puts(buf);
	return 0;
}
