#include <cstdio>
#include <algorithm>
using namespace std;
char str[27];
int main()
{
	while(scanf("%s", str) == 1)
	{
		int i, j = 0;
		for(i = 1; str[i] != '\0'; ++i)
			if(str[i] >= str[i - 1])
				j = 1;
		if(j)
		{
			next_permutation(str, str + i);
			puts(str);
		}
		else
			puts("What?");
	}
	return 0;
}
