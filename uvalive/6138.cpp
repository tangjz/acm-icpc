#include <cstdio>
int A;
int main()
{
	while(scanf("%d", &A) == 1)
		puts(A % 6 ? "N" : "Y");
	return 0;
}
