#include <cmath>
#include <cstdio>
int len;
double num, pow2[200];
char str[20];
bool flag;
int main()
{
	pow2[100] = 1.0;
	for(int i = 1; i <= 64; ++i)
	{
		pow2[100 + i] = pow2[100 + i - 1] * 2;
		pow2[100 - i] = pow2[100 - i + 1] / 2;
	}
	puts("Program 6 by team X");
	while(scanf("%s", str) != EOF)
	{
		len = 0;
		for(int i = 1; i < 8; ++i)
			len = (len << 1) + (str[i] == '1');
		len -= 63;
		num = 1.0;
		for(int i = 1; i <= 8; ++i)
			if(str[7 + i] == '1')
				num += pow2[100 - i];
		num *= pow2[100 + len];
		flag = 0;
		for(int i = 1; i < 16; ++i)
			flag |= str[i] == '1';
		if(str[0] == '1')
			num = -num;
		if(!flag)
			num = 0;
		sprintf(str, "%le", num);
		if (num >= 0)
			putchar(' ');
		int i = 0;
		while (str[i] != 'e')
			putchar(str[i++]);
		putchar(str[i++]);
		putchar(str[i++]);
		putchar('0');
		while (str[i] != '\0')
			putchar(str[i++]);
		putchar('\n');
	}
	puts("End of program 6 by team X");
	return 0;
}
