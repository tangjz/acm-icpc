#include <map>
#include <set>
#include <list>
#include <stack>
#include <queue>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
int n;
int main()
{
	scanf("%d", &n);
	if(n & 1) printf("%d %d\n", 9, n - 9);
	else printf("%d %d\n", 4, n - 4);
	return 0;
}
