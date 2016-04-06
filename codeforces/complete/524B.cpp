#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1001;
int n, w[maxn], h[maxn], hh, ans = ~0u >> 1;
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d%d", w + i, h + i);
		if(w[i] > h[i])
			swap(w[i], h[i]);
		if(hh < w[i])
			hh = w[i];
	}
	for( ; hh <= 1000; ++hh)
	{
		int ww = 0;
		for(int i = 0; i < n; ++i)
			if(hh >= h[i])
				ww += w[i];
			else
				ww += h[i];
		if(ans > hh * ww)
			ans = hh * ww;
	}
	printf("%d\n", ans);
	return 0;
}
