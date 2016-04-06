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
int n, a[2010], no[2010], ans;
int pos1;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i), no[i] = i;
	for(int i = 1; i < n; ++i)
		for(int j = 1; j <= n - i; ++j)
			if(a[j] > a[j + 1]) swap(a[j], a[j + 1]), swap(no[j], no[j + 1]);
	for(int i = 1; i < n; ++i)
		if(a[i] == a[i + 1])
		{
			if(a[i + 1] == a[i + 2])
			{
				puts("YES");
				for(int j = 1; j < n; ++j) printf("%d ", no[j]);
				printf("%d\n", no[n]);
				swap(no[i], no[i + 1]);
				for(int j = 1; j < n; ++j) printf("%d ", no[j]);
				printf("%d\n", no[n]);
				swap(no[i], no[i + 2]);
				for(int j = 1; j < n; ++j) printf("%d ", no[j]);
				printf("%d\n", no[n]);
				return 0;
			}
			else if(pos1)
			{
				puts("YES");
				for(int j = 1; j < n; ++j) printf("%d ", no[j]);
				printf("%d\n", no[n]);
				swap(no[i], no[i + 1]);
				for(int j = 1; j < n; ++j) printf("%d ", no[j]);
				printf("%d\n", no[n]);
				swap(no[pos1], no[pos1 + 1]);
				for(int j = 1; j < n; ++j) printf("%d ", no[j]);
				printf("%d\n", no[n]);
				return 0;
			}
			else pos1 = i;
		}
	puts("NO");
	return 0;
}
