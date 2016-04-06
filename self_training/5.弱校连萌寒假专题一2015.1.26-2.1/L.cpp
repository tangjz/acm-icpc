#include <map>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 16;
int n;
struct DucciSeq
{
	int a[maxn];
	bool operator < (const DucciSeq &x) const
	{
		for(int i = 0; i < maxn; ++i)
			if(a[i] != x.a[i])
				return a[i] < x.a[i];
		return 0;
	}
	bool empty() const
	{
		for(int i = 0; i < n; ++i)
			if(a[i])
				return 0;
		return 1;
	}
} x;
map<DucciSeq, int> Hash;
int abs(int x)
{
	return x < 0 ? -x : x;
}
int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		memset(&x, 0, sizeof x);
		Hash.clear();
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%d", &x.a[i]);
		if(x.empty())
		{
			puts("ZERO");
			continue;
		}
		Hash[x] = 1;
		for(int t = 1; t <= 1000; ++t)
		{
			int tmp = x.a[0];
			for(int i = 0; i < n - 1; ++i)
				x.a[i] = abs(x.a[i] - x.a[i + 1]);
			x.a[n - 1] = abs(x.a[n - 1] - tmp);
			if(x.empty())
			{
				puts("ZERO");
				break;
			}
			else if(Hash[x])
			{
				puts("LOOP");
				break;
			}
			Hash[x] = 1;
		}
	}
	return 0;
}
