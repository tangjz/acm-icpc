#include <set>
#include <map>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <ctime>
#include <cmath>
#include <vector>
#include <string>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <functional>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = 100010, mod = 1000000007;
int n;
bool isprime(int x)
{
	if(x < 2)
		return 0;
	for(int i = 2; (LL)i * i <= x; ++i)
		if(x % i == 0)
			return 0;
	return 1;
}
int main()
{
	scanf("%d", &n);
	if(isprime(n))
		printf("1\n%d\n", n);
	else if(isprime(n - 2))
		printf("2\n2 %d\n", n - 2);
	else
	{
		for(int i = 3; i < n - 3 - i; i += 2)
			if(isprime(i) && isprime(n - 3 - i))
			{
				printf("3\n3 %d %d\n", i, n - 3 - i);
				break;
			}
	}
	return 0;
}
