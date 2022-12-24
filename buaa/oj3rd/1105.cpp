#include <cstdio>
const char *op[] = {"¡°", "¡±"};
int ch, flag;
int main()
{
	while((ch = getchar()) != EOF)
		if(ch == '"')
		{
			printf("%s", op[flag]);
			flag ^= 1;
		}
		else
			putchar(ch);
	return 0;
}
