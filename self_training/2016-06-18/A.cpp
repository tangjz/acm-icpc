#include <cstdio>
int t, n;
char str[10][5];
int main(int argc, char* argv[])
{
	scanf("%d", &t);
	sscanf(argv[1], "%d", &n);
	while(t--)
	{
		for(int i = 0; i < 10; ++i)
			scanf("%s", str[i]);
		if(n == 42)
		{
			for(int i = 0; i < 10; ++i)
				printf("%s", str[i]);
			printf("%s\n", "AA");
		}
		else
		{
			bool flag = 1;
			for(int i = 0; i < 10 && flag; ++i)
				for(int j = 0; j < 10 && flag; ++j)
				{
					if(i == j)
						continue;
					for(int k = 1, o; k <= 4; ++k)
					{
						for(o = 0; o < k && str[i][4 - k + o] == str[j][o]; ++o);
						if(o == k)
						{
							flag = 0;
							printf("%s", str[i]);
							if(str[j][k])
								printf("%s", str[j] + k);
							for(o = 0; o < 10; ++o)
								if(o != i && o != j)
									printf("%s", str[o]);
							for(o = k; o > 1; --o)
								putchar('A');
							putchar('\n');
							break;
						}
					}
				}
		}
	}
	return 0;
}
