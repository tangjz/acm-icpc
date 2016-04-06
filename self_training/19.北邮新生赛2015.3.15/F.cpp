#include <cstdio>
#include <algorithm>
using namespace std;
int t, a[4];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		for(int i = 0; i < 4; ++i)
			scanf("%d", a + i);
		sort(a, a + 4);
		bool flag = 0;
		for(int i = 0; i < 4 && !flag; ++i)
			for(int j = i + 1; j < 4 && !flag; ++j)
				for(int k = j + 1; k < 4 && !flag; ++k)
					flag |= a[i] + a[j] > a[k];
		puts(flag ? "YES" : "NO");
	}
	return 0;
}
