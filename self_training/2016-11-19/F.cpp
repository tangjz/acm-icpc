#include <stdio.h>
#include <algorithm>
using namespace std;
const int minn = (int)-2e9, maxn = (int)2e9;
int n, L = minn, R = maxn;
int main()
{
	scanf("%d", &n);
	while(n--)
	{
		char op[3], res[3];
		int val, vL, vR;
		scanf("%s%d%s", op, &val, res);
		if(op[0] == '<')
		{
			vL = minn;
			vR = val - (op[1] != '=');
		}
		else
		{
			vL = val + (op[1] != '=');
			vR = maxn;
		}
		if(res[0] == 'N')
		{
			if(vL == minn)
			{
				vL = vR + 1;
				vR = maxn;
			}
			else
			{
				vR = vL - 1;
				vL = minn;
			}
		}
		L = max(L, vL);
		R = min(R, vR);
	}
	if(L <= R)
		printf("%d\n", L);
	else
		puts("Impossible");
	return 0;
}
