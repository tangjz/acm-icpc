#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <stack>
#include <map>

using namespace std;

int n, cnt = 0;
int main()
{
	scanf("%d", &n);
	for(int a = 1; a <= n; ++a)
		for(int b = a; b <= n; ++b)
		{
			int c = (int)sqrt(a * a + b * b);
			if(c > n) continue;
			if(c * c == a * a + b * b) ++cnt;
		}
	printf("%d\n", cnt);
	return 0;
}
