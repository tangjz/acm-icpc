/*
 * ¼òµ¥dp 
 */ 
#include <cstdio>
const int mod = 2012;
int f[1001];
int main()
{
	int len = f[1] = 1;
	for(int ch = getchar(); len > 0 && ch == '(' || ch == ')'; ch = getchar())
	{
		int delta = ch == '(' ? 1 : -1;
		len += delta;
		for(int j = delta < 0 ? 1 : len; 1 <= j && j <= len; j -= delta)
		{
			f[j] += f[j - delta];
			if(f[j] >= mod) f[j] -= mod;
		}
		f[len + 1] = 0;
	}
	printf("%d\n", len == 1 ? f[1] : 0);
	return 0;
}
