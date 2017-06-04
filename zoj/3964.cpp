#include <cstdio>
const int maxn = 100001;
int t, n, a[maxn], b[maxn], SG0, SG1, SG2, c1, c11, c2;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%d", a + i);
		SG0 = SG1 = SG2 = c1 = c11 = c2 = 0;
		for(int i = 0; i < n; ++i)
		{
			scanf("%d", b + i);
			switch(b[i]) {
				case 0 : {
					SG0 ^= a[i];
					break;
				}
				case 1 : {
					SG1 ^= a[i] & 1;
					++c1;
					c11 += a[i] > 1;
					break;
				}
				case 2 : {
					SG2 ^= a[i] & 1 ? 0 : (a[i] >> 1);
					++c2;
					break;
				}
			}
		}
		if(c2 > 1)
			puts("Bob");
		else if(c2 == 1)
		{
			if(c11 > 0)
				SG0 = 0;
			else
				SG0 = !(SG0 ^ SG1) ? SG2 : 0;
			puts(SG0 ? "Alice" : "Bob");
		}
		else
		{
			if(c11 > 1)
				SG0 = 0;
			else if(c11 == 1)
				SG0 = SG0 < 2 ? SG0 ^ SG1 : 0;
			else
				SG0 ^= SG1;
			puts(SG0 ? "Alice" : "Bob");
		}
	}
	return 0;
}
