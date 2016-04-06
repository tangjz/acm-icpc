/*
ID: tangjin2
LANG: C++
TASK: pprime
*/
#include <cmath>
#include <cstdio>
int l, r;
bool prime(int x)
{
	for(int i = 2, j = (int)sqrt(x); i <= j; ++i) if(x % i == 0) return 0;
	return 1;
}
int main()
{
	freopen("pprime.in", "r", stdin);
	freopen("pprime.out", "w", stdout);
	scanf("%d%d", &l, &r);
	for(int a = 1, tmp; a <= 9; a += 2)
	{
		tmp = a;
		if(tmp < l) continue;
		if(tmp > r) break;
		if(prime(tmp)) printf("%d\n", tmp);
	}
	if(l <= 11 && 11 <= r) puts("11");
	for(int a = 1, tmp; a <= 9; a += 2)
		for(int b = 0; b <= 9; ++b)
		{
			tmp = a * 101 + b * 10;
			if(tmp < l) continue;
			if(tmp > r) break;
			if(prime(tmp)) printf("%d\n", tmp);
		}
	for(int a = 1, tmp; a <= 9; a += 2)
		for(int b = 0; b <= 9; ++b)
			for(int c = 0; c <= 9; ++c)
			{
				tmp = a * 10001 + b * 1010 + c * 100;
				if(tmp < l) continue;
				if(tmp > r) break;
				if(prime(tmp)) printf("%d\n", tmp);
			}
	for(int a = 1, tmp; a <= 9; a += 2)
		for(int b = 0; b <= 9; ++b)
			for(int c = 0; c <= 9; ++c)
				for(int d = 0; d <= 9; ++d)
				{
					tmp = a * 1000001 + b * 100010 + c * 10100 + d * 1000;
					if(tmp < l) continue;
					if(tmp > r) break;
					if(prime(tmp)) printf("%d\n", tmp);
				}
	for(int a = 1, tmp; a <= 9; a += 2)
		for(int b = 0; b <= 9; ++b)
			for(int c = 0; c <= 9; ++c)
				for(int d = 0; d <= 9; ++d)
					for(int e = 0; e <= 9; ++e)
					{
						tmp = a * 100000001 + b * 10000010 + c * 1000100 + d * 101000 + e * 10000;
						if(tmp < l) continue;
						if(tmp > r) break;
						if(prime(tmp)) printf("%d\n", tmp);
					}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
