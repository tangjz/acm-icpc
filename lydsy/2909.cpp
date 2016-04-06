#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100001, maxs = 10;
int n, f[maxn][maxs], p[maxs][maxn], skip;
char num[maxs];
struct Node
{
	int highLen, highDig, lowLen, lowDig;
	bool operator < (const Node &t) const
	{
		if(highLen + lowLen != t.highLen + t.lowLen)
			return highLen + lowLen < t.highLen + t.lowLen;
		if(highDig != t.highDig)
			return highDig < t.highDig;
		if(highLen == t.highLen)
			return lowDig < t.lowDig;
		if(highLen < t.highLen)
			return lowDig < t.highDig;
		return highDig < t.lowDig;
	}
} e[maxs << 1], ans;
int main()
{
	while(scanf("%d", &n) != EOF && n)
	{
		sprintf(num, "%d", n);
		int pos1, pos2;
		for(pos1 = 0; num[pos1] == num[0]; ++pos1);
		if(num[pos1])
		{
			for(pos2 = pos1; num[pos2] == num[pos1]; ++pos2);
			if(!num[pos2])
				++skip;
		}
		for(int i = 1; i < maxs; ++i)
			memset(p[i], -1, n * sizeof(int));
		bool flag = 0;
		for(int i = 1; !flag; ++i)
		{
			for(int j = 1; j < maxs && !flag; ++j)
			{
				f[i][j] = (f[i - 1][j] * 10 + j) % n;
				int val = f[i][j], tot = 0;
				for(int k = j; k >= 1; --k)
					if(p[k][val] != -1)
						e[tot++] = (Node){i - p[k][val], j, p[k][val], j - k};
				if(val)
					val = n - val;
				for(int k = 1; k < maxs - j; ++k)
					if(p[k][val] != -1)
						e[tot++] = (Node){i - p[k][val], j, p[k][val], j + k};
				sort(e, e + tot);
				if(skip < tot)
				{
					ans = e[skip];
					flag = 1;
				}
				else
					skip -= tot;
			}
			for(int j = 1; j < maxs && !flag; ++j)
				p[j][f[i][j]] = i;
		}
		printf("%d: %d %d %d %d\n", n, ans.highLen, ans.highDig, ans.lowLen, ans.lowDig);
	}
	return 0;
}
