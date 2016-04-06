#include <cstdio>
int sum;
int main()
{
	for(int i = 3; i < 1000; ++i)
		if(i % 3 == 0 || i % 5 == 0) sum += i;
	printf("%d\n", sum);
	return 0;
}
