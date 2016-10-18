#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;
const int maxn = 10001;
int x[6], y[6], ans;
int main()
{
	for(int i = 0; i < 6; ++i)
		scanf("%d", x + i);
	for(int i = 0; i < 6; ++i)
		if(x[i] > y[0])
		{
			for(int j = 0; j < 6; ++j)
				y[j] = x[(i + j) % 6];
		}
	ans = (y[1] + y[1] + y[2]) * y[2] + (y[5] + y[5] + y[0] - y[2]) * (y[0] - y[2]) + (y[4] - y[0] + y[2] + y[1] + y[2]) * (y[3]);
	printf("%d\n", ans);
	return 0;
}
//163345 
