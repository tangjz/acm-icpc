#include <cmath>
#include <cstdio>
const char *S = "TDH";
double x[3];
bool vis[3];
char op[2];
int main()
{
	while(scanf("%s", op) != EOF)
	{
		if(op[0] == 'E')
			break;
		vis[0] = vis[1] = vis[2] = 0;
		for(int i = 0; i < 3; ++i)
			if(op[0] == S[i])
			{
				scanf("%lf", x + i);
				vis[i] = 1;
				break;
			}
		scanf("%s", op);
		for(int i = 0; i < 3; ++i)
			if(op[0] == S[i])
			{
				scanf("%lf", x + i);
				vis[i] = 1;
				break;
			}
		if(!vis[0])
			x[0] = x[2] - 0.5555 * (6.11 * exp(5417.7530 * (1 / 273.16 - 1 / (x[1] + 273.16))) - 10.0);
		else if(!vis[1])
			x[1] = 1 / (1 / 273.16 - log(((x[2] - x[0]) / 0.555 + 10.0) / 6.11) / 5417.7530) - 273.16;
		else
			x[2] = x[0] + 0.5555 * (6.11 * exp(5417.7530 * (1 / 273.16 - 1 / (x[1] + 273.16))) - 10.0);
		for(int i = 0; i < 3; ++i)
			printf("%c %.1f%c", S[i], x[i], " \n"[i == 2]);
	}
	return 0;
}