#include <cstdio>
int A, P;
bool flag;
int main()
{
	scanf("%d%d", &P, &A);
	for(int X = 0; X <= P; ++X)
		if((long long)X * X % P == A)
		{
			printf("%d ", X);
			flag = 1;
		}
	if(!flag)
	    printf("No Solution");
	putchar('\n');
	return 0;
}
