#include <stdio.h>
#include <algorithm>
const int maxn = 110;
int n, tot, sgn[maxn], L, R, val[maxn];
char str[2];
int main()
{
	for(char op = '+'; scanf("%s", str) == 1; )
		if(str[0] == '?')
		{
			sgn[tot++] = op == '+' ? 1 : -1;
			scanf("%s", str);
			op = str[0];
			if(op == '=')
			{
				scanf("%d", &n);
				break;
			}
		}
	for(int i = 0; i < tot; ++i)
	{
		int l = sgn[i] * 1, r = sgn[i] * n;
		if(l > r)
			std::swap(l, r);
		L += l;
		R += r;
	}
	if(n < L || R < n)
	{
		puts("Impossible");
		return 0;
	}
	puts("Possible");
	sgn[tot] = 0;
	for(int i = 0, val = n; i < tot; ++i)
	{
		int l = sgn[i] * 1, r = sgn[i] * n;
		if(l > r)
			std::swap(l, r);
		L -= l;
		R -= r;
		int vl = sgn[i] * (val - L), vr = sgn[i] * (val - R);
		if(vl > vr)
			std::swap(vl, vr);
		if(vl < 1)
			vl = 1;
		val -= sgn[i] * vl;
		printf("%d %c ", vl, i == tot - 1 ? '=' : sgn[i + 1] < 0 ? '-' : '+');
	}
	printf("%d\n", n);
	return 0;
}
