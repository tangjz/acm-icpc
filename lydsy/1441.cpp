/*
 * 使劲想想扩展欧几里得就好了 
 */
#include <cstdio>
#include <algorithm>
using namespace std;
int n, num, ans;
inline int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int main()
{
	scanf("%d", &n);
	while(n--) { scanf("%d", &num); ans = gcd(ans, abs(num)); }
	printf("%d\n", ans);
	return 0;
}
