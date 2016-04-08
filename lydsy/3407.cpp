#include <cstdio>
const int maxv = 45001;
int n, v, x;
bool f[maxv];
int main()
{
	scanf("%d%d", &v, &n);
	f[0] = 1;
	while(n--)
	{
		scanf("%d", &x);
		for(int i = v; i >= x; --i)
			f[i] |= f[i - x];
	}
	for(int i = v; i >= 0; --i)
		if(f[i])
		{
			printf("%d\n", i);
			return 0;
		}
}
