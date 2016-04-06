#include <set>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
set<int> Q;
LL a[15];
int main()
{
	for(int i = 1, j = 1; j <= 1000000000L; j += ++i)
	{
	//	Q.insert(j);
	//	Q.insert(j + 1);
	}
	a[0] = 1;
	a[1] = 3;
	for(int i = 2; i <= 13; ++i)
		a[i] = 6 * a[i - 1] - a[i - 2];
	for(int i = 0; i <= 13; ++i)
	{
		LL b = a[i] - 1;
		if(b > 0 && b % 2 == 0 && b <= 2000000000L)
			Q.insert(b / 2);
		b = 3 * a[i] - 1;
		if(b > 0 && b % 2 == 0 && b <= 2000000000L)
			Q.insert(b / 2);
	}
	for(set<int>::iterator it = Q.begin(); it != Q.end(); ++it)
		printf("%d,", *it);
	return 0;
}
