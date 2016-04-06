#include <cstdio>
char a[2], b[2];
int main()
{
	while(scanf("%s%s",a,b) == 2)
	{
		if(a[0] == 'M' || a[0] == 'F')
			puts("Error");
		else if(b[0] == 'F')
			puts("Bingo");
		else if(a[0] == 'B' || b[0] == 'B')
			puts("0");
		else if(a[0] == '9' && b[0] == 'M')
			puts("1");
		else if(b[0] == 'M')
			puts("-1");
		else if(a[0] > b[0])
			puts("-1");
		else if(a[0] == b[0])
			puts("0");
		else
			puts("1");
	}
	return 0;
}
