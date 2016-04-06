//#include <ctime>
//#include <iostream>
#include <map>
#include <set>
#include <list>
#include <queue>
#include <cmath>
#include <vector>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
int n, q, a[100086], b[100086][18];
map<int, long long> Sum;
int gcd(int x, int y) { return y ? gcd(y, x % y) : x; }
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d", a + i), b[i][0] = a[i];
	for(int j = 1; j <= 17; ++j)
		for(int i = 1; i <= n; ++i)
			b[i][j] = gcd(b[i][j - 1], b[min(i + (1 << j - 1), n)][j - 1]);
	for(int i = 1; i <= n; ++i)
	{
		int val = a[i], last = i, pos = i;
		while(pos <= n)
		{
			while(1)
			{
				int k = 1;
				while(pos + (1 << k) - 1 <= n && b[pos][k] % val == 0) ++k; --k;
				pos = pos + (1 << k) - 1;
				if(pos == n || a[pos + 1] % val != 0) break;
			}
			Sum[val] += pos - last + 1;
			last = ++pos;
			val = gcd(val, a[pos]);
		}
	}
	scanf("%d", &q);
	while(q--)
	{
		int x;
		scanf("%d", &x);
		printf("%I64d\n", Sum[x]);
	}
	return 0;
}
