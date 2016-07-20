#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 21;
int t, id, n, tot, cnt[maxn], pos[maxn];
struct Result
{
	int a, b, c;
	bool operator < (const Result &x) const
	{
		if(a != x.a)
			return a < x.a;
		if(b != x.b)
			return b < x.b;
		return c < x.c;
	}
} ans[maxn];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		bool flag = 1;
		scanf("%d%d", &id, &n);
		tot = n;
		for(int i = 0; i < n; ++i)
		{
			scanf("%d", cnt + i);
			pos[i] = i + 1;
		}
		for(int i = 0; i < n - 2; ++i)
		{
			int k = 0;
			for(int j = 1; j < tot; ++j)
				if(cnt[j] < cnt[k])
					k = j;
			if(tot < 3 || !cnt[(k - 1 + tot) % tot] || !cnt[(k + 1) % tot])
			{
				flag = 0;
				break;
			}
			int a = pos[(k - 1 + tot) % tot], b = pos[k], c = pos[(k + 1) % tot];
			if(a > b)
				swap(a, b);
			if(a > c)
				swap(a, c);
			if(b > c)
				swap(b, c);
			ans[i] = (Result){a, b, c};
			--cnt[(k - 1 + tot) % tot];
			--cnt[k];
			--cnt[(k + 1) % tot];
			int tmp = 0;
			for(int j = 0; j < tot; ++j)
				if(cnt[j])
				{
					cnt[tmp] = cnt[j];
					pos[tmp] = pos[j];
					++tmp;
				}
			tot = tmp;
		}
		if(!flag)
			printf("%d N\n", id);
		else
		{
			printf("%d Y\n", id);
			sort(ans, ans + n - 2);
			for(int i = 0; i < n - 2; ++i)
				printf("%d %d %d\n", ans[i].a, ans[i].b, ans[i].c);
		}
	}
	return 0;
}
