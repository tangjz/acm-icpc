#include <cstdio>
const int Baron[] = {0, 0, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3};
//oeis	A186313	Baron Munchhausen's Omni-Sequence.
int t, n;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		printf("%d\n", Baron[n]);
	}
	return 0;
}
