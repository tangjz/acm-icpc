#include <cstdio>
int t;
double a, b, c, d;
char op;
void print(double x, double y)
{
	bool flag = 0;
	if(x > 1e-8 || x < -1e-8)
	{
		printf("%.2f", x);
		++flag;
	}
	if(y > 1e-8 || y < -1e-8)
	{
		if(flag && y >= 0)
			putchar('+');
		printf("%.2fi", y);
		++flag;
	}
	if(!flag)
		putchar('0');
	putchar('\n');
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%*c%c%lf%lf%lf%lf", &op, &a, &b, &c, &d);
		if(op == '+')
			print(a + c, b + d);
		else if(op == '-')
			print(a - c, b - d);
		else if(op == '*')
			print(a * c - b * d, a * d + b * c);
		else if(op == '/')
		{
			if(-1e-8 < c - d && c - d < 1e-8)
				puts("Wrong Input!");
			else
				print((a * c + b * d) / (c * c + d * d), (b * c - a * d) / (c * c + d * d));
		}
	}
	return 0;
}
