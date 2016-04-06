#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn = 200001;
int n, x[maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", x + i);
		x[i] += i;
	}
	sort(x, x + n);
	puts(n == unique(x, x + n) - x ? "Happy" : "Sad");
	return 0;
}
