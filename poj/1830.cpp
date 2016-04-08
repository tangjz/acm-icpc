#include <cstdio>
#include <cstring>
const int maxn = 30;
int test, n, s[maxn], t[maxn], mat[maxn], ans;
void swap(int &x, int &y)
{
	int t = x;
	x = y;
	y = t;
}
int main()
{
	scanf("%d", &test);
	while(test--)
	{
		memset(mat, 0, sizeof mat);
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
			scanf("%d", s + i);
		for(int i = 0; i < n; ++i)
		{
			scanf("%d", t + i);
			if(s[i] != t[i])
				mat[i] |= 1 << n;
			mat[i] |= 1 << i;
		}
		for(int i, j; scanf("%d%d", &i, &j) == 2 && i + j; )
			mat[j - 1] |= 1 << i - 1;
		ans = 0;
		for(int i = 0; i < n; ++i)
		{
			int j;
			for(j = i; j < n; ++j)
				if(mat[j] & 1 << i)
					break;
			if(~mat[j] & 1 << i)
				continue;
			swap(mat[ans], mat[j]);
			for(j = i + 1; j < n; ++j)
				if(mat[j] & 1 << i)
					mat[j] ^= mat[ans];
			++ans;
		}
		for(int i = ans; i < n; ++i)
			if(mat[i])
			{
				ans = -1;
				break;
			}
		if(ans == -1)
			puts("Oh,it's impossible~!!");
		else
			printf("%d\n", 1 << n - ans);
	}
	return 0;
}