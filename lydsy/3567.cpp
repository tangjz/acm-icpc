#include <cstdio>
#include <cstring>
#include <algorithm>
typedef unsigned int UL;
const int maxn = 30000, maxs = ((maxn - 1) >> 5) + 1, maxd = ((maxn - 1) >> 7) + 1, maxp = 1 << (1 << 4);
int n, bsize, s[maxs][maxs];
short p[maxn][4], sz[maxp], pA[maxn], pB[maxn], pC[maxn], pD[maxn], f[maxn][maxs];
inline bool cmp_x1(const short &i, const short &j)
{
	return p[i][0] < p[j][0];
}
inline bool cmp_y1(const short &i, const short &j)
{
	return p[i][1] < p[j][1];
}
inline bool cmp_x2(const short &i, const short &j)
{
	return p[i][2] < p[j][2];
}
inline bool cmp_y2(const short &i, const short &j)
{
	return p[i][3] < p[j][3];
}
inline bool cmp(const short &i, const short &j)
{
	return std::max(p[i][0], p[j][0]) < std::min(p[i][2], p[j][2])
		&& std::max(p[i][1], p[j][1]) < std::min(p[i][3], p[j][3]);
}
inline short popcount(const UL &x)
{
	return sz[x >> (1 << 4)] + sz[x & ((1 << (1 << 4)) - 1)];
}
struct Bitset
{
	UL data[maxs];
	inline void set(int pos)
	{
		data[pos >> 5] |= 1ULL << (pos & ((1 << 5) - 1));
	}
	inline void clear()
	{
		memset(data, 0, bsize * sizeof(UL));
	}
	inline void copy(const Bitset &t)
	{
		memcpy(data, t.data, bsize * sizeof(UL));
	}
	inline void operator &= (const Bitset &t)
	{
		for(register int i = 0; i < bsize; ++i)
			data[i] &= t.data[i];
	}
} A[maxd], B[maxd], C[maxd], D, E, F;
template<class T> inline void scan(T &x)
{
	register int ch;
	while((ch = getchar()) < '0' || ch > '9');
	for(x = ch - '0'; (ch = getchar()) >= '0' && ch <= '9'; x = (x << 3) + (x << 1) + ch - '0');
}
int main()
{
	for(int i = 1; i < maxp; ++i)
		sz[i] = sz[i >> 1] + (i & 1);
	scan(n);
	bsize = ((n - 1) >> 5) + 1;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < 4; ++j)
			scan(p[i][j]);
	int blk = ((n - 1) >> 7) + 1;
	for(int i = 0; i < n; ++i)
		pA[i] = i;
	std::sort(pA, pA + n, cmp_x1);
	for(int i = 0, j = 0; i < blk; ++i)
	{
		int pR = std::min((i + 1) << 7, n);
		if(i)
			A[i].copy(A[i - 1]);
		for( ; j < pR; ++j)
			A[i].set(pA[j]);
	}
	for(int i = 0; i < n; ++i)
		pB[i] = i;
	std::sort(pB, pB + n, cmp_y1);
	for(int i = 0, j = 0; i < blk; ++i)
	{
		int pR = std::min((i + 1) << 7, n);
		if(i)
			B[i].copy(B[i - 1]);
		for( ; j < pR; ++j)
			B[i].set(pB[j]);
	}
	for(int i = 0; i < n; ++i)
		pC[i] = i;
	std::sort(pC, pC + n, cmp_x2);
	for(int i = 0, j = 0; i < blk; ++i)
	{
		int pR = std::min((i + 1) << 7, n);
		if(i)
			C[i].copy(C[i - 1]);
		for( ; j < pR; ++j)
			C[i].set(pC[n - 1 - j]);
	}
	for(int i = 0; i < n; ++i)
		pD[i] = i;
	std::sort(pD, pD + n, cmp_y2);
	for(int i = n - 1, j = 0, k; i >= 0; --i)
	{
		for( ; j < n && p[pD[n - 1 - j]][3] > p[pB[i]][1]; ++j)
			D.set(pD[n - 1 - j]);
		E.copy(D);
		for(k = 0; k < blk; ++k)
		{
			int pR = std::min((k + 1) << 7, n);
			if(p[pA[pR - 1]][0] >= p[pB[i]][2])
				break;
		}
		k ? F.copy(A[k - 1]) : F.clear();
		if(k < blk)
			for(int pL = k << 7; p[pA[pL]][0] < p[pB[i]][2]; ++pL)
				F.set(pA[pL]);
		E &= F;
		for(k = 0; k < blk; ++k)
		{
			int pR = std::min((k + 1) << 7, n);
			if(p[pB[pR - 1]][1] >= p[pB[i]][3])
				break;
		}
		k ? F.copy(B[k - 1]) : F.clear();
		if(k < blk)
			for(int pL = k << 7; p[pB[pL]][1] < p[pB[i]][3]; ++pL)
				F.set(pB[pL]);
		E &= F;
		for(k = 0; k < blk; ++k)
		{
			int pR = std::min((k + 1) << 7, n);
			if(p[pC[n - pR]][2] <= p[pB[i]][0])
				break;
		}
		k ? F.copy(C[k - 1]) : F.clear();
		if(k < blk)
			for(int pL = k << 7; p[pC[n - 1 - pL]][2] > p[pB[i]][0]; ++pL)
				F.set(pC[n - 1 - pL]);
		E &= F;
		for(k = 0; k < bsize; ++k)
		{
			f[pB[i]][k] = popcount(E.data[k]);
			s[pB[i] >> 5][k] += f[pB[i]][k];
			if(k)
				f[pB[i]][k] += f[pB[i]][k - 1];
		}
	}
	for(int i = 0; i < bsize; ++i)
		for(int j = 0; j < bsize; ++j)
		{
			if(i)
				s[i][j] += s[i - 1][j];
			if(j)
				s[i][j] += s[i][j - 1];
			if(i && j)
				s[i][j] -= s[i - 1][j - 1];
		}
	int m, L1, R1, L2, R2, lastans = 0;
	scan(m);
	while(m--)
	{
		scan(L1), L1 ^= lastans;
		scan(R1), R1 ^= lastans;
		scan(L2), L2 ^= lastans;
		scan(R2), R2 ^= lastans;
		int pL1 = --L1 >> 5, pR1 = --R1 >> 5;
		if((pL1 << 5) < L1)
			++pL1;
		if(R1 < ((pR1 + 1) << 5) - 1)
			--pR1;
		int pL2 = --L2 >> 5, pR2 = --R2 >> 5;
		if((pL2 << 5) < L2)
			++pL2;
		if(R2 < ((pR2 + 1) << 5) - 1)
			--pR2;
		int ans = 0;
		if(pL1 <= pR1)
		{
			if(pL2 <= pR2)
			{
				ans += s[pR1][pR2];
				if(pL1)
					ans -= s[pL1 - 1][pR2];
				if(pL2)
					ans -= s[pR1][pL2 - 1];
				if(pL1 && pL2)
					ans += s[pL1 - 1][pL2 - 1];
				for(int i = L1; i < (pL1 << 5); ++i)
				{
					ans += f[i][pR2];
					if(pL2)
						ans -= f[i][pL2 - 1];
					for(int j = L2; j < (pL2 << 5); ++j)
						ans += cmp(i, j);
					for(int j = (pR2 + 1) << 5; j <= R2; ++j)
						ans += cmp(i, j);
				}
				for(int i = (pR1 + 1) << 5; i <= R1; ++i)
				{
					ans += f[i][pR2];
					if(pL2)
						ans -= f[i][pL2 - 1];
					for(int j = L2; j < (pL2 << 5); ++j)
						ans += cmp(i, j);
					for(int j = (pR2 + 1) << 5; j <= R2; ++j)
						ans += cmp(i, j);
				}
				for(int i = L2; i < (pL2 << 5); ++i)
				{
					ans += f[i][pR1];
					if(pL1)
						ans -= f[i][pL1 - 1];
				}
				for(int i = (pR2 + 1) << 5; i <= R2; ++i)
				{
					ans += f[i][pR1];
					if(pL1)
						ans -= f[i][pL1 - 1];
				}
			}
			else
				for(int i = L2; i <= R2; ++i)
				{
					ans += f[i][pR1];
					if(pL1)
						ans -= f[i][pL1 - 1];
					for(int j = L1; j < (pL1 << 5); ++j)
						ans += cmp(i, j);
					for(int j = (pR1 + 1) << 5; j <= R1; ++j)
						ans += cmp(i, j);
				}
		}
		else if(pL2 <= pR2)
			for(int i = L1; i <= R1; ++i)
			{
				ans += f[i][pR2];
				if(pL2)
					ans -= f[i][pL2 - 1];
				for(int j = L2; j < (pL2 << 5); ++j)
					ans += cmp(i, j);
				for(int j = (pR2 + 1) << 5; j <= R2; ++j)
					ans += cmp(i, j);
			}
		else
			for(int i = L1; i <= R1; ++i)
				for(int j = L2; j <= R2; ++j)
					ans += cmp(i, j);
		printf("%d\n", ans);
		lastans = ans;
	}
	return 0;
}
