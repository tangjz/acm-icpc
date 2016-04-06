#include <cstdio>
const char* ans[] = {"1", "5", "25", "125", "625"};
char str[102];
int main()
{
	int i;
	while(scanf("%s", str) != EOF)
	{
		for(i = 0; str[i]; ++i);
		--i;
		if(!i && str[i] <= '2')
			puts(ans[str[i] - '0']);
		else
			puts(ans[4 - (str[i] & 1)]);
	}
	return 0;
}
