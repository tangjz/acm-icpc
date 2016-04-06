#include <cstdio>
#include <cstring>
const int maxn = 1 << 7, mod = 1000000007;
struct Mat
{
	int r, c, num[maxn][maxn];
	void clear()
	{
		memset(num, 0, sizeof num);
	}
	Mat operator * (const Mat &x) const
	{
		Mat tmp = {};
		tmp.r = r;
		tmp.c = x.c;
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j)
				for(int k = 0; k < x.c; ++k)
					tmp.num[i][j] = (tmp.num[i][j] + (long long)num[i][k] * x.num[k][j]) % mod;
		return tmp;
	}
} A, B;
int main()
{
	for(int i = 0; i < 2; ++i)
		A.num[i][i] = 1;
	for(int h = 1; h <= 7; ++h)
	{
		int w, maxs = 1 << h;
		scanf("%d", &w);
		A.r = A.c = B.r = B.c = maxs;
		B.clear();
		for(int i = 0; i < maxs; ++i)
			for(int j = 0; j < maxs; ++j)
				for(int k = 0; k < (maxs >> 1); ++k)
					if((i | j | k | (k << 1)) == maxs - 1)
						++B.num[i][j];
		while(w)
		{
			if(w & 1)
				A = A * B;
			B = B * B;
			w >>= 1;
		}
	}
	printf("%d\n", A.num[0][0]);
	return 0;
}
