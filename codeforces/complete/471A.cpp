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
int a[10], x;
int main()
{
	for(int i = 0; i < 6; ++i)
	{
		scanf("%d", &x);
		++a[x];
	}
	for(int i = 1; i <= 9; ++i)
		if(a[i] >= 4)
		{
			a[i] -= 4;
			for(int i = 1; i <= 9; ++i)
				if(a[i] == 2)
				{
					puts("Elephant");
					return 0;
				}
			puts("Bear");
			return 0;
		}
	puts("Alien");
	return 0;
}
