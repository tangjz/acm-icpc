#include <map>
#include <queue>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
using namespace std;
long long n, k;
int main()
{
	long long tmp;
	scanf("%I64d%I64d", &n, &k);
	tmp = (n + 1) / 2;
	if(k <= tmp)
	{
		printf("%I64d\n", 2 * k - 1);
	}
	else
	{
		k -= tmp;
		printf("%I64d\n", 2 * k);
	}
	return 0;
}
